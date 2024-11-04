#include "LinkedListCoordinate.h"

    LinkedListCoordinate::LinkedListCoordinate() : head(nullptr) {}

    // Function to insert a new node with a coordinate and blockType object
    void LinkedListCoordinate::insert\
    (mcpp::Coordinate coordinate, mcpp::BlockType blockType) {
        // Create a new node with a coordinate and blockType object
        Node* newNode = new Node(coordinate, blockType);  

        // If the list is empty, set the new node as the head
        if (head == nullptr) {
            head = newNode;
        }
        else {
            // Traverse the list to find the last node
            Node* temp = head;
            while (temp->getnext() != nullptr) {
                temp = temp->getnext();
            }
            // Link the last node to the new node
            temp->setnext(newNode);
        }
    }

    // Goes through the linkedList till a nullptr is reached
    void LinkedListCoordinate::placeback() {
      Node* temp = head;
      while (temp != nullptr) {
          mc.setBlock(temp->getCoord(), temp->getBlock());
          temp = temp->getnext();
      }
    }

    // Destructor to free memory
    LinkedListCoordinate::~LinkedListCoordinate() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->getnext();
            delete current;
            current = nextNode;
        }
    }
