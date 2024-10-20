#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

class GenerateMaze {

public:

GenerateMaze(int x, int y);
// ~GenerateMaze();
// GenerateMazze(int x, int y);  // Constructor
// ~GenerateMazze();             // Destructor
void UserInputMaze(int x, int y);
// void GenerateRandomMaze(int x, int y);
// void carveMaze();
// int randomMove(int x, int y);
// bool isValid(int x, int y, int dirX, int dirY);
// void printMaze();
int getMazeHeight();
int getMazeWidth();
char** getMaze() const;
//std::vector<std::vector<char>> getMaze() const;

private:
//std::vector<std::vector<char>> maze;
char** maze;
int currLoc[2];
int lastDecision[2];
std::vector<std::vector<int[2]>> pathWay; 
int width;
int height;

};

#endif