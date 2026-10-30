# maze_pathFinder
Minor project of the DSA internship at TechnGlobal Pvt. Ltd for the shortest route from start to end of a maze using BFS and DFS.

OVERVIEW
The maze is a NxM grid(N and M both are odd +ve integers). Each cell in the grid has a 
2-D representation({r,c}) as well as 1-D representation(r*no. of columns+c).'S' represents 
starting position, 'G' represents goal and '#' represents wall.

FEATURES
1) Grid-based maze representation
2) Random Maze Creation from text input
3) Pathfinding - Using BFS as well as DFS to find shortest route 
4) SFML based animated output rendering of the maze
5) Example ->  #########
               #S....###
               #.###.###
               #...#..##
               ###.##.##
               ###....G#
               #########

maze_pathFinder/
├── docs/
|   ├── screenshots
|   ├── PPT
|   └── DEMO VIDEO
├── src/
│   ├── grid.cpp
│   ├── grid.h
│   ├── main.cpp
│   ├── maze.cpp
|   ├── maze.h
│   ├── pathfinder.cpp
|   ├── pathfinder.h
│   ├── renderer.cpp
|   └── renderer.h
├── tests/
|   └── test_pathfinder.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md

TECHNOLOGY USED
1) Language :- C++
2) Build :- CMake
3) Editor :- VS Code
4) Unit Testing :- Catch2
5) Version Control :- Github
6) Animation Visualization :- SFML(Simple and Fast Multimedia Library)

BUILD AND RUN
From the project root : cmake -S . -B build -G Ninja
                        cmake --build build

Test : ctest --test-dir build --output-on-failure

Key   Action
B     Starts BFS for current maze
D     Starts DFS for current maze
N     Generates new maze
ESC   Closes the window(QUIT)


WORKING
1) The grid is actually a graph. Every open cell is a node, connected to its open UP, RIGHT, DOWN, LEFT
neighbours.The grid is stored in a flat vector, where a cell at (row, col) has index row * cols + col.

2) BFS uses a queue to take the oldest cell, mark it explored and pushes every open, unseen neighbour.

3) DFS uses a stack to take the newest cell, skip it if already explored and push the open unseen neighbours.

4) Maze generation uses a recursive backtracker. Starting at (1, 1), it jumps two cells in a random direction, removes the wall between them, and backtracks at dead ends. Grid sizes must be odd, so that cells sit on odd rows and columns and walls on even ones. The result is a perfect maze with exactly one route between any two cells. addLoops() then removes a fraction of the inner walls to create alternative routes.

5) Logic and drawing are separate. BFS and DFS does not draw the ouput. They return a SearchResult with visited order and the path, for example : S(1,1) - (1,2) - (1,3) - (2,3) - G(3,3). The renderer.cpp marks each cell as start, goal, explored, unexplored, wall and then assigns a color to them and animates the path frame by frame.


COMPLEXITY
R = rows ; C = columns ; V=RxC
Part            | Time             Space
________________|________________________
BFS             | O(V)             O(V)
DFS             | O(V)             O(V)
Maze generation | O(V)             O(V)worst case
addLoops        | O(V)             O(1) extra


                | BFS                       | DFS
Data Structure  | Queue                     | Stack
Explore         | In rings around the start | One corridor at a time
Path found      | Always shortest path      | The first valid path(not necessarily shortest)


TERMINAL OUTPUT
BFS | seed 42 | explored: 343 | path length: 73 | blue: 270 | yellow: 73
BFS | seed 45 | explored: 394 | path length: 97 | blue: 297 | yellow: 97
DFS | seed 45 | explored: 416 | path length: 105 | blue: 311 | yellow: 105
BFS | seed 49 | explored: 403 | path length: 157 | blue: 246 | yellow: 157
DFS | seed 49 | explored: 331 | path length: 225 | blue: 106 | yellow: 225


LIMITATIONS AND FUTURE WORK
1) All cells costs the same as there is no weighted search, might add A* or Dijkstra
2) The user can not control the size of the grid as it is declared and initialized in the main.cpp file

AUTHOR
Vipin Kumar - DSA Internship at TechnGlobal Pvt. Ltd.

