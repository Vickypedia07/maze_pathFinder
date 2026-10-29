#include "maze.h"

#include <array>
#include <random>
#include <utility>
#include <vector>
#include <stack>

void generateMaze(Grid& g, unsigned seed){
    for(int r=0 ; r<g.rows() ; ++r){
        for(int c=0 ; c<g.cols() ; ++c){
            g.setWall({r,c} , true);
        }
    }
    static const std::array<std::pair<int,int>,4> D = {{{-2,0},{2,0},{0,-2},{0,2}}};

    std::mt19937 rng(seed);
    std::stack<Pos> st;

    Pos s{1,1};
    g.setWall(s,false);
    st.push(s);

    while(!st.empty()){
        Pos cur = st.top();
        std::vector<Pos> options;
        for(const auto& [dr ,dc] : D){
            Pos n{cur.r+dr , cur.c+dc};
            if(n.r > 0 && n.r < g.rows()-1 &&
                n.c > 0 && n.c<g.cols()-1 &&
                g.isWall(n)) options.push_back(n);
        }
        if(options.empty()){
            st.pop();
            continue;
        }
        Pos n = options[rng()%options.size()];
        g.setWall({(cur.r+n.r)/2,(cur.c+n.c)/2},false);
        g.setWall(n,false);
        st.push(n);
    }
    g.start = {1,1};
    g.goal = {g.rows()-2,g.cols()-2};
}

void addLoops(Grid& g , unsigned seed , double fraction){
    std::mt19937 rng(seed);
    std::uniform_int_distribution dist(0.0,1.0);
    for(int r = 1 ; r<g.rows()-1 ; ++r){
        for(int c = 1 ; c<g.cols()-1 ; ++c){
            if(g.isWall({r,c}) && dist(rng) < fraction) g.setWall({r,c} , false);
        }
    }
}



