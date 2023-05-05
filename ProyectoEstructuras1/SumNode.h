#include "Node.h"
#ifndef SumNode_H
#define SumNode_H

class SumNode: public Node {
private:
    //int capacity; (herencia)
    //int size; (herencia)
    Node* izq;
    Node* der;
public:
    SumNode();
    void insertDer(Node*);
    void insertIzq(Node*);
    void actualizar();
    //int getCapacity(); (herencia)
    //int getSize(); (herencia)
};

#endif