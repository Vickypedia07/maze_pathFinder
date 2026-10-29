#include "renderer.h"
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <vector>
#include <optional>
#include <string>
#include <iostream>

#include "maze.h"
#include "pathfinder.h"

namespace{

const int CELL = 24;
const int STEPS_PER_FRAME = 3;

enum class Phase {Idle , Exploring , DrawingPath};

sf::Color colorFor(Grid& g, Pos p , char mark){
    if(p==g.start) return sf::Color(46,204,113);
    if(p==g.goal) return sf::Color(231,76,60);
    if(g.isWall(p)) return sf::Color(44,62,80);
    if(mark == 2) return sf::Color(241,196,15);
    if(mark == 1) return sf::Color(93,173,226);
    return sf::Color(236, 240, 241);
}

}

void runVisualizer(Grid& gr , unsigned seed){
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(gr.cols()*CELL),static_cast<unsigned>(gr.rows()*CELL)}),
        "Pathfinding Visualizer - B: BFS, D: DFS, N: new maze, Esc: quit"
    );
    window.setFramerateLimit(60);

    std::vector<char> mark(gr.cols()*gr.rows(), 0);

    SearchResult result;
    Phase phase = Phase::Idle;
    std::size_t step = 0;
    std::string algo;
    

    auto startSearch = [&](bool useBfs){
        std::fill(mark.begin(),mark.end(),0);
        result = useBfs ? bfs(gr) : dfs(gr);
        algo = useBfs ? "BFS" : "DFS";
        step = 0 ;
        phase = Phase::Exploring;
    };

    auto newMaze = [&](){
        ++seed;
        generateMaze(gr,seed);
        addLoops(gr,seed+1000,0.05);
        std::fill(mark.begin(),mark.end(),0);
        phase = Phase::Idle;
    };

    sf::RectangleShape cell(sf::Vector2f(CELL-1,CELL-1));

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }else if(const auto* key = event->getIf<sf::Event::KeyPressed>()){
                if(key->code == sf::Keyboard::Key::Escape) window.close();
                else if(key->code == sf::Keyboard::Key::B) startSearch(true);
                else if(key->code == sf::Keyboard::Key::D) startSearch(false);
                else if(key->code == sf::Keyboard::Key::N) newMaze();
                
            }

        }

        if(phase == Phase::Exploring){
            for(int i = 0; i < STEPS_PER_FRAME && step < result.visitedOrder.size(); ++i,++step){
                Pos p = result.visitedOrder[step];
                mark[p.r*gr.cols()+p.c] = 1;
            }
            if(step >= result.visitedOrder.size()){
                step = 0;
                phase = Phase::DrawingPath;
            }
            
        }else if(phase == Phase::DrawingPath){
            for(int i =0 ; i<STEPS_PER_FRAME && step < result.path.size() ; ++i,++step){
                Pos p = result.path[step];
                mark[p.r*gr.cols()+p.c] = 2;

            }
            if(step >= result.path.size()){
                phase = Phase::Idle;
                std::size_t blue = std::count(mark.begin(), mark.end(), static_cast<char>(1));
                std::size_t yellow = std::count(mark.begin(), mark.end(), static_cast<char>(2));
                std::cout << algo << " | seed " << seed
                        << " | explored: " << result.visitedOrder.size()
                        << " | path length: " << result.path.size()
                        << " | blue: " << blue << " | yellow: " << yellow << "\n";
            }
        }

        window.clear(sf::Color::Black);
        for(int r=0 ; r<gr.rows() ; ++r){
            for(int c=0 ; c<gr.cols() ; ++c){
                cell.setPosition({static_cast<float>(c*CELL),static_cast<float>(r*CELL)});
                cell.setFillColor(colorFor(gr,Pos{r,c},mark[r*gr.rows()+c]));
                window.draw(cell);
            }
        }
        window.display();


    }

}