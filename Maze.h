#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>
#include "LinkedListCoordinate.h"
#include "GenerateMaze.h"

class Maze
{

public:
    Maze();
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                        unsigned int zlen,
                                        bool mode, char** sourceMaze);
    ~Maze();
    void scanTerrain();
    void storeTerrain();
    void terraformTerrain();
    void buildMaze();
    void exitCleanUp();
    
    void scanTerrainEnhancement();
    void buildMazeEnhancement();
    void exitCleanUpEnhancement();

private:
    /* data */
    char** maze;
    mcpp::Coordinate basePoint;
    unsigned int xlen;
    unsigned int zlen;
    bool mode;
    mcpp::MinecraftConnection mc;
    LinkedListCoordinate list;
    mcpp::BlockType block;
    int build_x;
    int build_y;
    int build_z;
    int tempy;
    int counter;
    int maxHeight;
    mcpp::Coordinate currCoord;
    mcpp::BlockType currBlock;
    mcpp::Coordinate playerOrg;
    bool EnhancementMode = false;
    std::vector<std::vector<char>> vec;


};




#endif //ASSIGN_MAZE_H
