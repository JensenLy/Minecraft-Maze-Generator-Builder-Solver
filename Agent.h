#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread> 
#include <vector>
#include <algorithm>
#include <cmath>

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)
#define acacia mcpp::Blocks::ACACIA_WOOD_PLANK

class Agent
{

public:
    Agent();
    ~Agent();

    bool checkNorth(mcpp::BlockType block); 
    bool checkEast(mcpp::BlockType block); 
    bool checkSouth(mcpp::BlockType block); 
    bool checkWest(mcpp::BlockType block); 

    void goNorth(); 
    void goEast(); 
    void goSouth(); 
    void goWest();

    void reportStep(); 
    bool isDone(); 
    void vecRemoveDups(std::vector<mcpp::Coordinate> &vec);
    void manualSolve(mcpp::Coordinate basePoint, int row, int col, char** maze);
    void manualSolveTest(mcpp::Coordinate playerOrg, int row, int col, char** maze);
    void initialiseSolve(); 
    void initialiseSolveTest(); 
    void rightHandSolve(); 
    void bfsSolve(); 

    
private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate currPos; 
    int step; 
    int orientation; 
    bool keepGoing; 

};



#endif //ASSIGN3_AGENT_H