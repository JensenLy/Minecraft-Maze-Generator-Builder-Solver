#include "Maze.h"
#include "env.h"
#include <random>
#include <mcpp/mcpp.h>

Maze::Maze() {}


Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                    unsigned int zlen,
                                    bool mode, char** sourceMaze)
{
  this->basePoint = basePoint;
  this->xlen = xlen;
  this->zlen = zlen;
  this->mode = mode;
  

    
    mc.doCommand("time set day");

    this->maze = new char*[zlen];
    for (unsigned int i = 0; i < zlen; ++i) {
        this->maze[i] = new char[xlen];
        for (unsigned int j = 0; j < xlen; ++j) {
            this->maze[i][j] = sourceMaze[i][j];  // Copying each element
        }
    }

    // Env test_env(zlen, xlen);
    
    // char readChar;
    

    // for (unsigned int row = 0; row < zlen; row++) {
    //     for (unsigned int col = 0; col < xlen; col++) {
    //     readChar = maze[row][col];
    //     test_env.setEnvElement(row, col, readChar);
    //     }
    // }

    
    mcpp::Coordinate playerOrg = basePoint;
    build_x = playerOrg.x;
    build_y = playerOrg.y;
    build_z = playerOrg.z;

    std::cout << "Building at X: " << build_x << ", Y: " << build_y << ", Z: " << build_z << std::endl;
    mcpp::Coordinate startCoord(build_x, build_y, build_z);
    

    // end of constructor
}


    // Terraforms terrain
    // Goes through row by row
    void Maze::terraformTerrain() {
      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
          // Goes through column by column
          for (unsigned int col = 0; col < xlen; col++) {

            counter = build_y - mc.getHeight(build_x + row, build_z + col);
            if (counter > 0) {
                tempy = mc.getHeight(build_x + row, build_z + col) - build_y;
                block = mc.getBlock(startCoord+mcpp::Coordinate(row, tempy, col));
                for (int i = 0; i < counter; i++) {
                  mc.setBlock(startCoord+mcpp::Coordinate(row, tempy, col), block);
                  tempy++;
                }
            }
          }
      }
    }

    //Checks the terrain and stores the blocks in the way of the maze whilst clearing it
    void Maze::storeTerrain() {
      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
          for (unsigned int col = 0; col < xlen; col++) {
            for (int height = 0; height < 3; height++) {
                if (mc.getBlock(startCoord+mcpp::Coordinate(row, height, col)) != mcpp::Blocks::AIR) {
                mcpp::Coordinate currCoord;
                mcpp::BlockType currBlock;
                currCoord = startCoord+mcpp::Coordinate(row, height, col);
                currBlock = mc.getBlock(startCoord+mcpp::Coordinate(row, height, col));
                list.insert(currCoord, currBlock);

                std::cout << currCoord << std::endl;
                std::cout << currBlock << std::endl;


                mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
                }
            }
          }
      }
    }

    // Builds the maze according to maze structure 
    void Maze::buildMaze() {
      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
        for (unsigned int col = 0; col < xlen; col++) {
          for (int height = 0; height < 3; height++) {
            mc.setBlock(startCoord+mcpp::Coordinate(col, height, row), mcpp::Blocks::AIR);
              // If there is an x or X in the maze structure then place ACACIA_WOOD_PLANK
              if (maze[row][col] == 'x' || maze[row][col] == 'X') {

              // if (test_env.getEnvElement(row, col) == 'x' || test_env.getEnvElement(row, col) == 'X'){
                mc.setBlock(startCoord+mcpp::Coordinate(col, height, row), mcpp::Blocks::ACACIA_WOOD_PLANK);
              }
              else {
                if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
                  // Only place carpet on the first height layer (ground)
                  mc.setBlock(startCoord + mcpp::Coordinate(col, 0, row), mcpp::Blocks::BLUE_CARPET);
                }
              }
          }
        }
      }
    }

    // for (unsigned int row = 0; row < zlen; row++) {
    //     for (unsigned int col = 0; col < xlen; col++) {
    //       for (int height = 0; height < 3; height++) {
    //           mc.setBlock(startCoord+mcpp::Coordinate(col, height, row), mcpp::Blocks::AIR);
    //           if (test_env.getEnvElement(row, col) == 'x'){
    //             std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //             mc.setBlock(startCoord+mcpp::Coordinate(col, height, row), mcpp::Blocks::ACACIA_WOOD_PLANK);
    //           }
    //           else {
    //             if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
    //               mc.setBlock(startCoord+mcpp::Coordinate(col, 0, row), mcpp::Blocks::BLUE_CARPET);
    //             }
    //           }
              
    //       }
    //     }
    // }
    // for (unsigned int row = 0; row < zlen; row++) {
    //     for (unsigned int col = 0; col < xlen; col++) {
    //       for (int height = 0; height < 3; height++) {
    //           mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
    //           if (test_env.getEnvElement(row, col) == 'x'){
    //             mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::ACACIA_WOOD_PLANK);
    //           }
    //           else {
    //             if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
    //               mc.setBlock(startCoord+mcpp::Coordinate(row, 0, col), mcpp::Blocks::BLUE_CARPET);
    //             }
    //           }
              
    //       }
    //     }
    // }


// Restores the terrain back to how it was before clearing the area
// void Maze::exitCleanUp() {
//   mcpp::Coordinate startCoord(build_x, build_y, build_z);
//   for (unsigned int row = 0; row < xlen; row++) {
//       for (unsigned int col = 0; col < zlen; col++) {
//         for (int height = 0; height < 3; height++) {
//             if (mc.getBlock(startCoord+mcpp::Coordinate(row, height, col)) != mcpp::Blocks::AIR) {
//               mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
//             }
//         }
//       }
//   }
//   list.placeback();
// }


Maze::~Maze()
{
  for (unsigned int i = 0; i < zlen; i++) {
    delete[] maze[i];
  }
  delete[] maze;

  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  for (unsigned int row = 0; row < xlen; row++) {
      for (unsigned int col = 0; col < zlen; col++) {
        for (int height = 0; height < 3; height++) {
          mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
        }
      }
  }
  list.placeback();

}

