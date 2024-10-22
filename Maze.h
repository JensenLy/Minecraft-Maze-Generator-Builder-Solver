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
    void ReadEnvSize(int &envLength, int &envWidth);
    void readEnvStdin(char **EnvStruct, int length, int width);
    void ReadBuildLocation(int &build_x, int &build_y, int &build_z);
    void exitCleanUp();

private:
    /* data */
    char** maze;
    mcpp::Coordinate basePoint;
    unsigned int xlen;
    unsigned int zlen;
    bool mode;
    mcpp::MinecraftConnection mc;
    LinkedListCoordinate list;
    int build_x;
    int build_y;
    int build_z;


};




#endif //ASSIGN_MAZE_H
