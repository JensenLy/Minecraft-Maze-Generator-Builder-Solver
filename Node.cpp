#include "Node.h"

Node::Node(mcpp::Coordinate c, mcpp::BlockType b) {
    this->coordinate = c;
    this->blockType = b;
}

Node* Node::getnext() {
    return this->next;
}

mcpp::Coordinate Node::getCoord() {
    return this->coordinate;
}

mcpp::BlockType Node::getBlock() {
    return this->blockType;
}


    

