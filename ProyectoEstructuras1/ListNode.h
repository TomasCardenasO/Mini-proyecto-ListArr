#ifndef ListNode_H
#define ListNode_H

class ListNode {
private:
    int capacity;
    int size;
public:
    ListNode* next; //puntero al siguiente ListNode
    int* arr; //arreglo de enteros
    ListNode(int);
    ~ListNode();
    int getCapacity();
    int getSize();
};

#endif