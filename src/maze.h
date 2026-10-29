#pragma once
#include "grid.h"

void generateMaze(Grid& g, unsigned seed);/*Sets starting position at (1,1) and
 goal position at (rows-2,cols-2) because the outer boundary is considered a wall,
 also the value of rows and cols should be odd so that the maze has a proper structure */

void addLoops(Grid& g, unsigned seed, double fraction);/*Creates loops in the maze by 
randomly removing some walls so the BFS and DFS algorithms can find multiple paths, the 
fraction parameter determines the probability of walls to be removed */