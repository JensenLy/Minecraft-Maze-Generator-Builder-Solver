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

class GenerateMaze {

public:

GenerateMaze();
GenerateMaze(int x, int y, mcpp::Coordinate currCord);

//Getting and validating user's input
GenerateMaze ValidateUserMazeSize();
void ValidateUserMazeInput();

//Fixing the maze from the user input (Extension)
void fixUserInput();
char removeIsolation();
char removeLoop();
std::array<int, 2> findEntrance();
std::vector<std::vector<char>> floodFill(std::array<int, 2> start, char search);
void floodFillHelper(std::vector<std::vector<char>>& floodedMaze, int x, int y,
char search);

//Generating the maze
void GenerateRandMaze();
void GenerateTestMaze();
void carveMaze();
void carveTestMaze();
int randomMove(int x, int y, char isNormal);
bool isValid(int x, int y, int dirX, int dirY, char isNormal);


void printMaze();


int getMazeHeight();
int getMazeWidth();


char** getMaze() const;
std::vector<std::vector<char>> getMazeVec() const;
mcpp::Coordinate getCord();
void setMaze(std::vector<std::vector<char>> maze);



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