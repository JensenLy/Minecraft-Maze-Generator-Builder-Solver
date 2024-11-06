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

bool Agent::checkNorth() {
    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(currPos + MOVE_XPLUS); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

bool Agent::checkEast() {
    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(currPos + MOVE_ZPLUS); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

bool Agent::checkSouth() {
    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(currPos + MOVE_XMINUS); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

bool Agent::checkWest() {
    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(currPos + MOVE_ZMINUS); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

void Agent::goNorth() { 
    mc.setBlock(currPos, mcpp::Blocks::AIR); // clear the current lime carpet
    currPos = currPos + MOVE_XPLUS; // step 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET); // place the new carpet
} 

void Agent::goEast() {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZPLUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goSouth() {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_XMINUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goWest() {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZMINUS; 
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
    // returns true when there's a blue carpet around the player
    bool isDone = false; 

    if (mc.getBlock(currPos + MOVE_XPLUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true;  
    }
    if (mc.getBlock(currPos + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
    }
    if (mc.getBlock(currPos + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true;  
    }
    if (mc.getBlock(currPos + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET){
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

    mc.setPlayerTilePosition(playerOrg + farPoint);
    farPoint = playerOrg + farPoint; 
    std::string output = "Teleported to: "; 
    output += std::to_string(farPoint.x); 
    output += " " + std::to_string(farPoint.y);
    output += " " + std::to_string(farPoint.z);
    std::cout << output << std::endl; 

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
        if(!checkNorth()){
            orientation = 3; 
            end = true;
        }
        else if (!checkEast()){ 
            orientation = 0; 
            end = true; 
        }
        else if (!checkSouth()){ 
            orientation = 1; 
            end = true; 
        }
        else if (!checkWest()){ 
            orientation = 2; 
            end = true; 
        }
        else { // randomly move the player
            if (rand() % 4 == 0){ 
                currPos = currPos + MOVE_XPLUS;
                mc.setPlayerPosition(currPos);  
            }
            else if (rand() % 4 == 1){ 
                currPos = currPos + MOVE_ZPLUS;
                mc.setPlayerPosition(currPos);   
            }
            else if (rand() % 4 == 2){ 
                currPos = currPos + MOVE_XMINUS;
                mc.setPlayerPosition(currPos);   
            }
            else if (rand() % 4 == 3){ 
                currPos = currPos + MOVE_ZMINUS;
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
    if (!checkNorth()){ 
        orientation = 3; 
    }
    else if (!checkEast()){ 
        orientation = 0;
    }
    else if (!checkSouth()){ 
        orientation = 1;
    }
    else if (!checkWest()){ 
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
            if (checkEast()) {
                orientation += 1; // turn 90 degree clockwise (turn right)
                goEast();  
            }
            else if(checkNorth()) { 
                goNorth(); // go straight
            }
            else if(checkWest()) { 
                orientation += 3; // turn 270 degree clockwise (turn left) 
                goWest(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goSouth(); 
            }
        }
        else if (orientation % 4 == 1){ // Facing East
            if (checkSouth()) {
                orientation += 1; // turn 90 degree clockwise (turn right)
                goSouth();  
            }
            else if(checkEast()) { 
                goEast(); // go straight
            }
            else if(checkNorth()) { 
                orientation += 3; // turn 270 degree clockwise (turn left)
                goNorth(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goWest(); 
            }
        }
        else if (orientation % 4 == 2){ // Facing South
            if (checkWest()) { 
                orientation += 1; // turn 90 degree clockwise (turn right)
                goWest();  
            }
            else if(checkSouth()) { 
                goSouth(); // go straight
            }
            else if(checkEast()) { 
                orientation += 3; // turn 270 degree clockwise (turn left)
                goEast(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step (turn around)
                goNorth(); 
            }
        }
        else if (orientation % 4 == 3){ // Facing West 
            if (checkNorth()) {
                orientation += 1; // turn 90 degree clockwise (turn right)
                goNorth();  
            }
            else if(checkWest()) { 
                goWest(); // go straight
            }
            else if(checkSouth()) { 
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
            if (mc.getBlock(queue[i] + MOVE_XPLUS) == mcpp::Blocks::AIR) {
                queue.push_back(queue[i] + MOVE_XPLUS); 
            }
            if (mc.getBlock(queue[i] + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
                queue.push_back(queue[i] + MOVE_ZPLUS); 
            }
            if (mc.getBlock(queue[i] + MOVE_XMINUS) == mcpp::Blocks::AIR) {
                queue.push_back(queue[i] + MOVE_XMINUS); 
            }
            if (mc.getBlock(queue[i] + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
                queue.push_back(queue[i] + MOVE_ZMINUS); 
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

    mc.postToChat("Setting the escape path"); 

    for (size_t j = visited.size(); j > 0; j--) { // Trace path
        if (currPos + MOVE_XPLUS == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = currPos + MOVE_XPLUS; 
        }
        else if (currPos + MOVE_ZPLUS == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = currPos + MOVE_ZPLUS; 
        }
        else if (currPos + MOVE_XMINUS == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = currPos + MOVE_XMINUS; 
        }
        else if (currPos + MOVE_ZMINUS == visited.at(j - 1)) { 
            path.push_back(currPos);
            currPos = currPos + MOVE_ZMINUS; 
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