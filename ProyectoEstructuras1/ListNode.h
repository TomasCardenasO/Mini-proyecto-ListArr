#ifndef ListNode_H
#define ListNode_H

class ListNode {
private:
    int capacity;
    int size;
    int* arr; //arreglo de enteros
public:
    ListNode* next; //puntero al siguiente ListNode

    ListNode(int);
    ~ListNode();
    int getCapacity();
    int getSize();
};

#endif