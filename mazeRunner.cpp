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
    // maze* =nullptr
    Maze *m = new Maze();
    bool correctInput = false;
    GenerateMaze userMaze;
    //Maze

    //State machine for menu        
    while (curState != ST_Exit)
    {
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
                }
                else if(userInput == "2"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    std::cout << "***Printing Maze***" << std::endl;
                    std::cout << "Base Point: " << userMaze.getCord() << std::endl;
                    std::cout << "Structure: "  << std::endl;
                    userMaze.GenerateTestMaze();
                    userMaze.carveTestMaze();
                    userMaze.printMaze();
                }
                else if(userInput == "3"){
                    curState = ST_Main;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 3"; 
                }
            }
            else{
                if(userInput == "1"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    userMaze.ValidateUserMazeInput();
                    userMaze.printMaze();
                }
                else if(userInput == "2"){
                    userMaze = userMaze.ValidateUserMazeSize();
                    std::cout << "***Printing Maze***" << std::endl;
                    std::cout << "Base Point: " << userMaze.getCord() << std::endl;
                    std::cout << "Structure: "  << std::endl;
                    userMaze.GenerateRandMaze();
                    userMaze.carveMaze();
                    userMaze.printMaze();
                }
                else if(userInput == "3"){
                    curState = ST_Main;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 3"; 
                }
            }

        }
        else if(curState == ST_Creators){
            std::cout << "Building maze" << std::endl;
            m = new Maze(userMaze.getCord(), userMaze.getMazeWidth(), userMaze.getMazeHeight(), correctInput, userMaze.getMaze());

            m->scanTerrain();
            m->storeTerrain();
            m->terraformTerrain();
            m->buildMaze();
            
            curState = ST_Main;
        }
        else if(curState == ST_SolveMaze){
            printSolveMazeMenu();
            getline(std::cin, userInput);

            if (mode) { // Test mode
                if(userInput == "1") {
                    Agent* solve = new Agent();  
                    
                    solve->manualSolveTest(userMaze.getCord(),\
                    userMaze.getMazeHeight(), userMaze.getMazeWidth(), \
                    userMaze.getMaze()); 

                    delete solve;
                }
                else if(userInput == "2"){
                    Agent* solve = new Agent(); 
                    solve->initialiseSolveTest();
                    solve->rightHandSolve(); 
                    delete solve; 
                }
                else if(userInput == "4"){
                    curState = ST_Main;
                }
                else if(userInput == "3") { // Placeholder for BFS Solving
                    Agent* solve = new Agent(); 
                    solve->bfsSolve(); 
                    delete solve;
                }
                else{
                    std::cout << "Please select menu item with numbers 1 to 3"; 
                }
            }
            else { // Normal mode
                if(userInput == "1"){ 
                    Agent* solve = new Agent(); 
                    
                    solve->manualSolve(userMaze.getCord(), \
                    userMaze.getMazeHeight(), userMaze.getMazeWidth(), \
                    userMaze.getMaze()); 

                    delete solve; 
                }
                else if(userInput == "2"){
                    Agent* solve = new Agent(); 
                    solve->initialiseSolve(); 
                    solve->rightHandSolve(); 
                    delete solve; 
                }
                else if(userInput == "4"){
                    curState = ST_Main;
                }
                else if(userInput == "3") { // Placeholder for BFS Solving
                    Agent* solve = new Agent(); 
                    solve->bfsSolve(); 
                    delete solve;
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