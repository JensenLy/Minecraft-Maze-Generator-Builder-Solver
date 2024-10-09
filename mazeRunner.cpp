#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(void){

    //bool mode = NORMAL_MODE;
    //read Mode
    
    printStartText();

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    States curState = ST_Main;
    std::string userInput;

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
            
            if(userInput == "1"){
                std::cout << "To Do Opt 1";

            }
            else if(userInput == "2"){
                std::cout << "To Do Opt 2";
            }
            else if(userInput == "3"){
                curState = ST_Main;
            }
            else{
                std::cout << "Please select menu item with numbers 1 to 3"; 
            }
        }
        else if(curState == ST_Creators){
            std::cout << "To Do Build Maze";
            curState = ST_Main;
        }
        else if(curState == ST_SolveMaze){
            printSolveMazeMenu();
            getline(std::cin, userInput);

            if(userInput == "1"){
                std::cout << "To Do Opt 1";
            }
            else if(userInput == "2"){
                std::cout << "To Do Opt 2";
            }
            else if(userInput == "3"){
                curState = ST_Main;
            }
            else{
                std::cout << "Please select menu item with numbers 1 to 3"; 
            }
        }

        

    }

    printExitMassage();


    return EXIT_SUCCESS;

}