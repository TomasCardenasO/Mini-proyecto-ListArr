#include "ListArr.h"
#include <iostream>
#include <math.h>

using namespace std;

ListArr::ListArr(int arrCapacity) {
    this->arrCapacity = arrCapacity;
    this->head = new ListNode(arrCapacity);
    this->listSize = 1;
    this->raiz = crearArbol(calcularNiveles(listSize), head);
}
int ListArr::calcularNiveles(int listSize) {
    int n = 1;
    while(listSize > pow(2, n)) {
        n += 1;
    }
    return n;
}
Node* ListArr::crearArbol(int niveles, ListNode* head) {
    if(niveles == 0) {
        return head;
    } else {
        SumNode* padre = new SumNode;
        padre->izq = crearArbol(niveles - 1, head);
        for(int i = 0; i < pow(2, niveles) / 2; i++) {
            if(head == nullptr or head->next == nullptr) {
                head = nullptr;
                break;
            } else {
                head = head->next;
            }
        }
        padre->der = crearArbol(niveles - 1, head);
        return padre;
    }
}