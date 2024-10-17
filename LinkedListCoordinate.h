#ifndef LINKEDLISTCOORDINATE
#define LINKEDLISTCOORDINATE
#include <iostream>
#include <mcpp/mcpp.h>
#include "Node.h"

class LinkedListCoordinate {
    private:
        Node* head; // Pointer to the first node in the list

    public:
        mcpp::MinecraftConnection mc;
        LinkedListCoordinate();
        void insert(mcpp::Coordinate coordinate, mcpp::BlockType blockType);
        void placeback();
        ~LinkedListCoordinate();
};

#endif