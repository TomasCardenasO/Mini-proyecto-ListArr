#include "SumNode.h"
#include <iostream>

using namespace std;

SumNode::SumNode() {
    this->capacity = 0;
    this->size = 0;
    this->izq = nullptr;
    this->der = nullptr;
    this->listaIzq = nullptr;
    this->listaDer = nullptr;
}
void SumNode::actualizar() {
    if(izq != nullptr and der != nullptr) {
        this->capacity = izq->getCapacity() + der->getCapacity();
        this->size = izq->getSize() + der->getSize();
    } else if(listaIzq == nullptr and listaDer == nullptr){
        this->capacity = 0;
        this->size = 0;
    } else if(listaDer == nullptr) {
        this->capacity = listaIzq->getCapacity();
        this->size = listaIzq->getSize();
    } else {
        this->capacity = listaIzq->getCapacity() + listaDer->getCapacity();
        this->size = listaIzq->getSize() + listaDer->getSize();
    }
}
int SumNode::getCapacity() {
    return capacity;
}
int SumNode::getSize() {
    return size;
}