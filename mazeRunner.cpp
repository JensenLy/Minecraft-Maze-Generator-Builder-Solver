#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "GenerateMaze.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(int argc, char* argv[]){

    bool mode = NORMAL_MODE;
    std::string argument = ""; 

    if (argc > 1) { 
        argument = std::string(argv[1]);
        if (argument == "-testmode"){
            mode = TESTING_MODE; 
        }
    }
    
    printStartText();

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    States curState = ST_Main;
    std::string userInput;
    Maze *m = new Maze();
    bool correctInput = false;
    GenerateMaze userMaze;
    bool isBuilt = false; 
    bool isTeleported = false; 

    //State machine for menu        
    while (curState != ST_Exit)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        if(curState == ST_Main){
            printMainMenu();
            getline(std::cin, userInput);
            
            if(userInput == "1"){
                curState = ST_GetMaze;
            }
            else if(userInput == "2"){
                curState = ST_Creators;
            }
            else if(userInput == "3"){
                curState = ST_SolveMaze;
            }
            else if(userInput == "4"){
                printTeamInfo();
            }
            else if(userInput == "5"){
                curState = ST_Exit;
            }
            else{
                std::cout << "Please select menu item with numbers 1 to 5";
            }
        }

        if(curState == ST_GetMaze){
            printGenerateMazeMenu();
            getline(std::cin, userInput);
            
            if(mode){
                if(userInput == "1"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    userMaze.ValidateUserMazeInput();
                    userMaze.printMaze();
                    correctInput = true;
                    curState = ST_Main;
                }
                else if(userInput == "2"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    std::cout << "***Printing Maze***" << std::endl;
                    std::cout << "Base Point: " << userMaze.getCord() << std::endl;
                    std::cout << "Structure: "  << std::endl;
                    userMaze.GenerateTestMaze();
                    userMaze.carveTestMaze();
                    userMaze.printMaze();
                    curState = ST_Main;
                    correctInput = true;
                }
                else if(userInput == "3"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    userMaze.ValidateUserMazeInput();
                    std::array<int, 2> entrance = userMaze.findEntrance();
                    userMaze.floodFill(entrance, '.');
                    userMaze.printMaze();

                    userMaze.printMaze();
                    curState = ST_Main;
                }
                else if(userInput == "4"){
                    curState = ST_Main;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 4"; 
                }
            }
            else{
                if(userInput == "1"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    userMaze.ValidateUserMazeInput();
                    userMaze.printMaze();
                    curState = ST_Main;
                    correctInput = true;
                }
                else if(userInput == "2"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    userMaze.GenerateRandMaze();
                    userMaze.carveMaze();
                    userMaze.printMaze();
                    curState = ST_Main;
                    correctInput = true;
                }
                else if(userInput == "3"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    userMaze.ValidateUserMazeInput();
                    userMaze.fixUserInput();

                    curState = ST_Main;
                }
                else if(userInput == "4"){
                    curState = ST_Main;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 4"; 
                }
            }

        }
        else if(curState == ST_Creators){
            printBuildMaze();
            getline(std::cin, userInput);

            if (userInput == "1") {
                if (correctInput) {
                    std::cout << "Building Maze" << std::endl;
                    m = new Maze(userMaze.getCord(), userMaze.getMazeWidth(),\
                    userMaze.getMazeHeight(), correctInput, userMaze.getMaze());

                    m->scanTerrain();
                    m->storeTerrain();
                    m->terraformTerrain();
                    m->buildMaze();
                    
                    std::cout << "Built Maze" << std::endl;
                    curState = ST_Main;

                    isBuilt = true;
                }
                else {
                    std::cout << "Generate maze first. Type 1 to Generate Maze" << std::endl;
                    curState = ST_Main;
                }
            }
            else if (userInput == "2") {
                if (correctInput) {
                    std::cout << "Building Maze" << std::endl;
                    m = new Maze(userMaze.getCord(), userMaze.getMazeWidth(),\
                    userMaze.getMazeHeight(), correctInput, userMaze.getMaze());

                    m->scanTerrainEnhancement();
                    m->buildMazeEnhancement();
                    
                    std::cout << "Built Maze" << std::endl;
                    curState = ST_Main;

                    isBuilt = true;
                }
                else {
                    std::cout << "Generate maze first. Type 1 to Generate Maze" << std::endl;
                    curState = ST_Main;
                }
            }
            else if(userInput == "3"){
                    curState = ST_Main;
            }
            else{
                std::cout << "Please select menu item with numbers 1 to 3"; 
            }
            
        }
        else if(curState == ST_SolveMaze){
            printSolveMazeMenu();
            getline(std::cin, userInput);

            if (mode) { // Test mode
                if(userInput == "1") {
                    if (isBuilt){
                        Agent solve;  
                        
                        solve.manualSolveTest(userMaze.getCord(),\
                        userMaze.getMazeHeight(), userMaze.getMazeWidth(), \
                        userMaze.getMaze()); 

                        isTeleported = true; 
                    }
                    else { 
                        std::cout << "Please build the maze first before ";
                        std::cout << "teleporting, doing so by pressing \"2\" ";
                        std::cout << "on the main menu" << std::endl; 
                    }
                    
                }
                else if(userInput == "2"){
                    if (isTeleported){ 
                        Agent solve; 
                        solve.initialiseSolveTest();
                        solve.rightHandSolve();  
                        isTeleported = false; 
                    }
                    else { 
                        std::cout << "Please use \"Manual Solve\" before "; 
                        std::cout << "attempting to show the escape path "; 
                        std::cout << "by pressing \"1\" in \"Solve Maze\" menu";
                        std::cout << std::endl; 
                    }
                    
                }
                else if(userInput == "3") {
                    if (isTeleported){ 
                        Agent solve; 
                        solve.bfsSolve(); 

                        isTeleported = false; 
                    }
                    else {
                        std::cout << "Please use \"Manual Solve\" before "; 
                        std::cout << "attempting to show the escape path "; 
                        std::cout << "by pressing \"1\" in \"Solve Maze\" menu";
                        std::cout << std::endl; 
                    }
                }
                else if(userInput == "4"){
                    curState = ST_Main;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 4"; 
                }
            }
            else { // Normal mode
                if(userInput == "1"){ 
                    if (isBuilt){
                        Agent solve;  
                        
                        solve.manualSolve(userMaze.getCord(),\
                        userMaze.getMazeHeight(), userMaze.getMazeWidth(), \
                        userMaze.getMaze()); 

                        isTeleported = true; 
                    }
                    else { 
                        std::cout << "Please build the maze first before ";
                        std::cout << "teleporting, doing so by pressing \"2\" ";
                        std::cout << "on the main menu" << std::endl; 
                    }
                }
                else if(userInput == "2"){
                    if (isTeleported){ 
                        Agent solve; 
                        solve.initialiseSolve();
                        solve.rightHandSolve(); 

                        isTeleported = false; 
                    }
                    else { 
                        std::cout << "Please use \"Manual Solve\" before "; 
                        std::cout << "attempting to show the escape path "; 
                        std::cout << "by pressing \"1\" in \"Solve Maze\" menu";
                        std::cout << std::endl; 
                    }
                }
                else if(userInput == "3") {
                    if (isTeleported){ 
                        Agent solve; 
                        solve.bfsSolve(); 

                        isTeleported = false; 
                    }
                    else {
                        std::cout << "Please use \"Manual Solve\" before "; 
                        std::cout << "attempting to show the escape path "; 
                        std::cout << "by pressing \"1\" in \"Solve Maze\" menu";
                        std::cout << std::endl; 
                    }
                }
                else if(userInput == "4"){
                    curState = ST_Main;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 3"; 
                }
            }
        }

    }
    //maze , access the list
    printExitMassage();
    // {
    // Maze Maze;
    // }
    // Maze.exitCleanUp();
    delete m;

    

    return EXIT_SUCCESS;

}