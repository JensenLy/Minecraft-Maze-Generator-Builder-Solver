#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

class GenerateMaze {

public:

GenerateMaze(int x, int y);
void UserInputMaze(int x, int y);
// void GenerateRandomMaze(int x, int y);
// void carveMaze();
// int randomMove(int x, int y);
// bool isValid(int x, int y, int dirX, int dirY);
void printMaze();
int getMazeHeight();
int getMazeWidth();


private:
std::vector<std::vector<char>> maze;
int currLoc[2];
int lastDecision[2];
std::vector<std::vector<int[2]>> pathWay; 

};

#endif