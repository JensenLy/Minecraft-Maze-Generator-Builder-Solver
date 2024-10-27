#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <array>
#include <limits>
#include <sstream>
#include <string>
#include <mcpp/mcpp.h>
#include "Maze.h"
#include "env.h"

class GenerateMaze {

public:

GenerateMaze();
GenerateMaze(int x, int y, mcpp::Coordinate currCord);


GenerateMaze ValidateUserMazeSize();
void ValidateUserMazeInput();


void GenerateRandMaze();
void GenerateTestMaze();
void carveMaze();
void carveTestMaze();
int randomMove(int x, int y);
bool isValid(int x, int y, int dirX, int dirY);


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
mcpp::MinecraftConnection mc;

};

#endif