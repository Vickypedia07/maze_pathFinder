#pragma once
#include "grid.h"
#include <vector>

struct SearchResult{
    bool found = false;
    std::vector<Pos> visitedOrder;
    std::vector<Pos> path;
};

SearchResult bfs(const Grid& g);
SearchResult dfs(const Grid& g);