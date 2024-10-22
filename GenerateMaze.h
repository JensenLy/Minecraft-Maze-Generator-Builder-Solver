#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <array>
#include <mcpp/mcpp.h>
#include "Maze.h"
#include "env.h"

class GenerateMaze {

public:

GenerateMaze();
GenerateMaze(int x, int y, mcpp::Coordinate currCord);
void GenerateRandMaze();
void carveMaze();
int randomMove(int x, int y);
bool isValid(int x, int y, int dirX, int dirY);
void UserInputMaze(int x, int y);
void printMaze();
int getMazeHeight();
int getMazeWidth();
char** getMaze() const;
mcpp::Coordinate getCord();



private:
std::vector<std::vector<char>> maze;
std::array<int, 2> currLoc{};
std::vector<std::array<int, 2>> pathWay;
int width;
int height;
mcpp::Coordinate cord;

};

#endif