#include "Maze.h"
#include "env.h"
#include "LinkedListCoordinate.h"
#include <random>
#include <mcpp/mcpp.h>
void ReadEnvSize(int &envLength, int &envWidth);
void readEnvStdin(char **EnvStruct, int length, int width);
void ReadBuildLocation(int &build_x, int &build_y, int &build_z);

Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                    unsigned int zlen,
                                    bool mode)
{
    mcpp::MinecraftConnection mc;
    mc.doCommand("time set day");
    int envLength = 0;
    int envWidth = 0;
    ReadEnvSize(envLength, envWidth);
    Env test_env(envLength, envWidth);
    std::cout << "Length: " << test_env.getLength() << ", Width: " << test_env.getWidth() << std::endl;
    char readChar;
    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
        std::cin >> readChar;
        test_env.setEnvElement(row, col, readChar);
        }
    }
    int build_x = 0;
    int build_y = 0;
    int build_z = 0;
    
    mcpp::Coordinate playerOrg = mc.getPlayerPosition();
    build_x = playerOrg.x;
    build_y = playerOrg.y;
    build_z = playerOrg.z;

    std::cout << "Building at X: " << build_x << ", Y: " << build_y << ", Z: " << build_z << std::endl;
    mcpp::Coordinate startCoord(build_x, build_y, build_z);
    mcpp::BlockType block;
    int tempy;
    int counter;

    // Goes through row by row
    for (int row = 0; row < envLength; row++) {
        // Goes through column by column
        for (int col = 0; col < envWidth; col++) {

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

    LinkedListCoordinate list;

    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
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


    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
        for (int height = 0; height < 3; height++) {
            mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
            if (test_env.getEnvElement(row, col) == 'x'){
            mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::ACACIA_WOOD_PLANK);
            }
        }
        }
    }

    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
        for (int height = 0; height < 3; height++) {
            if (mc.getBlock(startCoord+mcpp::Coordinate(row, height, col)) != mcpp::Blocks::AIR) {
            mc.setBlock(startCoord+mcpp::Coordinate(row, height, col), mcpp::Blocks::AIR);
            }
        }
        }
    }

    list.placeback();

}


Maze::~Maze()
{
}

void ReadEnvSize(int& envLength, int& envWidth){
  std::cout << "Enter the size of the rectangular environment (L, W): " << std::endl;
  std::cin >> envLength;
  std::cin >> envWidth;
}

void readEnvStdin(char **EnvStruct, int length, int width) {
  char readChar;
  for (int row = 0; row < length; row++) {
    for (int col = 0; col < width; col++) {
      std::cin >> readChar;
      EnvStruct[row][col] = readChar;
    }
  }
}

void ReadBuildLocation(int &build_x, int &build_y, int &build_z) {
  std::cin >> build_x;
  std::cin >> build_y;
  std::cin >> build_z;
}