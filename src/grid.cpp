#include "grid.h"

Grid::Grid(int rows, int cols)
    : start{0,0} , goal{rows-1,cols-1} , rows_(rows), cols_(cols), cells_(rows*cols, Cell::Open) {}
    
bool Grid::inBound(Pos p) const{
    return p.r >= 0 && p.r < rows_ && p.c >= 0 && p.c < cols_;
}

bool Grid::isWall(Pos p) const{
    return cells_[p.r * cols_ + p.c] == Cell::Wall;
}

void Grid::setWall(Pos p, bool wall){
    cells_[p.r * cols_ +p.c] = wall ? Cell::Wall : Cell::Open ;
}

Grid Grid::fromStrings(const std::vector<std::string>& lines){
    Grid g(static_cast<int>(lines.size()),static_cast<int>(lines[0].size()));
    for(int r=0 ; r<g.rows ; ++r){
        for(int c=0 ; c<g.cols ; ++c){
            char ch = lines[r][c];
            if(ch == '#') setWall({r,c}, true);
            else if(ch == 'S') g.start = {r,c};
            else if(ch == 'G') g.goal = {r,c};
        }
    }return g;
}