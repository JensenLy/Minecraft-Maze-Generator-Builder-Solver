#include "Agent.h"

Agent::Agent(/*mcpp::Coordinate startLoc*/)
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
    bool clear = false; 
    mcpp::BlockType tempBlock; 
    mcpp::Coordinate tempPos = currPos + MOVE_XPLUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
    tempBlock = mc.getBlock(tempPos); 

    if (tempBlock != block){
        clear = true;  
    }
    return clear; 
}

bool Agent::checkEast(mcpp::BlockType block) {
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
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET); // place the new carpet
} 

void Agent::goEast() {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZPLUS; 
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goSouth() {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_XMINUS; 
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goWest() {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZMINUS; 
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::reportStep() { 
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
    mcpp::Coordinate tempPos;

    tempPos = currPos + MOVE_XPLUS; 
    tempPos.y = mc.getHeight(tempPos.x, tempPos.z) + 1; 
    if (mc.getBlock(tempPos) == mcpp::Blocks::BLUE_CARPET){
        isDone = true;  
    }

    tempPos = currPos + MOVE_ZPLUS; 
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
    srand(rand()); 
    int rowRand = 0; 
    int colRand = 0; 
    while (keepGoing){ 
        rowRand = rand() % row; 
        colRand = rand() % col; 

        if (maze[rowRand][colRand] == '.') { 
            keepGoing = false; 
            currPos = playerOrg + mcpp::Coordinate(rowRand, 0 , colRand);
            currPos.y = mc.getHeight(currPos.x, currPos.z); 
            mc.setPlayerTilePosition(currPos); 
        }
    }
}

void Agent::manualSolveTest\
(mcpp::Coordinate playerOrg, int row, int col, char** maze){ 
    double furthest = 0.0; 
    double currDist = 0.0; 
    mcpp::Coordinate farPoint(0, 0, 0); 

    for (int i = 0; i < row; i++){ 
        for (int j = 0; j < col; j++){ 
            if (maze[i][j] == '.'){ 
                currDist = sqrt(i * i + j * j);  
            }

            if (currDist > furthest){
                furthest = currDist; 
                farPoint = mcpp::Coordinate(i, 0, j); 
            }
        }
    }

    farPoint = playerOrg + farPoint; 
    mc.setPlayerTilePosition(farPoint);
    std::string output = "Teleported to: "; 
    output += std::to_string(farPoint.x); 
    output += " " + std::to_string(farPoint.y);
    output += " " + std::to_string(farPoint.z);
    std::cout << output << std::endl; 

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
    mc.postToChat("Orientation: " + std::to_string(orientation % 4));
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

    mc.postToChat("Orientation: " + std::to_string(orientation % 4));
}

void Agent::rightHandSolve() { 
    mc.doCommand("time set day");
    currPos.y = mc.getHeight(currPos.x, currPos.z) + 1;

    std::string origPos = "Start Position:"; 
    origPos += " " + std::to_string(currPos.x);
    origPos += " " + std::to_string(currPos.y);
    origPos += " " + std::to_string(currPos.z);
    mc.postToChat(origPos);

    mc.postToChat("Follow the Lime Carpet");

    while (keepGoing){ 
        // In the wall follower solving, I use an integer named "orientation"
        // to indicate where the player is facing (the front, not right hand).
        // For each step, I check the current position's (currPos) right, 
        // front, back, and left respectively and take a step if there's 
        // a free space (since it's right-hand wall follower so I have to
        // prioritise/check the right hand side first). 

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
        
        // half a second delay. 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
} 

void Agent::bfsSolve(){ 
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
            tempPos = queue[i] + MOVE_XPLUS; 
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z); 
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;  
                queue.push_back(tempPos); 
            }

            tempPos = queue[i] + MOVE_ZPLUS; 
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;
                queue.push_back(tempPos); 
            }

            tempPos = queue[i] + MOVE_XMINUS; 
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;
                queue.push_back(tempPos); 
            }

            tempPos = queue[i] + MOVE_ZMINUS; 
            tempPos.y = mc.getHeight(tempPos.x, tempPos.z);
            if (mc.getBlock(tempPos) != acacia) {
                tempPos.y += 1;
                queue.push_back(tempPos); 
            }

            mc.setBlock(queue.at(i), mcpp::Blocks::WHITE_CARPET);
            visited.push_back(queue.at(i));

            currPos = queue.at(i);

            if (isDone()) { 
                keepGoing = false; 
                mc.postToChat("BFS Completed"); 
                mc.setBlock(currPos, mcpp::Blocks:: WHITE_CARPET);
            }
        }
        i++; 
    }

    for (size_t j = 0; j < visited.size(); j++) {
        mc.setBlock(visited.at(j), mcpp::Blocks::AIR);
    }

    mc.postToChat("Setting the escape path, WAIT for the lime carpet."); 

    for (size_t j = visited.size(); j > 0; j--) { // Trace path
        tempXPlus = currPos + MOVE_XPLUS; 
        tempXPlus.y = mc.getHeight(tempXPlus.x, tempXPlus.z) + 1; 

        tempZPlus = currPos + MOVE_ZPLUS; 
        tempZPlus.y = mc.getHeight(tempZPlus.x, tempZPlus.z) + 1;

        tempXMinus = currPos + MOVE_XMINUS; 
        tempXMinus.y = mc.getHeight(tempXMinus.x, tempXMinus.z) + 1;

        tempZMinus = currPos + MOVE_ZMINUS; 
        tempZMinus.y = mc.getHeight(tempZMinus.x, tempZMinus.z) + 1;

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
        path.push_back(currPos);
    }

    vecRemoveDups(path); 
    mc.postToChat("Follow the lime carpet");
    for (size_t j = path.size(); j > 0; j--){ 
        mc.setBlock(currPos, mcpp::Blocks::AIR);
        currPos = path.at(j - 1); 
        mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
        reportStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    mc.postToChat("Congratulations! You reached the exit!"); 
}  