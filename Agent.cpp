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
        // mc.postToChat("North Clear");
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
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_XPLUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
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
    // reportStep += " Orientation: " + std::to_string(orientation % 4); 
    // mc.postToChat(reportStep); 
    std::cout << reportStep << std::endl; 
}

bool Agent::isDone() { 
    bool isDone = false; 

    if (mc.getBlock(currPos + MOVE_XPLUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
        // currPos = currPos + MOVE_XPLUS; 
    }
    if (mc.getBlock(currPos + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
        // currPos = currPos + MOVE_ZPLUS; 
    }
    if (mc.getBlock(currPos + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
        // currPos = currPos + MOVE_XMINUS; 
    }
    if (mc.getBlock(currPos + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET){
        isDone = true; 
        // currPos = currPos + MOVE_ZMINUS; 
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
    mc.postToChat(output); 

}

void Agent::rightHandSolve() { 
    mc.doCommand("time set day");

    std::string origPos = "Original Position:"; 
    origPos += " " + std::to_string(currPos.x);
    origPos += " " + std::to_string(currPos.y);
    origPos += " " + std::to_string(currPos.z);
    mc.postToChat(origPos);

    mc.postToChat("Follow the Lime Carpet");

    while (keepGoing){ 

        if (orientation % 4 == 0){ // Facing North
            if (checkEast()) {
                orientation += 1; // turn 90 degree clockwise
                goEast();  
            }
            else if(checkNorth()) { 
                goNorth(); // go straight
            }
            else if(checkWest()) { 
                orientation += 3; // turn 270 degree clockwise (or 90 degree anti-clockwise)
                goWest(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step
                goSouth(); 
            }
        }
        else if (orientation % 4 == 1){ // Facing East
            if (checkSouth()) {
                orientation += 1; // turn 90 degree clockwise
                goSouth();  
            }
            else if(checkEast()) { 
                goEast(); // go straight
            }
            else if(checkNorth()) { 
                orientation += 3; // turn 270 degree clockwise (or 90 degree anti-clockwise)
                goNorth(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step
                goWest(); 
            }
        }
        else if (orientation % 4 == 2){ // Facing South
            if (checkWest()) { 
                orientation += 1; // turn 90 degree clockwise
                goWest();  
            }
            else if(checkSouth()) { 
                goSouth(); // go straight
            }
            else if(checkEast()) { 
                orientation += 3; // turn 270 degree clockwise (or 90 degree anti-clockwise)
                goEast(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step
                goNorth(); 
            }
        }
        else if (orientation % 4 == 3){ // Facing West
            if (checkNorth()) {
                orientation += 1; // turn 90 degree clockwise
                goNorth();  
            }
            else if(checkWest()) { 
                goWest(); // go straight
            }
            else if(checkSouth()) { 
                orientation += 3; // turn 270 degree clockwise (or 90 degree anti-clockwise)
                goSouth(); 
            }
            else { 
                orientation += 2; // turn 180 degree and step
                goEast(); 
            }
        }

        reportStep(); 

        if (isDone()) {
            keepGoing = false; 
            mc.setBlock(currPos, mcpp::Blocks::AIR);
            mc.postToChat("Congratulations! You reached the exit!"); 
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
} 

void Agent::bfsSolve(){ 
    int i = 0; 
    bool isVisited = false; 
    std::vector<mcpp::Coordinate> queue; 
    queue.push_back(currPos); 
    std::vector<mcpp::Coordinate> visited; 
    std::vector<mcpp::Coordinate> path; 

    while(keepGoing) { 
        // std::cout << "Loop " << i << std::endl; 
        isVisited = false; 

        for (size_t j = 0; j < visited.size(); j++) { // Check if the current block is visited
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
        std::this_thread::sleep_for(std::chrono::milliseconds(650));
    }
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    mc.postToChat("Congratulations! You reached the exit!"); 
}  