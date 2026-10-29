#include <random>
#include <string>
#include "grid.h"
#include "maze.h"
#include "renderer.h"

int main(int argc, char** argv){
    const unsigned seed = argc>1 ? static_cast<unsigned>(std::stoul(argv[1])) : std::random_device{}() ;

    Grid g(21,41);
    generateMaze(g,seed);
    addLoops(g,seed+1000,0.05);
    runVisualizer(g,seed);
    return 0;
}