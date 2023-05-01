#include "Node.h"
#ifndef ListNode_H
#define ListNode_H

class ListNode: public Node {
private:
    //int capacity; (herencia)
    //int size; (herencia)
    int* arr;
    ListNode* next;
public:
    ListNode(int);
    ~ListNode();
    //int getCapacity(); (herencia)
    //int getSize(); (herencia)
};

#endif