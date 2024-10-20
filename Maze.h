#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>

class Maze
{

public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                        unsigned int zlen,
                                        bool mode, char** sourceMaze);
    ~Maze();
    // Maze(char**&maze);
    

private:
    /* data */
    char** maze;
    mcpp::Coordinate basePoint;
    unsigned int xlen;
    unsigned int zlen;
    bool mode;

};




#endif //ASSIGN_MAZE_H
