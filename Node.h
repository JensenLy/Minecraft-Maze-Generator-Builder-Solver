#ifndef NODE 
#define NODE
#include <iostream>
#include <mcpp/mcpp.h>

class Node {
private:
    mcpp::Coordinate coordinate;    // coordinate object
    mcpp::BlockType blockType;      // blockType object
    Node* next;     // Pointer to the next nod
    
public:
    Node* getnext();
    mcpp::Coordinate getCoord();
    mcpp::BlockType getBlock();
    Node(mcpp::Coordinate c, mcpp::BlockType b);
    Node();
};

#endif 