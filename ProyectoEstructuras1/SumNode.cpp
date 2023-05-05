#include "SumNode.h"
#include <iostream>

using namespace std;

SumNode::SumNode() {
    this->capacity = 0;
    this->size = 0;
    this->izq = nullptr;
    this->der = nullptr;
}
void SumNode::insertDer(Node* der) {
    this->der = der;
}
void SumNode::insertIzq(Node* izq) {
    this->izq = izq;
}
void SumNode::actualizar() {
    if(izq == nullptr and der == nullptr) {
        this->capacity = 0;
        this->size = 0;
    } else if(izq == nullptr) {
        this->capacity = der->getCapacity();
        this->size = der->getSize();
    } else if(der == nullptr) {
        this->capacity = izq->getCapacity();
        this->size = izq->getSize();
    } else {
        this->capacity = izq->getCapacity() + der->getCapacity();
        this->size = izq->getSize() + der->getSize();
    }
}