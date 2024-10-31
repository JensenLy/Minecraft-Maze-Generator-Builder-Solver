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

    this->maze = new char*[xlen];
    for (unsigned int i = 0; i < xlen; ++i) {
        this->maze[i] = new char[zlen];
        for (unsigned int j = 0; j < zlen; ++j) {
            this->maze[i][j] = sourceMaze[i][j];  // Copying each element
        }
    }
    
    playerOrg = basePoint;
    build_x = playerOrg.x;
    build_y = playerOrg.y;
    build_z = playerOrg.z;

    std::cout << "Building at X: " << build_x << ", Y: " << build_y << ", Z: " << build_z << std::endl;
    mcpp::Coordinate startCoord(build_x, build_y, build_z);
    

    // end of constructor
}


    void Maze::scanTerrain() {
      maxheight = mc.getHeight(build_x, build_z);
      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
          for (unsigned int col = 0; col < xlen; col++) {
            if ((mc.getHeight(build_x + col, build_z + row)) > maxheight) {
              maxheight = mc.getHeight(build_x + col, build_z + row);
            }
            if (mc.getHeight(build_x + col, build_z + row) > build_y) {



            }
          }
      }
      
      maxheight -= (build_y - 1);

    }
    // Terraforms terrain
    // Goes through row by row
    void Maze::terraformTerrain() {
      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
          // Goes through column by column
          for (unsigned int col = 0; col < xlen; col++) {
            counter = (build_y - 1) - mc.getHeight(build_x + row, build_z + col);

            if (counter > 0) { 
              // Calculate the current terrain height
              tempy = mc.getHeight(build_x + row, build_z + col) - build_y;
              block = mc.getBlock(startCoord+mcpp::Coordinate(row, tempy, col));
              for (int i = 0; i < counter; i++) {
                mc.setBlock(startCoord+mcpp::Coordinate(row, tempy + 1, col), block);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                currCoord = startCoord+mcpp::Coordinate(row, tempy + 1, col);
                list.insert(currCoord, mcpp::Blocks::AIR);
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
            for (int height = maxheight; height >= 0; height--) {
                if (mc.getBlock(startCoord+mcpp::Coordinate(row, height, col)) != mcpp::Blocks::AIR) {
                  std::this_thread::sleep_for(std::chrono::milliseconds(50));
                  currCoord = startCoord+mcpp::Coordinate(row, height, col);
                  currBlock = mc.getBlock(startCoord+mcpp::Coordinate(row, height, col));
                  list.insert(currCoord, currBlock);

                  // std::cout << currCoord << std::endl;
                  // std::cout << currBlock << std::endl;
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
          tempy = mc.getHeight(build_x + row, build_z + col) - build_y + 1;
          for (int height = 0; height < 3; height++) {
            // mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
            // If there is an x or X in the maze structure then place ACACIA_WOOD_PLANK
            if (maze[col][row] == 'x' || maze[col][row] == 'X') {
              std::this_thread::sleep_for(std::chrono::milliseconds(50));
              currCoord = startCoord+mcpp::Coordinate(row, tempy, col);
              currBlock = mcpp::Blocks::ACACIA_WOOD_PLANK;
              mc.setBlock(currCoord, currBlock);
              tempy++;

            }
            else {
              if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
                // Only place carpet on the first height layer (ground)
                mc.setBlock(startCoord + mcpp::Coordinate(row, 0, col), mcpp::Blocks::BLUE_CARPET);
              }
            }
          }
        }
      }
    }

    void Maze::scanTerrainEnhancement() {
      EnhancementMode = true;
      GenerateMaze mazeStruc(xlen, zlen, playerOrg);
      mazeStruc.GenerateRandMaze();
      std::vector<std::vector<char>> vec = mazeStruc.getMazeVec();
      std::cout << "First Maze" << std::endl;
      for (unsigned int row = 0; row < zlen; row++) {
          for (unsigned int col = 0; col < xlen; col++) {
            std::cout << vec[row][col];
          }
          std::cout << std::endl;
      }

      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
          for (unsigned int col = 0; col < xlen; col++) {
            if ((mc.getHeight(build_x + col, build_z + row) - build_y) > 0) {
              vec[row][col] = '\\';
            }
          }
      }
      std::cout << "Mid Maze" << std::endl;
      for (unsigned int row = 0; row < zlen; row++) {
          for (unsigned int col = 0; col < xlen; col++) {
            std::cout << vec[row][col];
          }
          std::cout << std::endl;
      }
      mazeStruc.setMaze(vec);
      mazeStruc.carveMaze();
      vec = mazeStruc.getMazeVec();

      std::cout << "Final Maze" << std::endl;
      for (unsigned int row = 0; row < zlen; row++) {
          for (unsigned int col = 0; col < xlen; col++) {
            std::cout << vec[row][col];
          }
          std::cout << std::endl;
      }

      for (unsigned int row = 0; row < xlen; row++) {
          for (unsigned int col = 0; col < zlen; col++) {
            this->maze[row][col] = vec[row][col];
          }
      }
    }


    void Maze::buildMazeEnhancement() {
      mcpp::Coordinate startCoord(build_x, build_y, build_z);
      for (unsigned int row = 0; row < zlen; row++) {
        for (unsigned int col = 0; col < xlen; col++) {
          tempy = mc.getHeight(build_x + row, build_z + col) - build_y + 1;
          for (int height = 0; height < 3; height++) {
            // If there is an x or X in the maze structure then place ACACIA_WOOD_PLANK
            if (maze[col][row] == 'x' || maze[col][row] == 'X') {
              std::this_thread::sleep_for(std::chrono::milliseconds(50));
              currCoord = startCoord+mcpp::Coordinate(row, tempy, col);
              currBlock = mcpp::Blocks::ACACIA_WOOD_PLANK;
              mc.setBlock(currCoord, currBlock);
              list.insert(currCoord, mcpp::Blocks::AIR);
              tempy++;

            }
            else if (maze[col][row] == '.') {
              if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
                // Only place carpet on the first height layer (ground)
                mc.setBlock(startCoord + mcpp::Coordinate(row, tempy, col), mcpp::Blocks::BLUE_CARPET);
                list.insert(startCoord + mcpp::Coordinate(row, tempy, col), mcpp::Blocks::AIR);
              }
            }
          }
        }
      }
    }


// Restores the terrain back to how it was before clearing the area
void Maze::exitCleanUp() {
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  for (unsigned int row = 0; row < zlen; row++) {
      for (unsigned int col = 0; col < xlen; col++) {
        for (int height = 0; height < 3; height++) {
          mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
        }
      }
  }
  list.placeback();
}

void Maze::exitCleanUpEnhancement() {
  list.placeback();
}


Maze::~Maze()
{
  for (unsigned int i = 0; i < xlen; i++) {
    delete[] maze[i];
  }
  delete[] maze;

  if (EnhancementMode) {
    exitCleanUpEnhancement();
  }
  else {
    exitCleanUp();
  }

}