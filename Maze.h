#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>

class Maze
{

public:
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

};




#endif //ASSIGN_MAZE_H
