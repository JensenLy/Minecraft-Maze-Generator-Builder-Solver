#include "Node.h"

// Node::Node() : next(nullptr) {}  // Always initialize next to nullptr

Node::Node(mcpp::Coordinate c, mcpp::BlockType b) {
    this->coordinate = c;
    this->blockType = b;
    next = nullptr;

}

Node* Node::getnext() {
    return this->next;
}

mcpp::Coordinate Node::getCoord() {
    return coordinate;
}

mcpp::BlockType Node::getBlock() {
    return blockType;
}

void Node::setnext(Node* node) {
    this->next = node;
}


    

