#include "Node.h"
#ifndef SumNode_H
#define SumNode_H

class SumNode: public Node {
private:
    //int capacity; (herencia)
    //int size; (herencia)
public:
    Node* izq;
    Node* der;
    SumNode();
    void actualizar();
    //int getCapacity(); (herencia)
    //int getSize(); (herencia)
};

#endif