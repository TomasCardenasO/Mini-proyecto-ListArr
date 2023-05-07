#include "ListNode.h"
#ifndef SumNode_H
#define SumNode_H

class SumNode {
private:
    int capacity;
    int size;
public:
    SumNode* izq;
    SumNode* der;
    ListNode* listaIzq;
    ListNode* listaDer;

    SumNode();
    void actualizar();
    int getCapacity();
    int getSize();
};

#endif