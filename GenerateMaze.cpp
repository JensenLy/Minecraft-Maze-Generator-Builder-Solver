#include "GenerateMaze.h"

GenerateMaze::GenerateMaze(int x, int y){
    maze.resize(x, std::vector<char>(y,'X'));
}

void GenerateMaze::UserInputMaze(int x, int y){
    std::string userInput;

    std::cout << "Enter the maze structure:" << std::endl;

    for(int i = 0; i < x; i++){
        std::getline(std::cin, userInput);

        for(int j = 0; j < y; j++) {
            maze[i][j] = userInput[j];
        }
    }

    std::cout << "Maze read successfully";
    
}

// void GenerateMaze::GenerateRandomMaze(int x, int y){

//     //Create the maze according to the passed in paramaters
//     maze.resize(x, std::vector<char>(y,'X'));

//     int i;
//     int j;

//     int numSpaces = 0;
//     int numSpaceCounted = 0;


//     //Clear out empty spaces at odd i and j indexes
//     for(i = 0; i < x; i++){
//         for(j = 0; j < y; j++){
//             if(i % 2 != 0 && j % 2 != 0){
//                 maze[i][j] = ' ';
//                 numSpaces++;
//             }
//         }
//     }

//     //Generate 2 random numbers
//     //1st number is for a random starting position in an empty cell on the x axis
//     //2nd number is for a random choice of either the left or right side of the maze on the y axis
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     std::uniform_int_distribution<> distX(0, x/2);
//     std::uniform_int_distribution<> distY(0, 1);

//     int startX = distX(gen);
//     int startY = distY(gen);

//     //Depending on the 2nd random number place the start point on the left/right side of maze and put a '.' on the adjecent closest wall
//     if(startY == 0){
//         maze[startX*2-1][1] = '*';
//         maze[startX*2-1][0] = '.';
//         currLoc[0] = startX*2-1;
//         currLoc[1] = 1;
//     }
//     else if (startY == 1){
//         maze[startX*2-1][y-2] = '*';
//         maze[startX*2-1][y-1] = '.';
//         currLoc[0] = startX*2-1;
//         currLoc[1] = y-2;
//     }


// }

// void GenerateMaze::carveMaze(){

//     // while(){

//     //     int randChoice = randomMove(currLoc[0], currLoc[1]);

//     //     if(randChoice == 1){
//     //         maze[currLoc[0]][currLoc[1]+1] = '.';
//     //     }
//     //     else if(randChoice == 2){
//     //         maze[currLoc[0]+1][currLoc[1]] = '.';
//     //     }
//     //     else if(randChoice == 3){
//     //         maze[currLoc[0]][currLoc[1]-1] = '.';
//     //     }
//     //     else if(randChoice == 4){
//     //         maze[currLoc[0]-1][currLoc[1]] = '.';
//     //     }
//     //     else if(randChoice == 0){
//     //         currLoc[0] = lastDecision[0];
//     //         currLoc[1] = lastDecision[1];
//     //     }

//     // }
    
// }

// int GenerateMaze::randomMove(int x, int y){
//     std::vector<int> validMoves;
//     //Get the curr location and for each up down etc check if they are valid. 

//     //Move up
//     if(isValid(x,y,0,1)){
//         //If they are valid then put into a vector 
//         validMoves.push_back(1);
//     }

//     //Move right
//     if(isValid(x,y,1,0)){ 
//         validMoves.push_back(2);
//     }

//     //Move down
//     if(isValid(x,y,0,-1)){ 
//         validMoves.push_back(3);
//     }

//     //Move left
//     if(isValid(x,y,-1,0)){ 
//         validMoves.push_back(4);
//     }

//     if(validMoves.size() == 0){
//         validMoves.push_back(0);
//     }

//     //Shuffel the vector to get a random move
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::shuffle(validMoves.begin(), validMoves.end(), gen);

    
//     //Return the first int of the vector
//     return validMoves[0];
// }

// bool GenerateMaze::isValid(int x, int y, int dirX, int dirY){
//     bool validMove = true;
    
//     if(!(x+dirX > 0 && x+dirX < maze.size() - 1 && y+dirY > 0 && y+dirY < maze[0].size() - 1)){
//         validMove = false;
//     }

//     if(maze[x+dirX][y+dirY] == '.'){
//         validMove = false;
//     }

//     return validMove;

// }

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
    return maze[0].size();
}


int GenerateMaze::getMazeWidth(){
    return maze.size();
}
