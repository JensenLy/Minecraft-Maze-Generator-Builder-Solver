#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>
#include "LinkedListCoordinate.h"

class Maze
{

public:
    Maze();
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                        unsigned int zlen,
                                        bool mode, char** sourceMaze);
    ~Maze();
    // Maze(char**&maze);
    void exitCleanUp();
    void terraformTerrain();
    void storeTerrain();
    void buildMaze();
    void scanTerrain();
    
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
    int maxheight;
    mcpp::Coordinate currCoord;
    mcpp::BlockType currBlock;


};




#endif //ASSIGN_MAZE_H
