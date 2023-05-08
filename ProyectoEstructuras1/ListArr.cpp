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
ListArr::~ListArr() {
    destruirArbol(calcularNiveles(listSize), raiz);
    ListNode* copyhead = head;
    for(int i = 0; i < listSize; i++) {
        copyhead = copyhead->next;
        head->~ListNode();
        head = copyhead;
    }
}
/*##################################################################################################
                                            METODOS PRIVADOS
###################################################################################################*/
/*Para calcular los niveles del arbol (n) segun la cantidad de nodos de la lista (listSize) 
hay que tener en cuenta que el nivel "n" puede almacenar 2^n nodos (ya que es un arbol binario). 
Por lo tanto, cuando el numero de nodos sea menor o igual a 2^n tendremos un arbol lo 
necesariamente grande para contener la lista*/
int ListArr::calcularNiveles(int listSize) {
    int n = 1;
    while(listSize > pow(2, n)) {
        n += 1;
    }
    return n;
}
/*Para crear un arbol de n niveles basicamente en cada hijo (izquierdo y derecho) asignamos un arbol
de nivel n-1*/
SumNode* ListArr::crearArbol(int niveles) {
    if(niveles == 0) {
        return nullptr;
    } else {
        SumNode* raiz = new SumNode;
        raiz->izq = crearArbol(niveles - 1);
        raiz->der = crearArbol(niveles - 1);
        return raiz;
    }
}
/*Para destruir un arbol de n niveles destruimos los subarboles de n-1 niveles (de la izquierda y derecha)
y luego destruimos la raiz, cuando se llega al nivel mas bajo simplemente destruimos el SumNode correspondiente*/
void ListArr::destruirArbol(int niveles, SumNode* raiz) {
    if(niveles == 1) {
        delete raiz;
    } else {
        destruirArbol(niveles - 1, raiz->izq);
        destruirArbol(niveles - 1, raiz->der);
        delete raiz;
    }
}
/*Para unir un arbol a una lista necesitamos los niveles del arbol (n), la raiz del arbol y el puntero al primer
elemento de la lista. En el caso general (el arbol y la lista entera) vamos a subdividir el problema, tomaremos
el subarbol izquierdo y derecho, los cuales tienen nivel n-1, y dividiremos la lista por la mitad 
(con el ciclo for), esto se subdivide hasta llegar al nivel mas bajo del arbol, donde uniremos el
SumNode con los nodos de la lista*/
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
/*Para actualizar el arbol usamos la misma idea que en los metodos anteriores, primero actualizamos el
subarbol izquierdo y derecho y luego el padre, cuando lleguemos al nivel mas bajo simplente actualizamos
los SumNode (el metodo actualizar de los SumNode funciona sin importar a que tipo de nodo estemos apuntando)*/
void ListArr::actualizarArbol(int niveles, SumNode* raiz) {
    if(niveles == 1) {
        raiz->actualizar();
    } else {
        actualizarArbol(niveles - 1, raiz->izq);
        actualizarArbol(niveles - 1, raiz->der);
        raiz->actualizar();
    }
}
/*##################################################################################################
                                            METODOS PUBLIC
###################################################################################################*/
int ListArr::size() {
    return raiz->getSize();
}

void ListArr::insert(int valor, int indice) {

}
void ListArr::insert_left(int valor) {

}
void ListArr::insert_right(int valor) {

}
void ListArr::print() {
    ListNode* nodo = head; 
    for (int i = 0; i < listSize; i++){
        for (int j = 0; j < nodo->getSize(); j++){
            cout << nodo->arr[j];
        }
    nodo = nodo->next;
    }
}
bool ListArr::find(int valor) {

}
int ListArr::delete_left() {
    
}
int ListArr::delete_right() {

}