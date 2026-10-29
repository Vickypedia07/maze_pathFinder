#pragma once
#include <string>
#include <vector>



struct Pos{
    int r,c;
    bool operator==(const Pos& o) const {return r==o.r && c==o.c;}
};

enum class Cell : char {Open , Wall};

class Grid{
public :
    Grid(int rows, int cols);
    int rows() const {
        return rows_;
    }
    int cols() const {
        return cols_;
    }

    bool inBounds(Pos p) const;
    bool isWall(Pos p) const;
    void setWall(Pos p, bool wall); 

    static Grid fromStrings(const std::vector<std::string>& lines);

    Pos start , goal;

private:
    int rows_ , cols_;
    std::vector<Cell> cells_;
};
