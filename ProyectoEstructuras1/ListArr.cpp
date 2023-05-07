#include "ListArr.h"
#include <iostream>
#include <math.h>

using namespace std;

ListArr::ListArr(int arrCapacity) {
    this->arrCapacity = arrCapacity;
    this->head = new ListNode(arrCapacity);
    this->listSize = 1;
    int n = calcularNiveles(listSize); //cuantos niveles tendrá el arbol
    this->raiz = crearArbol(n);
    unirArbol(n, raiz, head);
    actualizarArbol(n, raiz);
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
void ListArr::unirArbol(int niveles, SumNode* raiz, ListNode* head) {
    if(niveles == 1) {
        raiz->listaIzq = head;
        if(head == nullptr) {
            raiz->listaDer = nullptr;
        } else {
            raiz->listaDer = head->next;
        }
    } else {
        unirArbol(niveles - 1, raiz->izq, head);
        for(int i = 0; i < pow(2, niveles) / 2; i++) {
            if(head == nullptr or head->next == nullptr) {
                head = nullptr;
                break;
            } else {
                head = head->next;
            }
        }
        unirArbol(niveles - 1, raiz->der, head);
    }
}
void ListArr::actualizarArbol(int niveles, SumNode* raiz) {
    if(niveles == 1) {
        raiz->actualizar();
    } else {
        actualizarArbol(niveles - 1, raiz->izq);
        actualizarArbol(niveles - 1, raiz->der);
        raiz->actualizar();
    }
}