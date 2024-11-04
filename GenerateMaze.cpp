#include "GenerateMaze.h"
#include "Maze.h"
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

GenerateMaze GenerateMaze::ValidateUserMazeSize(){
    bool isDone = false; 
    bool correctInput = false;
    int userX = 0;
    int userY = 0;
    mcpp::Coordinate playerOrg;
    std::string doneInput;

    std::cout << "In Minecraft navigate to where you want the maze to be in Minecraft and type - done:" << std::endl;
    std::cin >> doneInput;

    while(!isDone){
        if(doneInput == "done"){
            isDone = true;
        }
        else{
            std::cout << "In Minecraft navigate to where you want the maze to be in Minecraft and type - done:" << std::endl;
            std::cin >> doneInput;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    playerOrg = mc.getPlayerPosition();
    playerOrg.y = (mc.getHeight(playerOrg.x, playerOrg.z))+1;

    std::cout << "Enter the length and width of maze" << std::endl;

    while(!correctInput){
        std::string whInput;
        std::getline(std::cin, whInput);

        std::istringstream iss(whInput);
        // Check if exactly two integers were entered
        int x, y;
        if (iss >> x >> y) {
            if (x % 2 != 0 && y % 2 != 0 && x > 0 && y > 0) {
                correctInput = true;
                userX = x;
                userY = y;

            } else {
                std::cout << "Please enter 2 **odd** values greater than 0 for the length and width of the maze." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter two integer values." << std::endl;
        }
    }

    return GenerateMaze(userX, userY, playerOrg);

}

void GenerateMaze::ValidateUserMazeInput() {
    std::string userInput;
    bool isValidInput = false;

    int x = width;
    int y = height;

    std::cout << "Enter the maze structure (only 'X' and '.'): " << std::endl;

    for (int i = 0; i < x; i++) {
        // Reset for each row
        isValidInput = false;

        while (!isValidInput) {
            std::getline(std::cin, userInput);

            // Check input length
            if (userInput.size() != static_cast<size_t>(y)) {
                std::cout << "Please enter exactly " << y << " characters." << std::endl;
            } else {
                // Assume input is valid, check each character
                isValidInput = true;

                for (char c : userInput) {
                    if (c != 'X' && c != '.') {
                        std::cout << "Please enter only 'X' and '.' for the maze structure." << std::endl;
                        isValidInput = false;  // Mark input as invalid
                        // No `break` needed; just let the loop continue to next character
                    }
                }

                // If input is still valid, copy it to the maze
                if (isValidInput) {
                    for (int j = 0; j < y; j++) {
                        maze[i][j] = userInput[j];
                    }
                }
            }
        }
    }

    std::cout << "Maze read successfully." << std::endl;
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

void GenerateMaze::GenerateTestMaze(){
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

    maze[1][1] = '.';
    maze[1][0] = '.';
    currLoc[0] = 1;
    currLoc[1] = 1;

    cord.x = 4848;
    cord.y = 71;
    cord.z = 4369;
    mc.setPlayerPosition(cord);

}

void GenerateMaze::carveMaze(){
   pathWay.push_back(currLoc);

    while(!pathWay.empty()){
        int randChoice = randomMove(currLoc[0], currLoc[1]);

        int dirX = 0, dirY = 0;

        // UP
        if(randChoice == 1){
            dirX = -1;
            dirY = 0;
        }
        // RIGHT
        else if(randChoice == 2){
            dirX = 0;
            dirY = 1;
        }
        // DOWN
        else if(randChoice == 3){
            dirX = 1;
            dirY = 0;
        }
        // LEFT
        else if(randChoice == 4){
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
            // Mark new cell as visited
            maze[currLoc[0]][currLoc[1]] = '.';
        } else {
            // Backtrack
            pathWay.pop_back();
            if (!pathWay.empty()) {
                currLoc = pathWay.back();
            }
        }
    }

}

void GenerateMaze::carveTestMaze(){
    pathWay.push_back(currLoc);

    while(!pathWay.empty()){
        bool moved = false;

        for(int dir = 1; dir <= 4; ++dir){

            int dirX;
            int dirY;
        
            // UP
            if(dir == 1){
                dirX = -1;
                dirY = 0;
            }
            // RIGHT
            else if(dir == 2){
                dirX = 0;
                dirY = 1;
            }
            // DOWN
            else if(dir == 3){
                dirX = 1;
                dirY = 0;
            }
            // LEFT
            else if(dir == 4){
                dirX = 0;
                dirY = -1;
            }

            if (isValid(currLoc[0], currLoc[1], dirX, dirY)) {
                // Carve the wall between current and next cell
                maze[currLoc[0] + dirX][currLoc[1] + dirY] = '.';

                // Move to the next cell (skip the wall)
                currLoc[0] += 2 * dirX;
                currLoc[1] += 2 * dirY;

                // Add new location to path
                pathWay.push_back({currLoc[0], currLoc[1]});
                // Mark the new cell as visited
                maze[currLoc[0]][currLoc[1]] = '.';

                moved = true;
                break;  // Stop checking directions once we move
            }
        }

        if (!moved) {
            // No valid moves, backtrack to previous cell
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
        if(maze[newX][newY] == ' ' && maze[x + dirX][y + dirY] != '\\'){
            validMove = true;
        }
    }

    return validMove;

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

std::vector<std::vector<char>> GenerateMaze::getMazeVec() const {
    return maze;
}

mcpp::Coordinate GenerateMaze::getCord(){
    return cord;
}

void GenerateMaze::setMaze(std::vector<std::vector<char>> maze) {
    this->maze = maze;
}
