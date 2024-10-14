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

bool Agent::checkNorth(mcpp::Coordinate currPos) {
    mcpp::Coordinate blockPos(0, 0, 0);

    blockPos = currPos + MOVE_XPLUS; 

    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(blockPos); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
        // mc.postToChat("North Clear");
    }

    return isAir; 
}

bool Agent::checkEast(mcpp::Coordinate currPos) {
    mcpp::Coordinate blockPos(0, 0, 0);

    blockPos = currPos + MOVE_ZPLUS; 

    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(blockPos); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

bool Agent::checkSouth(mcpp::Coordinate currPos) {
    mcpp::Coordinate blockPos(0, 0, 0);

    blockPos = currPos + MOVE_XMINUS; 

    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(blockPos); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

bool Agent::checkWest(mcpp::Coordinate currPos) {
    mcpp::Coordinate blockPos(0, 0, 0);

    blockPos = currPos + MOVE_ZMINUS; 

    bool isAir = false; 
    mcpp::BlockType tempBlock; 
    tempBlock = mc.getBlock(blockPos); 

    if (tempBlock == mcpp::Blocks::AIR){
        isAir = true; 
    }

    return isAir; 
}

void Agent::goNorth(mcpp::Coordinate &currPos) { 
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_XPLUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
} 

void Agent::goEast(mcpp::Coordinate &currPos) {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZPLUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goSouth(mcpp::Coordinate &currPos) {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_XMINUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::goWest(mcpp::Coordinate &currPos) {
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    currPos = currPos + MOVE_ZMINUS; 
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
}

void Agent::rightHandSolve() { 
    mcpp::MinecraftConnection mc;
    mc.postToChat("Finding Path");
    mc.doCommand("time set day");

    std::string temp = "Original Position: "; 
    temp += " " + std::to_string(currPos.x);
    temp += " " + std::to_string(currPos.y);
    temp += " " + std::to_string(currPos.z);

    mc.postToChat(temp);

    while (keepGoing){

        if (orientation % 4 == 0){ //Facing North
            if (checkEast(currPos)) {
                goEast(currPos);  
                orientation += 1; // turn 90 degree clockwise
            }
            else if(!checkEast(currPos) && !checkNorth(currPos)) { 
                orientation += 2; // turn 180 degree clockwise
            }
            else if(!checkEast(currPos) && checkNorth(currPos)) { 
                goNorth(currPos); 
            }
        }
        else if (orientation % 4 == 1){ //Facing East
            if (checkSouth(currPos)) {
                goSouth(currPos); 
                orientation += 1; 
            }
            else if(!checkSouth(currPos) && !checkEast(currPos)) { 
                orientation += 2; 
            }
            else if(!checkSouth(currPos) && checkEast(currPos)) { 
                goEast(currPos); 
            }
        }
        else if (orientation % 4 == 2){ //Facing South
            if (checkWest(currPos)) {
                goWest(currPos); 
                orientation += 1; 
            }
            else if(!checkWest(currPos) && !checkSouth(currPos)) { 
                orientation += 2; 
            }
            else if(!checkWest(currPos) && checkSouth(currPos)) { 
                goSouth(currPos); 
            }
        }
        else if (orientation % 4 == 3){ //Facing West
            if (checkNorth(currPos)) {
                goNorth(currPos); 
                orientation += 1; 
            }
            else if(!checkNorth(currPos) && !checkWest(currPos)) { 
                orientation += 2; 
            }
            else if(!checkNorth(currPos) && checkWest(currPos)) { 
                goWest(currPos); 
            }
        }

        if (checkNorth(currPos) && checkEast(currPos) && checkSouth(currPos) && checkWest(currPos)) {
            keepGoing = false; 
            mc.setBlock(currPos, mcpp::Blocks::AIR);
            mc.postToChat("Solve completed"); 
            return;
        }

        step++; 
        std::string stepChat = "Step[" + std::to_string(step) + "]:"; 
        stepChat += " (" + std::to_string(currPos.x);
        stepChat += ", " + std::to_string(currPos.y);
        stepChat += ", " + std::to_string(currPos.z) + ")";
        // stepChat += " Orientation: " + std::to_string(orientation % 4); 
        // mc.postToChat(stepChat); 
        std::cout << stepChat << std::endl; 
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
} 