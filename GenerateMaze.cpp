#include "GenerateMaze.h"
#include "Maze.h"
#include "env.h"
GenerateMaze::GenerateMaze(){}

GenerateMaze::GenerateMaze(int x, int y, mcpp::Coordinate currCord){

    //Create the maze according to the passed in paramaters
    maze.resize(x, std::vector<char>(y,'X'));
    this->width = x;
    this->height = y;
    this->cord = currCord;
}

// GenerateMaze::~GenerateMaze() {
//     for (int i = 0; i < width; ++i) {
//         delete[] maze[i];
//     }
//     delete[] maze;
// }

void GenerateMaze::GenerateRandMaze(){
    int i;
    int j;

    int x = width;
    int y = height;

    int numSpaces = 0;

    //Clear out empty spaces at odd i and j indexes
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){
            if(i % 2 != 0 && j % 2 != 0){
                maze[i][j] = ' ';
                numSpaces++;
            }
        }
    }

    //Generate 2 random numbers
    //1st number is for a random starting position in an empty cell on the x axis
    //2nd number is for a random choice of either the left or right side of the maze on the y axis
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(1, x/2);
    std::uniform_int_distribution<> distY(0, 1);

    int startX = distX(gen);
    int startY = distY(gen);

    //Depending on the 2nd random number place the start point on the left/right side of maze and put a '.' on the adjecent closest wall
    if(startY == 0){
        maze[startX*2-1][1] = '.';
        maze[startX*2-1][0] = '.';
        currLoc[0] = startX*2-1;
        currLoc[1] = 1;
    }
    else if (startY == 1){
        maze[startX*2-1][y-2] = '.';
        maze[startX*2-1][y-1] = '.';
        currLoc[0] = startX*2-1;
        currLoc[1] = y-2;
    }

}

void GenerateMaze::carveMaze(){
   pathWay.push_back(currLoc);

    while(!pathWay.empty()){
        int randChoice = randomMove(currLoc[0], currLoc[1]);

        int dirX = 0, dirY = 0;

        if(randChoice == 1){ // UP
            dirX = -1;
            dirY = 0;
        }
        else if(randChoice == 2){ // RIGHT
            dirX = 0;
            dirY = 1;
        }
        else if(randChoice == 3){ // DOWN
            dirX = 1;
            dirY = 0;
        }
        else if(randChoice == 4){ // LEFT
            dirX = 0;
            dirY = -1;
        }

        if(randChoice != 0){
            // Carve the wall between current cell and next cell
            maze[currLoc[0] + dirX][currLoc[1] + dirY] = '.';

            // Move to the next cell (skip the wall)
            currLoc[0] += 2 * dirX;
            currLoc[1] += 2 * dirY;

            pathWay.push_back({currLoc[0], currLoc[1]});
            maze[currLoc[0]][currLoc[1]] = '.'; // Mark new cell as visited
        } else {
            // Backtrack
            pathWay.pop_back();
            if (!pathWay.empty()) {
                currLoc = pathWay.back();
            }
        }
    }

}

int GenerateMaze::randomMove(int x, int y){
    std::vector<int> validMoves;
    //Get the curr location and for each up down etc check if they are valid. 

    // Move up
    if(isValid(x, y, -1, 0)){
        validMoves.push_back(1);
    }
    // Move right
    if(isValid(x, y, 0, 1)){
        validMoves.push_back(2);
    }
    // Move down
    if(isValid(x, y, 1, 0)){
        validMoves.push_back(3);
    }
    // Move left
    if(isValid(x, y, 0, -1)){
        validMoves.push_back(4);
    }

    if(validMoves.empty()){
        //Move back to previouse path
        validMoves.push_back(0);

    }

    //Shuffel the vector to get a random move
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(validMoves.begin(), validMoves.end(), gen);

    
    //Return the first int of the vector
    return validMoves[0];
}

bool GenerateMaze::isValid(int x, int y, int dirX, int dirY){
    bool validMove = false;

    int newX = x + 2 * dirX;
    int newY = y + 2 * dirY;
    
    if (newX > 0 && newX < static_cast<int>(maze.size()) && newY > 0 && newY < static_cast<int>(maze[0].size())){
        if(maze[newX][newY] == ' '){
            validMove = true;
        }
    }

    return validMove;

}

void GenerateMaze::UserInputMaze(int x, int y){
    std::string userInput;

    std::cout << "Enter the maze structure:" << std::endl;

    // Ignore any leftover characters from the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for(int i = 0; i < x; i++){
        std::getline(std::cin, userInput);

        for(int j = 0; j < y; j++) {
            maze[i][j] = userInput[j];
        }
    }

    std::cout << "Maze read successfully";
    
}

void GenerateMaze::printMaze(){
    int x = maze.size();
    int y = maze[1].size();

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}

int GenerateMaze::getMazeHeight(){
    return height;
}


int GenerateMaze::getMazeWidth(){
    return width;
}

char** GenerateMaze::getMaze() const {
    int rows = width;
    int cols = height;

    // Allocate memory for the row pointers
    char** mazeArray = new char*[rows];

    // Allocate memory for each row and copy the contents from the vector
    for (int i = 0; i < rows; ++i) {
        mazeArray[i] = new char[cols];
        for (int j = 0; j < cols; ++j) {
            mazeArray[i][j] = maze[i][j];  // Copy each element
        }
    }

    return mazeArray;
}

mcpp::Coordinate GenerateMaze::getCord(){
    return cord;
}
