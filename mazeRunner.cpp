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
                int userX;
                int userY;
                bool correctInput = false;

                std::cout << "In Minecraft, navigate to where you need the maze\nto be built in Minecraft and type - done:" << std::endl;

                std::string input; 
                std::cin >> input;
                if (input == "done"){

                    //mcpp::Coordinate playerOrg = mc.getPlayerPosition();

                    std::cout << "Enter the length and width of maze" << std::endl;

                    while(!correctInput){
                        std::cin >> userX >> userY;
                
                        if(userX%2 == 0 || userY%2 == 0){
                            std::cout << "Please enter odd values for the length and width of maze" << std::endl;
                        }
                        else{
                            correctInput = true;
                        }
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                GenerateMaze userMaze = GenerateMaze(userX, userY);
                userMaze.UserInputMaze(userX, userY);
                userMaze.printMaze();

                }

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
            
            // std::string input; 
            // std::cin >> input;
            // if (input == "done") {
            //     std::cout << "Enter the length and width of maze:" << std::endl;
            //     int length;
            //     int width;
            //     std::cin >> length;
            //     std::cin >> width;
            
            // }
            // else {
            //     std::cout << "Invalid input, did you mean \"done\"" << std::endl; 
            // }

            
            // mcpp::Coordinate playerOrg = mc.getPlayerPosition();
            
            // curState = ST_Main;
        }
        else if(curState == ST_SolveMaze){
            printSolveMazeMenu();
            getline(std::cin, userInput);

            if(userInput == "1"){
                std::cout << "To Do Opt 1"; 
            }
            else if(userInput == "2"){
                Agent* solve = new Agent(); 
                solve->rightHandSolve(); 
                delete solve; 
            }
            else if(userInput == "3"){
                curState = ST_Main;
            }
            else if(userInput == "?") { // Placeholder for BFS Solving
                Agent* solve = new Agent(); 
                solve->BFSSolve(); 
                delete solve;
            }
            else{
                std::cout << "Please select menu item with numbers 1 to 3"; 
            }
        }

        

    }

    printExitMassage();


    return EXIT_SUCCESS;

}