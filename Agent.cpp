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

    mcpp::BlockType checkNorthx2; 
    mcpp::BlockType checkEastx2; 
    mcpp::BlockType checkSouthx2; 
    mcpp::BlockType checkWestx2; 

    checkNorthx2 = mc.getBlock(currPos + MOVE_XPLUS + MOVE_XPLUS); 
    checkEastx2 = mc.getBlock(currPos + MOVE_ZPLUS + MOVE_ZPLUS);
    checkSouthx2 = mc.getBlock(currPos + MOVE_XMINUS + MOVE_XMINUS);
    checkWestx2 = mc.getBlock(currPos + MOVE_ZMINUS + MOVE_ZMINUS);

    if (checkNorthx2 == mcpp::Blocks::AIR && checkNorth()){
        if (checkEastx2 == mcpp::Blocks::AIR && checkEast()){
            if (checkSouthx2 == mcpp::Blocks::AIR && checkSouth()){
                if (checkWestx2 == mcpp::Blocks::AIR && checkWest()){
                    isDone = true; 
                }
            }
        }
    }

    return isDone; 
}

void Agent::rightHandSolve() { 
    mcpp::MinecraftConnection mc;
    mc.doCommand("time set day");

    std::string origPos = "Original Position: "; 
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
            mc.postToChat("Congratulations! You are now outside the maze."); 
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
} 