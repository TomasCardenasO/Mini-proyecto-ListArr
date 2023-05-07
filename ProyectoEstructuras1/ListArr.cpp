#include "ListArr.h"
#include <iostream>
#include <math.h>

using namespace std;

ListArr::ListArr(int arrCapacity) {
    this->arrCapacity = arrCapacity;
    this->head = new ListNode(arrCapacity);
    this->listSize = 1;
    this->raiz = crearArbol(calcularNiveles(listSize));
}
int ListArr::calcularNiveles(int listSize) {
    int n = 1;
    while(listSize > pow(2, n)) {
        n += 1;
    }
    return n;
}
SumNode* ListArr::crearArbol(int niveles) {
    if(niveles == 0) {
        return nullptr;
    } else {
        SumNode* padre = new SumNode;
        padre->izq = crearArbol(niveles - 1);
        padre->der = crearArbol(niveles - 1);
        return padre;
    }
}