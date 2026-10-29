#include <catch2/catch_test_macros.hpp>
#include "grid.h"
#include <cstdlib>
#include "pathfinder.h"
#include "maze.h"

namespace {

// A valid path starts at start, ends at goal, never touches a wall,
// and every step moves exactly one cell up, down, left, or right.
bool isValidPath(const Grid& g, const std::vector<Pos>& path) {
    if (path.empty()) return false;
    if (!(path.front() == g.start) || !(path.back() == g.goal)) return false;
    for (size_t i = 0; i < path.size(); ++i) {
        if (!g.inBounds(path[i]) || g.isWall(path[i])) return false;
        if (i > 0) {
            int dist = std::abs(path[i].r - path[i - 1].r) +
                       std::abs(path[i].c - path[i - 1].c);
            if (dist != 1) return false;
        }
    }
    return true;
}

}  // namespace

TEST_CASE("Grid loads from text") {
    Grid g = Grid::fromStrings({
        "S.#",
        "..#",
        "#.G"
    });

    CHECK(g.rows() == 3);
    CHECK(g.cols() == 3);

    Pos wall{0, 2};
    Pos open{0, 1};
    CHECK(g.isWall(wall));
    CHECK_FALSE(g.isWall(open));

    CHECK(g.start.r == 0);
    CHECK(g.start.c == 0);
    CHECK(g.goal.r == 2);
    CHECK(g.goal.c == 2);
}

TEST_CASE("inBounds rejects positions outside the grid") {
    Grid g(3, 3);
    Pos inside{1, 1};
    Pos below{3, 0};
    Pos left{0, -1};
    CHECK(g.inBounds(inside));
    CHECK_FALSE(g.inBounds(below));
    CHECK_FALSE(g.inBounds(left));
}

TEST_CASE("DFS finds a valid path", "[dfs]") {
    Grid g = Grid::fromStrings({
        "S.#",
        "..#",
        "#.G"});
    auto res = dfs(g);
    REQUIRE(res.found);
    CHECK(isValidPath(g, res.path));
    CHECK(res.visitedOrder.front() == g.start);
}

TEST_CASE("DFS reports no path when blocked", "[dfs]") {
    Grid g = Grid::fromStrings({"S#G"});
    auto res = dfs(g);
    CHECK_FALSE(res.found);
    CHECK(res.path.empty());
}

TEST_CASE("DFS handles start equal to goal", "[dfs]") {
    Grid g(1, 1);   // start and goal are both (0,0)
    auto res = dfs(g);
    REQUIRE(res.found);
    CHECK(res.path.size() == 1);
}

TEST_CASE("DFS path is never shorter than BFS path", "[dfs][bfs]") {
    Grid g(5, 5);   // open 5x5 grid, start (0,0), goal (4,4)
    auto b = bfs(g);
    auto d = dfs(g);
    REQUIRE(b.found);
    REQUIRE(d.found);
    CHECK(isValidPath(g, d.path));
    CHECK(b.path.size() <= d.path.size());
}

TEST_CASE("every generated maze is solvable") {
    for (unsigned seed = 0; seed < 50; ++seed) {
        Grid g(21, 41);
        generateMaze(g, seed);
        REQUIRE(bfs(g).found);
    }
}

TEST_CASE("same seed gives the same maze") {
    Grid a(11, 11), b(11, 11);
    generateMaze(a, 7);
    generateMaze(b, 7);
    for (int r = 0; r < 11; ++r)
        for (int c = 0; c < 11; ++c)
            CHECK(a.isWall({r, c}) == b.isWall({r, c}));
}

TEST_CASE("BFS is never longer than DFS on mazes with loops", "[bfs][dfs][maze]") {
    for (unsigned seed = 0; seed < 50; ++seed) {
        Grid g(21, 41);
        generateMaze(g, seed);
        addLoops(g, seed + 1, 0.1);
        auto b = bfs(g);
        auto d = dfs(g);
        REQUIRE(b.found);
        REQUIRE(d.found);
        CHECK(isValidPath(g, b.path));
        CHECK(isValidPath(g, d.path));
        CHECK(b.path.size() <= d.path.size());
    }
}