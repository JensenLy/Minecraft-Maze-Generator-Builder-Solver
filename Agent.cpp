#include "Agent.h"

Agent::Agent()
{
    step = 0; 
    orientation = 0; 
    keepGoing = true; 
    currPos = mc.getPlayerPosition(); 
}

Agent::~Agent()
{
}

bool Agent::checkNorth(mcpp::BlockType block) {
    // Checks the tile on the X-Positive, if it's the same as the one on the
    // parameter, returns false (which means it's a wall, not free to move),
    // otherwises returns true (which means clear, free to move); 
    bool clear = false; 
    mcpp::BlockType tempBlock; 

    // move the temporary position on X-Positive
    mcpp::Coordinate tempPos = currPos + MOVE_XPLUS; 

    // getHeight is used for dealing with uneven surfaces. 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z);

    // get the blocktype
    tempBlock = mc.getBlock(tempPos); 

    // comparison
    if (tempBlock != block){
        clear = true;  
    }
    return clear; 
}

bool Agent::checkEast(mcpp::BlockType block) {
    // same as checkNorth(), just Z-Positive instead of X-Positive
    bool clear = false; 
    mcpp::BlockType tempBlock; 
    mcpp::Coordinate tempPos = currPos + MOVE_ZPLUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
    tempBlock = mc.getBlock(tempPos); 
    tempBlock = mc.getBlock(tempPos); 

    if (tempBlock != block){
        clear = true;  
    }
    return clear; 
}

bool Agent::checkSouth(mcpp::BlockType block) {
    // same as checkNorth(), just X-Negative instead of X-Positive
    bool clear = false; 
    mcpp::BlockType tempBlock; 
    mcpp::Coordinate tempPos = currPos + MOVE_XMINUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
    tempBlock = mc.getBlock(tempPos); 
    tempBlock = mc.getBlock(tempPos); 

    if (tempBlock != block){
        clear = true;  
    }
    return clear; 
}

bool Agent::checkWest(mcpp::BlockType block) {
    // same as checkNorth(), just Z-Negative instead of X-Positive
    bool clear = false; 
    mcpp::BlockType tempBlock; 
    mcpp::Coordinate tempPos = currPos + MOVE_ZMINUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
    tempBlock = mc.getBlock(tempPos); 
    tempBlock = mc.getBlock(tempPos); 
    if (tempBlock != block){
        clear = true;  
    }
    return clear; 
}

void Agent::goNorth() { 
    mc.setBlock(currPos, mcpp::Blocks::AIR); // clear the current lime carpet
    currPos = currPos + MOVE_XPLUS; // step 

    // getHeight for uneven surfaces
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1;

    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET); // place the new carpet
} 

void Agent::goEast() {
    // same as goNorth(), just Z-Positive instead of X-Positive
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZPLUS; 
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goSouth() {
    // same as goNorth(), just X-Negative instead of X-Positive
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_XMINUS; 
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goWest() {
    // same as goNorth(), just Z-Negative instead of X-Positive
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZMINUS; 
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::reportStep() {
    // Prints the current step, coordinate of currPos
    step++; 
    std::string reportStep = "Step[" + std::to_string(step) + "]:"; 
    reportStep += " (" + std::to_string(currPos.x);
    reportStep += ", " + std::to_string(currPos.y);
    reportStep += ", " + std::to_string(currPos.z) + ")";
    std::cout << reportStep << std::endl; 
}

bool Agent::isDone() { 
    // returns true when there's a blue carpet around the current position. 
    bool isDone = false; 

    // tempPos is used for getHeight,
    // which is used for uneven surfaces. 
    mcpp::Coordinate tempPos; 

    tempPos = currPos + MOVE_XPLUS; //step on the X-Positive
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z) + 1; 
    if (mc.getBlock(tempPos) == mcpp::Blocks::BLUE_CARPET){ //checks for blue
        isDone = true;  
    }

    tempPos = currPos + MOVE_ZPLUS; //similar as above
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z) + 1; 
    if (mc.getBlock(tempPos) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
    }

    tempPos = currPos + MOVE_XMINUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z) + 1; 
    if (mc.getBlock(tempPos) == mcpp::Blocks::BLUE_CARPET){
        isDone = true;  
    }

    tempPos = currPos + MOVE_ZMINUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z) + 1; 
    if (mc.getBlock(tempPos) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
    }

    return isDone; 
}

void Agent::vecRemoveDups(std::vector<mcpp::Coordinate> &vec){
    vec.erase(std::unique(vec.begin(), vec.end()),vec.end());
}

void Agent::manualSolve\
(mcpp::Coordinate playerOrg, int row, int col, char** maze){
    // random seed for more randomness (I know it's not true random :'> )
    srand(rand()); 
    int rowRand = 0; 
    int colRand = 0; 
    while (keepGoing){ 
        rowRand = rand() % row; // random range from 0 to row
        colRand = rand() % col; // random range from 0 to column

        if (maze[rowRand][colRand] == '.') { // checks if it is a wall or not
            keepGoing = false; 

            // Set the coord for teleporting.
            // The results = current coord of the player + the point relative 
            // to (0,0) in the structure of the maze.  
            currPos = playerOrg + mcpp::Coordinate(rowRand, 0 , colRand);

            mc.setPlayerTilePosition(currPos); 
        }
    }
}

void Agent::manualSolveTest\
(mcpp::Coordinate playerOrg, int row, int col, char** maze){ 
    double furthest = 0.0; 
    double currDist = 0.0; 
    mcpp::Coordinate farPoint(0, 0, 0); 

    // this function will uses the formula to calculate the distance between
    // 2 points: sqrt((x2 – x1)^2 + (y2 – y1)^2)
    // But since the base point of the maze structure is (0,0), I simplified
    // it to sqrt(x^2 + y^2)
    for (int i = 0; i < row; i++){ 
        for (int j = 0; j < col; j++){ 
            if (maze[i][j] == '.'){ 
                currDist = sqrt(i * i + j * j); // sqrt(x^2 + y^2)
            }

            if (currDist > furthest){ // compare to get the furthest distance
                furthest = currDist; 
                // the coord of the furthest point relative to the maze
                farPoint = mcpp::Coordinate(i, 0, j); 
            }
        }
    }

    // combine playerOrg and farPoint to get the coord for teleporting
    farPoint = playerOrg + farPoint; 
    mc.setPlayerTilePosition(farPoint);

    // Report the coord the player teleports to (via minecraft chat)
    std::string output = "Teleported to: "; 
    output += std::to_string(farPoint.x); 
    output += " " + std::to_string(farPoint.y);
    output += " " + std::to_string(farPoint.z);
    std::cout << output << std::endl; 

    // a second delay for the player to safely fall on the ground before solving
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Agent::initialiseSolve(){ 
    // The first part of the while-loop operates in the same way as 
    // initialiseSolveTest(), which is checking the sides and set the
    // orientation based on what's available. The second part of the loop
    // teleports the player to a random location 1 block away from the player 
    // until there's a block next to. 

    // bool end will turns "true" if free space is found, 
    // which ends the loop. 
    bool end = false; 
    srand(rand()); // random seed for more randomness

    while(!end){
        if(!checkNorth(acacia)){
            orientation = 3; 
            end = true;
        }
        else if (!checkEast(acacia)){ 
            orientation = 0; 
            end = true; 
        }
        else if (!checkSouth(acacia)){ 
            orientation = 1; 
            end = true; 
        }
        else if (!checkWest(acacia)){ 
            orientation = 2; 
            end = true; 
        }
        else { // randomly move the player
            if (rand() % 4 == 0){ 
                currPos = currPos + MOVE_XPLUS;
                currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
                mc.setPlayerPosition(currPos);  
            }
            else if (rand() % 4 == 1){ 
                currPos = currPos + MOVE_ZPLUS;
                currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
                mc.setPlayerPosition(currPos);   
            }
            else if (rand() % 4 == 2){ 
                currPos = currPos + MOVE_XMINUS;
                currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
                mc.setPlayerPosition(currPos);   
            }
            else if (rand() % 4 == 3){ 
                currPos = currPos + MOVE_ZMINUS;
                currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
                mc.setPlayerPosition(currPos);  
            }
        }
    } 
}

void Agent::initialiseSolveTest(){  
    // This function will just check the surrounding and set the orientation, 
    // starts with orientation = 3 means facing west means the right hand is 
    // facing north.  
    orientation = 3; 
    if (!checkNorth(acacia)){ 
        orientation = 3; 
    }
    else if (!checkEast(acacia)){ 
        orientation = 0;
    }
    else if (!checkSouth(acacia)){ 
        orientation = 1;
    }
    else if (!checkWest(acacia)){ 
        orientation = 2;
    }
}

void Agent::rightHandSolve() { 
    mc.doCommand("time set day");
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1;

    std::string origPos = "Start Position:"; 
    origPos += " " + std::to_string(currPos.x);
    origPos += " " + std::to_string(currPos.y);
    origPos += " " + std::to_string(currPos.z);
    mc.postToChat(origPos);

    mc.postToChat("FOLLOW the Lime Carpet");

    while (keepGoing){ 
        // In this context: 
        //  - North means X-positive/X-plus
        //  - East means Z-positive/Z-plus
        //  - South means X-negative/X-minus
        //  - West means Z-negative/Z-minus

        // Orientation is responsible to where the player is facing. Treat it
        // like a circle where each number in orientation equals 90-degree
        // (or pi/2 if you use that). 
        // E.g. orientation = 5 = 450-degree = 90-degree (3 o-clock or east)

        if (orientation % 4 == 0){ // Facing North
            if (checkEast(acacia)) {
                orientation += 1; // turn 90 degree clockwise (turn right)
                goEast();  
            }
            else if(checkNorth(acacia)) { 
                goNorth(); // go straight
            }
            else if(checkWest(acacia)) { 
                orientation += 3; // turn 270 degree clockwise (turn left) 
                goWest(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goSouth(); 
            }
        }
        else if (orientation % 4 == 1){ // Facing East
            if (checkSouth(acacia)) {
                orientation += 1; // turn 90 degree clockwise (turn right)
                goSouth();  
            }
            else if(checkEast(acacia)) { 
                goEast(); // go straight
            }
            else if(checkNorth(acacia)) { 
                orientation += 3; // turn 270 degree clockwise (turn left)
                goNorth(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goWest(); 
            }
        }
        else if (orientation % 4 == 2){ // Facing South
            if (checkWest(acacia)) { 
                orientation += 1; // turn 90 degree clockwise (turn right)
                goWest();  
            }
            else if(checkSouth(acacia)) { 
                goSouth(); // go straight
            }
            else if(checkEast(acacia)) { 
                orientation += 3; // turn 270 degree clockwise (turn left)
                goEast(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goNorth(); 
            }
        }
        else if (orientation % 4 == 3){ // Facing West 
            if (checkNorth(acacia)) {
                orientation += 1; // turn 90 degree clockwise (turn right)
                goNorth();  
            }
            else if(checkWest(acacia)) { 
                goWest(); // go straight
            }
            else if(checkSouth(acacia)) { 
                orientation += 3; // turn 270 degree clockwise (turn left)
                goSouth(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goEast(); 
            }
        }

        reportStep(); 

        // isDone() returns true when there's a blue carpet next to the player 
        if (isDone()) {
            keepGoing = false; // keepGoing is what keeps the loop going
            // the line below clears the current lime carpet. 
            mc.setBlock(currPos, mcpp::Blocks::AIR); 
            mc.postToChat("Congratulations! You reached the exit!"); 
        }
        
        // 200 miliseconds delay. 
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
} 

void Agent::bfsSolve(){ 
    // this getHeight is to prevent the solver from starting mid-air
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1;
    int i = 0; 
    bool isVisited = false; 
    mcpp::Coordinate tempPos; 
    mcpp::Coordinate tempXPlus; 
    mcpp::Coordinate tempZPlus; 
    mcpp::Coordinate tempXMinus; 
    mcpp::Coordinate tempZMinus; 
    std::vector<mcpp::Coordinate> queue; 
    queue.push_back(currPos); 
    std::vector<mcpp::Coordinate> visited; 
    std::vector<mcpp::Coordinate> path; 

    while(keepGoing) { 
        isVisited = false; 

        for (size_t j = 0; j < visited.size(); j++) { 
            // Check if the current block is visited
            if (queue.at(i) == visited[j]) { 
                isVisited = true; 
            }
        }

        if (!isVisited){ 
            // add the coord of the tile to "queue" vector if the next step
            // is not Acacia Wood Plank (called acacia in Agent) 
            tempPos = queue[i] + MOVE_XPLUS; // next step to X-positive
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z); 
            if (mc.getBlock(tempPos) != acacia) { 
                tempPos.y += 1;  
                queue.push_back(tempPos); 
            }

            tempPos = queue[i] + MOVE_ZPLUS; // next step to Z-positive
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;
                queue.push_back(tempPos); 
            }

            tempPos = queue[i] + MOVE_XMINUS; // next step to X-negative
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;
                queue.push_back(tempPos); 
            }

            tempPos = queue[i] + MOVE_ZMINUS; // next step to Z-negative
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;
                queue.push_back(tempPos); 
            }

            // move to the current tile in queue by placing a white carpet
            mc.setBlock(queue.at(i), mcpp::Blocks::WHITE_CARPET);
            // add that tile to "visited" vector
            visited.push_back(queue.at(i));
            // set the current Position to that tile
            currPos = queue.at(i);

            if (isDone()) { // the same isDone() as rightHandSolve()
                keepGoing = false; 
                mc.postToChat("BFS Completed"); 
                mc.setBlock(currPos, mcpp::Blocks:: WHITE_CARPET);
            }
        }
        i++; // move to the next item in queue. 
    }

    // clear the white carpets
    for (size_t j = 0; j < visited.size(); j++) {
        mc.setBlock(visited.at(j), mcpp::Blocks::AIR);
    }

    mc.postToChat("Setting the escape path, WAIT for the lime carpet."); 

    for (size_t j = visited.size(); j > 0; j--) { // Trace path
        // all the temps here have only 1 purpose: which is to use getHeight,
        // which is for making the algorithm works with uneven surfaces
        tempXPlus = currPos + MOVE_XPLUS; 
        tempXPlus.y = mc.getHeight(tempXPlus.x, tempXPlus.z) + 1; 

        tempZPlus = currPos + MOVE_ZPLUS; 
        tempZPlus.y = mc.getHeight(tempZPlus.x, tempZPlus.z) + 1;

        tempXMinus = currPos + MOVE_XMINUS; 
        tempXMinus.y = mc.getHeight(tempXMinus.x, tempXMinus.z) + 1;

        tempZMinus = currPos + MOVE_ZMINUS; 
        tempZMinus.y = mc.getHeight(tempZMinus.x, tempZMinus.z) + 1;

        // this is similar to the breadth first search, but going backwards
        // from the finish line (blue carpet), and only allowed to step on 
        // the tiles in "visited" vector
        if (tempXPlus == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = tempXPlus; 
        }
        else if (tempZPlus == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = tempZPlus;
        }
        else if (tempXMinus == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = tempXMinus;
        }
        else if (tempZMinus == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = tempZMinus;
        }
        // at the steps into "path" vector for displaying the lime carpet
        path.push_back(currPos);
    }

    // there's duplicate in the "path" vector so I removed them. 
    vecRemoveDups(path); 
    mc.postToChat("FOLLOW the lime carpet");

    // show the lime carpet path (similar as shown in rightHandSolve)
    for (size_t j = path.size(); j > 0; j--){ 
        mc.setBlock(currPos, mcpp::Blocks::AIR);
        currPos = path.at(j - 1); 
        mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
        reportStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    mc.setBlock(currPos, mcpp::Blocks::AIR); // clear the final lime carpet
    mc.postToChat("Congratulations! You reached the exit!"); 
}  