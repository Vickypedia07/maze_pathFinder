#include "pathfinder.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <array>
#include <utility>

namespace {
    const std::array<std::pair<int,int>,4> DIRS = {{{-1,0},{0,1},{1,0},{0,-1}}};


    std::vector<Pos> buildPath(const std::vector<int>& parent, const Grid& g){
        std::vector<Pos> path;
        const int cols = g.cols();
        const int startId = g.start.r*cols+g.start.c;
        int cur = g.goal.r*cols+g.goal.c;
        while(cur != -1){
            path.push_back({cur/cols, cur%cols});
            if(cur == startId) break;
            cur = parent[cur];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
}

SearchResult bfs(const Grid& g){
    SearchResult res;
    const int cols = g.cols();
    auto id = [cols](Pos p){
        return p.r*cols+p.c;
    };

    std::vector<int> parent(g.rows()*cols , -1);
    std::vector<char> seen(g.rows()*cols , 0);
    std::queue<Pos> q;

    q.push(g.start);
    seen[id(g.start)] = 1;

    while(!q.empty()){
        Pos cur = q.front();
        q.pop();
        res.visitedOrder.push_back(cur);
        if(cur == g.goal){
            res.found = true;
            break;
        }
        for(const auto& [dr,dc] : DIRS){
            Pos nxt{cur.r+dr, cur.c+dc};
            if(!g.inBounds(nxt) || g.isWall(nxt) || seen[id(nxt)]) continue;
            seen[id(nxt)] = 1;
            parent[id(nxt)] = id(cur);
            q.push(nxt);
        }
    }
    if(res.found) res.path = buildPath(parent , g);
    return res;
    
}

SearchResult dfs(const Grid& g) {
    SearchResult res;
    const int cols = g.cols();
    auto id = [cols](Pos p) { return p.r * cols + p.c; };

    std::vector<int> parent(g.rows() * cols, -1);
    std::vector<char> seen(g.rows() * cols, 0);
    std::stack<std::pair<Pos, int>> st;   // (cell, id of the cell we came from)

    st.push({g.start, -1});
    while (!st.empty()) {
        auto [cur, par] = st.top();
        st.pop();
        if (seen[id(cur)]) continue;
        seen[id(cur)] = 1;
        parent[id(cur)] = par;
        res.visitedOrder.push_back(cur);
        if (cur == g.goal) {
            res.found = true;
            break;
        }
        for (const auto& [dr, dc] : DIRS) {
            Pos nxt{cur.r + dr, cur.c + dc};
            if (!g.inBounds(nxt) || g.isWall(nxt) || seen[id(nxt)]) continue;
            st.push({nxt, id(cur)});
        }
    }
    if (res.found) res.path = buildPath(parent, g);
    return res;
}