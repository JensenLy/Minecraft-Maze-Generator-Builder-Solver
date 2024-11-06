#include "GenerateMaze.h"

GenerateMaze::GenerateMaze(){}

GenerateMaze::GenerateMaze(int x, int y, mcpp::Coordinate currCord){

    //Create the maze according to the passed in paramaters
    maze.resize(x, std::vector<char>(y,'X'));
    this->width = x;
    this->height = y;
    this->cord = currCord;
    
}

GenerateMaze GenerateMaze::ValidateUserMazeSize(){
    bool isDone = false; 
    bool correctInput = false;
    int userX = 0;
    int userY = 0;
    mcpp::Coordinate playerOrg;
    std::string doneInput;

    std::cout << "In Minecraft navigate to where you want the maze to be in "
    << "Minecraft and type - done:" << std::endl;
    std::cin >> doneInput;

    // While the user does not input "done"
    while(!isDone){
        if(doneInput == "done"){
            isDone = true;
        }
        else{
            std::cout << "In Minecraft navigate to where you want the maze to "
            << "be in Minecraft and type - done:" << std::endl;
            std::cin >> doneInput;
        }
    }

    // Clear any extra user inputs from buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get the players position in Mineraft they want to build the maze
    playerOrg = mc.getPlayerPosition();
    playerOrg.y = (mc.getHeight(playerOrg.x, playerOrg.z))+1;

    std::cout << "Enter the length and width of maze" << std::endl;

    // Check the user entered exactly 2 odd int's otherwise prompt them again
    while(!correctInput){
        std::string whInput;
        std::getline(std::cin, whInput);

        std::istringstream iss(whInput);
        int x, y;
        if (iss >> x >> y) {
            if (x % 2 != 0 && y % 2 != 0 && x > 0 && y > 0) {
                correctInput = true;
                userX = x;
                userY = y;

            } else {
                std::cout << "Please enter 2 **odd** values greater than 0 for "
                << "the length and width of the maze." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter two integer"
            << " values." << std::endl;
        }
    }

    /* 
     * Once validated the user's input, call the constructor and create the
     * GenerateMaze object to return to mazeRunner and associate with the user's
     * Maze.
     */
    return GenerateMaze(userX, userY, playerOrg);

}

void GenerateMaze::ValidateUserMazeInput() {
    std::string userInput;
    bool isValidInput = false;

    int x = width;
    int y = height;

    std::cout << "Enter the maze structure (only 'X' and '.'): " << std::endl;

    //For each line the user input's check it is correct length and only 'X'&'.'
    for (int i = 0; i < x; i++) {
        isValidInput = false;

        while (!isValidInput) {
            std::getline(std::cin, userInput);

            // Check input length
            if (userInput.size() != static_cast<size_t>(y)) {
                std::cout << "Please enter exactly " << y << " characters." 
                << std::endl;
            } else {
                // Assume input is valid, check each character
                isValidInput = true;

                for (char c : userInput) {
                    if (c != 'X' && c != '.') {
                        isValidInput = false; 
                    }
                }

                //If the input is invalid, indicate to the user why
                if(!isValidInput){
                    std::cout << "Please enter only 'X' and '.' for the"
                    << " maze structure." << std::endl;
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

void GenerateMaze::fixUserInput(){
    // Call remove isolation first to check if there are any isolations to fix
    char fixedIso = this->removeIsolation();
    bool noProblems = false;

    // If there is nothing to be fixed then set no Problems true for later use
    if(fixedIso == '0'){
        noProblems = true;
    }

    // While there isolations still exist in the maze
    while(fixedIso != '0' && fixedIso != '2'){
        fixedIso = this->removeIsolation();

        // Once all isolations are removed, let the user know they are fixed
        if(fixedIso == '0'){
        std::cout << "Isolations in your maze have been fixed!" << std::endl;
        }
    }

    // Call the remove loop to check if there are any loops to be fixed.
    char fixedLoop = this->removeLoop();

    // If there are no loops and no isolations, let the user know.
    if(noProblems && fixedLoop == '0'){
        std::cout << "Your maze has no problems!" << std::endl;
    }

    // While loops still exist in the maze
    while(fixedLoop != '0' && fixedLoop != '2'){
        fixedLoop = this->removeLoop();

        // Once all loops are fixed, let the user know they are fixed
        if(fixedLoop == '0'){
        std::cout << "Loops in your maze have been fixed!" << std::endl;
        }
    }

    // If there are loops or isolations that cannot be fixed, tell the user
    if(fixedIso == '2' || fixedLoop == '2'){
        std::cout << "Your maze cannot be completely fixed!" << std::endl;
    }

    this->printMaze();

}

char GenerateMaze::removeIsolation(){

    // Find the entrance to the users maze
    std::array<int, 2> entrance = this->findEntrance();

    // Create a new 2D maze vector that can be used for flooding
    // Call the floodFill function to flood fill on the '.'
    std::vector<std::vector<char>> floodedMaze = this->floodFill(entrance, '.');

    int x = maze.size();
    int y = maze[1].size();
    int randChoice;
    int dirX = 0;
    int dirY = 0;
    int moveX;
    int moveY;
    char foundIsolation = '0';
    int i = 0;

    // Search the flooded maze until you find '.' (Meaning there is a isolation)
    // Using a while loop because when a isolation is found and fixed, then the
    // - function needs to exit
    while(foundIsolation == '0' && i < x){
        for(int j = 0; j < y; j++){
            if(floodedMaze[i][j] == '.'){
                randChoice = randomMove(i, j, '0');

                // Move UP
                if(randChoice == 1){
                    dirX = -1;
                    dirY = 0;
                }
                // Move RIGHT
                else if(randChoice == 2){
                    dirX = 0;
                    dirY = 1;
                }
                // Move DOWN
                else if(randChoice == 3){
                    dirX = 1;
                    dirY = 0;
                }
                // Move LEFT
                else if(randChoice == 4){
                    dirX = 0;
                    dirY = -1;
                }

                // If there is valid move to fix the isolation, update the maze
                if(randChoice != 0){
                    moveX = dirX*2 + i;
                    moveY = dirY*2 + j;

                    maze[dirX+i][dirY+j] = '.';
                    maze[moveX][moveY] = '.';
                    foundIsolation = 1;
                }
                else{
                    // Return 2 which means there is no valid moves and -
                    // - isolation cannot be fixed
                    foundIsolation = '2';
                }

            }
        }
        i++;
    }

    //Return the outcome of finding the Isolation to understand what to do next
    return foundIsolation;
}

char GenerateMaze::removeLoop(){

    std::array<int, 2> entrance = {0, 0};
    std::vector<std::vector<char>> floodedMaze = this->floodFill(entrance, 'X');

    int x = maze.size();
    int y = maze[1].size();
    int randChoice;
    int dirX = 0;
    int dirY = 0;
    int moveX;
    int moveY;
    char foundIsolation = '0';
    int i = 0;

    // Search the flooded maze until you find '.' (Meaning there is a loop)
    // Using a while loop because when a loop is found and fixed, then the -
    // - function needs to exit
    while(foundIsolation == '0' && i < x){
        for(int j = 0; j < y; j++){
            if(floodedMaze[i][j] == 'X'){
                randChoice = randomMove(i, j, '2');

                // Move UP
                if(randChoice == 1){
                    dirX = -1;
                    dirY = 0;
                }
                // Move RIGHT
                else if(randChoice == 2){
                    dirX = 0;
                    dirY = 1;
                }
                // Move DOWN
                else if(randChoice == 3){
                    dirX = 1;
                    dirY = 0;
                }
                // Move LEFT
                else if(randChoice == 4){
                    dirX = 0;
                    dirY = -1;
                }

                // If there is a valid move to fix loop, update the maze
                if(randChoice != 0){
                    moveX = dirX*2 + i;
                    moveY = dirY*2 + j;

                    maze[dirX+i][dirY+j] = 'X';
                    maze[moveX][moveY] = 'X';
                    foundIsolation = '1';
                }
                else{
                    // Return 2 which means there is no valid moves and loop
                    // Cannot be fixed
                    foundIsolation = '2';
                }

            }
        }
        i++;
    }

    // Return the outcome of finding the Isolation to understand what to do next
    return foundIsolation;

}

std::vector<std::vector<char>> GenerateMaze::floodFill(std::array<int, 2> start,
char search) {
    // Create a copy of the maze to work with
    std::vector<std::vector<char>> floodedMaze = maze;

    // Get the starting coordinates to start the flood
    int startX = start[0];
    int startY = start[1];

    // Call the flood fill to fill the floodedMaze
    floodFillHelper(floodedMaze, startX, startY, search);

    // Return the flooded maze to identify where there are isolations/loops
    return floodedMaze;
}       

void GenerateMaze::floodFillHelper(std::vector<std::vector<char>>& floodedMaze, 
int x, int y, char search) {
    // Initialize a flag to control recursion
    bool shouldContinue = true;

    // Check boundary conditions and whether the current cell matches the - 
    // - search char
    if (x < 0 || x >= static_cast<int>(floodedMaze.size()) || y < 0 ||
        y >= static_cast<int>(floodedMaze[0].size())) {
        shouldContinue = false;
    } else if (floodedMaze[x][y] != search) {
        shouldContinue = false;
    }

    if (shouldContinue) {
        // Flood the maze with 0's to indicate that cell has been flodded
        floodedMaze[x][y] = '0';

        // Recursively call flood fill on neighboring cells
        floodFillHelper(floodedMaze, x + 1, y, search);
        floodFillHelper(floodedMaze, x - 1, y, search);
        floodFillHelper(floodedMaze, x, y + 1, search);
        floodFillHelper(floodedMaze, x, y - 1, search);
    }
    // Only one return statement at the end (implicit for void function)
}

std::array<int, 2> GenerateMaze::findEntrance(){
    std::array<int, 2> entrance = {0,0};

    // Check all sides for the entrance of the users inputed maze
    for(int i = 0; i < width; i++){
        if(maze[i][0] == '.'){
            entrance[0] = i;
        }
        else if(maze[i][height-1] == '.'){
            entrance[0] = i;
            entrance[1] = height-1;
        }    
    }

    // Return the x and y of where the entrance is in the maze
    return entrance;

}

void GenerateMaze::printMaze(){
    //Get the dimensions of maze to print
    int x = maze.size();
    int y = maze[1].size();

    //Print the formatting of the maze
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "Base Point: " << cord << std::endl;
    std::cout << "Structure: "  << std::endl;

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "**End Printing Maze**" << std::endl;

}

void GenerateMaze::GenerateRandMaze(){
    int i;
    int j;
    int x = width;
    int y = height;
    int numSpaces = 0;

    // Clear out empty spaces at odd i and j indexes to get maze ready to carve
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){
            if(i % 2 != 0 && j % 2 != 0){
                maze[i][j] = ' ';
                numSpaces++;
            }
        }
    }

    /*
     * Generate 2 random numbers for starting location
     * 1st number is for a random starting position in an empty cell on the x 
     * axis
     * 2nd number is for a random choice of either the left or right side of the
     * maze on the y axis
     */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(1, x/2);
    std::uniform_int_distribution<> distY(0, 1);
    int startX = distX(gen);
    int startY = distY(gen);

    /* 
     * Use start X to indicate the starting position of the entrance on X axis
     * Use start Y to indicate the starting position of the entrance on Y axis
     * Mark '.' where this is, also set current location to this position
     */
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

    // Clear out empty spaces at odd i and j indexes to get maze ready to carve
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){
            if(i % 2 != 0 && j % 2 != 0){
                maze[i][j] = ' ';
                numSpaces++;
            }
        }
    }

    // Set the entrance to x[1], y[0] as the test mode required
    maze[1][1] = '.';
    maze[1][0] = '.';
    currLoc[0] = 1;
    currLoc[1] = 1;

    // Set the players starting cord as the test mode required
    cord.x = 4848;
    cord.y = 71;
    cord.z = 4369;
    mc.setPlayerPosition(cord);

}

void GenerateMaze::carveMaze(){
   
    // Add the currentlocation to the pathway that was set in the generation of
    // the maze
    pathWay.push_back(currLoc);

    // This mode is used in the randomMove function
    char validMode = '1';

    // Keep making moves until the pathway has recursed back to nothing, meaning
    // the whole maze has been carved
    while(!pathWay.empty()){

        // Random move gets a move that is random and is valid
        int randChoice = randomMove(currLoc[0], currLoc[1], validMode);

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

        // If there is a valid move to be made
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
            // Backtrack one move
            pathWay.pop_back();
            if (!pathWay.empty()) {
                currLoc = pathWay.back();
            }
        }
    }

}

void GenerateMaze::carveTestMaze(){
    // Add the current location to the pathway
    pathWay.push_back(currLoc);

    // This mode is used in the randomMove function
    char validMode = '1';

    // Keep making moves until the pathway has recursed back to nothing, meaning
    // the whole maze has been carved
    while(!pathWay.empty()){
        bool moved = false;
        int dir = 1;

        // Make moves up, right, left, down as specified in test mode requirment
        while(dir <= 4 && !moved){
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

            // If the move that was made due to test mode is valid, carve
            if (isValid(currLoc[0], currLoc[1], dirX, dirY, validMode)) {
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
            }

            //Increment the direction to next one
            ++dir;
        }

        if (!moved) {
            // No a valid moves, backtrack to previous cell
            pathWay.pop_back();
            if (!pathWay.empty()) {
                currLoc = pathWay.back();
            }
        }
    }

}

int GenerateMaze::randomMove(int x, int y, char isNormal){
    
    // Vector to store all the valid moves
    std::vector<int> validMoves; 

    // Check all moves to see if that move is valid, if it is put into vector of
    // valid moves

    // Move up
    if(isValid(x, y, -1, 0, isNormal)){
        validMoves.push_back(1);
    }
    // Move right
    if(isValid(x, y, 0, 1, isNormal)){
        validMoves.push_back(2);
    }
    // Move down
    if(isValid(x, y, 1, 0, isNormal)){
        validMoves.push_back(3);
    }
    // Move left
    if(isValid(x, y, 0, -1, isNormal)){
        validMoves.push_back(4);
    }

    if(validMoves.empty()){
        //No Valid moves
        validMoves.push_back(0);
    }

    //Shuffel the vector to get a random move
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(validMoves.begin(), validMoves.end(), gen);

    
    //Return the first int of the vector
    return validMoves[0];
}

bool GenerateMaze::isValid(int x, int y, int dirX, int dirY, char isNormal){
    bool validMove = false;

    // Set the var's for where the new move is
    int newX = x + 2 * dirX;
    int newY = y + 2 * dirY;
    
    // Check if the move is in bounds of the dimensions of the maze
    if (newX > 0 && newX < static_cast<int>(maze.size()) && newY > 0 && 
        newY < static_cast<int>(maze[0].size())){
        
        // Normal mode = 1 (Used for normal recursion of carving maze)
        if(isNormal == '1'){
            if(maze[newX][newY] == ' ' && maze[x + dirX][y + dirY] != '\\'){
                validMove = true;
            }
        }
        // Isolation mode = 0 (Used for checking moves for fixing isolation)
        else if(isNormal == '0'){
            if(maze[newX][newY] == '.'){
                validMove = true;
            }
        }
        // Loop mode = 2 (Used for checking moves for fixing loop)
        else if(isNormal == '2'){
            if(maze[newX][newY] == 'X'){
                validMove = true;
            }
        }
    }

    // Return the bool of if the move was valid
    return validMove;

}

int GenerateMaze::getMazeHeight(){
    return height;
}

int GenerateMaze::getMazeWidth(){
    return width;
}

char** GenerateMaze::getMaze() const {
    // This function converts the maze 2D vector into 2D char pointer, allowing
    // teammate to generate the maze in minecraft

    int rows = width;
    int cols = height;

    // Allocate memory for the row pointers
    char** mazeArray = new char*[rows];

    // Allocate memory for each row and copy the contents from the vector
    for (int i = 0; i < rows; ++i) {
        mazeArray[i] = new char[cols];
        for (int j = 0; j < cols; ++j) {
            // Copy each element
            mazeArray[i][j] = maze[i][j];
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
