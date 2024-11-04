#include "Maze.h"
#include <random>
#include <mcpp/mcpp.h>

Maze::Maze() {}

// Constructor 
Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                    unsigned int zlen,
                                    bool mode, char** sourceMaze)
{
  
  // Separates the players x,y,z coordinates
  this->basePoint = basePoint;
  this->xlen = xlen;
  this->zlen = zlen;
  this->mode = mode;
    
  mc.doCommand("time set day");

  // Builds a 2D char pointer to have the same rows and columns to the 
  // sourceMaze using xlen and zlen
  this->maze = new char*[xlen];
  for (unsigned int i = 0; i < xlen; ++i) {
      this->maze[i] = new char[zlen];
      for (unsigned int j = 0; j < zlen; ++j) {
          this->maze[i][j] = sourceMaze[i][j];  // Copying each element
      }
  }
  //
  playerOrg = basePoint;
  build_x = playerOrg.x;
  build_y = playerOrg.y;
  build_z = playerOrg.z;

  std::cout << "Building at X: " << build_x << ", Y: " << build_y <<\
   ", Z: " << build_z << std::endl;
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  

  // end of constructor
}


void Maze::scanTerrain() {
  // Gets the maxHeight of the heighest obstacle in the maze's area
  maxHeight = mc.getHeight(build_x, build_z);
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  for (unsigned int row = 0; row < zlen; row++) {
      for (unsigned int col = 0; col < xlen; col++) {
        // If current height is greater than maxHeight reasign it to max height
        if ((mc.getHeight(build_x + col, build_z + row)) > maxHeight) {
          maxHeight = mc.getHeight(build_x + col, build_z + row);
        }
        // if (mc.getHeight(build_x + col, build_z + row) > build_y) {

        // }
      }
  }
  
  maxHeight -= (build_y - 1);

}
// Terraforms terrain
// Goes through row by row
void Maze::terraformTerrain() {
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  // Goes through row by row
  for (unsigned int row = 0; row < zlen; row++) {
      // Goes through column by column
      for (unsigned int col = 0; col < xlen; col++) {
        // Creates a counter based on the height difference between player's
        // y position and each position in the maze
        counter = (build_y - 1) - mc.getHeight(build_x + row, build_z + col); 
        if (counter > 0) { 
          // Gets the height of the block that is below the player's y
          // position
          tempy = mc.getHeight(build_x + row, build_z + col) - build_y;
          // Gets the block at that position
          block = mc.getBlock(startCoord+mcpp::Coordinate(row, tempy, col));
          for (int i = 0; i < counter; i++) {
            currCoord = startCoord+mcpp::Coordinate(row, tempy + 1, col);
            // Places block at the currCoord's coordinates which is one 
            // block heigher than the current block 
            mc.setBlock(currCoord, block);
            // Delays each iteration by 50 milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            // Inserts the coordinates of the block into a linked list with
            // the block type of AIR
            list.insert(currCoord, mcpp::Blocks::AIR);
            tempy++;
          }
        }
      }
  }
}

//Checks the terrain and stores any obstacles in the maze whilst clearing it
void Maze::storeTerrain() {
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  for (unsigned int row = 0; row < zlen; row++) {
      for (unsigned int col = 0; col < xlen; col++) {
        for (int height = maxHeight; height >= 0; height--) {
            if (mc.getBlock(startCoord+mcpp::Coordinate(row, height, col))\
              != mcpp::Blocks::AIR) {

              // Delays each iteration by 50 milliseconds
              std::this_thread::sleep_for(std::chrono::milliseconds(50));
              currCoord = startCoord+mcpp::Coordinate(row, height, col);
              currBlock = mc.getBlock(startCoord+mcpp::Coordinate\
              (row, height, col));
              // First inserts the coordinates of the block into a linked list
              // with the blocktype of the block
              list.insert(currCoord, currBlock);

              // std::cout << currCoord << std::endl;
              // std::cout << currBlock << std::endl;

              // Then sets the block to AIR
              mc.setBlock(startCoord+mcpp::Coordinate(row, height, col)\
              , mcpp::Blocks::AIR);
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
        // If there is an x or X in the maze structure then place 
        // ACACIA_WOOD_PLANK
        if (maze[col][row] == 'x' || maze[col][row] == 'X') {
          // Delays each iteration by 50 milliseconds
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          currCoord = startCoord+mcpp::Coordinate(row, tempy, col);
          currBlock = mcpp::Blocks::ACACIA_WOOD_PLANK;
          mc.setBlock(currCoord, currBlock);
          tempy++;

        }
        else {
          // If x or X is on the sides of the maze structure place a 
          // blue carpet
          if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
            // Only place carpet on the first height layer (ground)
            mc.setBlock(startCoord + mcpp::Coordinate(row, 0, col)\
            , mcpp::Blocks::BLUE_CARPET);
          }
        }
      }
    }
  }
}

// Enhancement 
void Maze::scanTerrainEnhancement() {
  EnhancementMode = true;
  // Uses GenerateMaze class's constructor
  GenerateMaze mazeStruc(xlen, zlen, playerOrg);
  // Generates a random maze
  mazeStruc.GenerateRandMaze();
  // Assign vec to the random generated maze
  vec = mazeStruc.getMazeVec();
  // Prints out the base random generated maze
  std::cout << "First Maze:" << std::endl;
  for (unsigned int row = 0; row < zlen; row++) {
      for (unsigned int col = 0; col < xlen; col++) {
        std::cout << vec[row][col];
      }
      std::cout << std::endl;
  }
  // Adds in the obstacles with height of greater than 1 into 
  // the maze structure
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  for (unsigned int row = 0; row < zlen; row++) {
      for (unsigned int col = 0; col < xlen; col++) {
        if ((mc.getHeight(build_x + col, build_z + row) - build_y) > 0) {
          vec[row][col] = '\\';
        }
      }
  }
  std::cout << "Mid Maze:" << std::endl;
  for (unsigned int row = 0; row < zlen; row++) {
      for (unsigned int col = 0; col < xlen; col++) {
        std::cout << vec[row][col];
      }
      std::cout << std::endl;
  }
  // Based on the obstacles carves a maze to build around them
  mazeStruc.setMaze(vec);
  mazeStruc.carveMaze();
  vec = mazeStruc.getMazeVec();

  
  std::cout << "Final Maze:" << std::endl;
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

// Enhancement 
void Maze::buildMazeEnhancement() {
  mcpp::Coordinate startCoord(build_x, build_y, build_z);
  for (unsigned int row = 0; row < zlen; row++) {
    for (unsigned int col = 0; col < xlen; col++) {
      tempy = mc.getHeight(build_x + row, build_z + col) - build_y + 1;
      for (int height = 0; height < 3; height++) {
        // If there is an x or X in the maze structure then place 
        // ACACIA_WOOD_PLANK
        if (maze[col][row] == 'x' || maze[col][row] == 'X') {
          // Delays each iteration by 50 milliseconds
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          currCoord = startCoord+mcpp::Coordinate(row, tempy, col);
          currBlock = mcpp::Blocks::ACACIA_WOOD_PLANK;
          mc.setBlock(currCoord, currBlock);
          // Inserts the coordinates of the block and block type AIR
          list.insert(currCoord, mcpp::Blocks::AIR);
          tempy++;

        }
        else if (maze[col][row] == '.') {
          if (row == 0 || row == (zlen - 1) || col == 0 || col == (xlen - 1)) {
            // If x or X is on the sides of the maze structure place a 
            // BLUE_CARPET
            mc.setBlock(startCoord + mcpp::Coordinate(row, tempy, col)\
            , mcpp::Blocks::BLUE_CARPET);
            // Inserts the coordinates of the block and block type AIR
            list.insert(startCoord + mcpp::Coordinate(row, tempy, col)\
            , mcpp::Blocks::AIR);
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
          // Removes the maze by replacing it with AIR Blocks
          mc.setBlock(startCoord+mcpp::Coordinate(row, height, col)\
          , mcpp::Blocks::AIR);
        }
      }
  }
  // Places back the blocks using the LinkedList by the coordinates 
  // and blocktype stored
  list.placeback();
}

// Enhancement
void Maze::exitCleanUpEnhancement() {
  // Places back the blocks using the LinkedList by the coordinates 
  // and blocktype stored
  list.placeback();
}

// Destructor 
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