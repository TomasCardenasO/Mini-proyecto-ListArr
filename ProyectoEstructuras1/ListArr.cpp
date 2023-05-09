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
los SumNode (el metodo actualizar de los SumNode funciona sin importar a que tipo de nodo estemos apuntando)www*/
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
    //tenemos que tomar en cuenta el indice. Pues necesitamos buscar el listnode adecuado.
    SumNode* auxiliar = raiz;
    ListNode* listaux;
    if(indice > raiz->getSize()) {
        cout << "El indice requerido no es valido, pruebe con un indice menor." << endl;
    } else {
        for (int i = 0; i < calcularNiveles(listSize) - 1; i++) {
            if(indice > auxiliar->izq->getSize()) {
                indice = indice - auxiliar->izq->getSize();
                auxiliar = auxiliar->der;
            } else {
                auxiliar = auxiliar->izq;
            }
        } //en este punto ya llegamos al sumnode deseado
        if(indice > auxiliar->listaIzq->getSize()) {
            listaux = auxiliar->listaDer;
        } else {
            listaux = auxiliar->listaIzq;
        } //en este punto llegamos al listnode deseado
        if(indice == listaux->getCapacity()) {
            ListNode* nuevo = new ListNode(arrCapacity);
            nuevo->arr[0] = valor;
            nuevo->size += 1;
            nuevo->next = listaux->next;
            listaux->next = nuevo;
            listSize++;
            destruirArbol(calcularNiveles(listSize - 1), raiz);
            raiz = crearArbol(calcularNiveles(listSize));
            unirArbol(calcularNiveles(listSize), raiz, head);
            actualizarArbol(calcularNiveles(listSize), raiz);
        } else {
            if(listaux->getSize() == listaux->getCapacity()) {
                ListNode* nuevo = new ListNode(arrCapacity);
                nuevo->arr[0] = listaux->arr[listaux->getSize() - 1];
                nuevo->size += 1;
                nuevo->next = listaux->next;
                listaux->next = nuevo;
                listSize++;
                int* arraux = new int[arrCapacity];
                for(int i = 0; i < listaux->getSize(); i++) {
                    if(i < indice) {
                        arraux[i] = listaux->arr[i];
                    } else if(i == indice) {
                        arraux[i] == valor;
                    } else {
                        arraux[i] = listaux->arr[i - 1];
                    }
                }
                delete[] listaux->arr;
                listaux->arr = arraux;
                destruirArbol(calcularNiveles(listSize - 1), raiz);
                raiz = crearArbol(calcularNiveles(listSize));
                unirArbol(calcularNiveles(listSize), raiz, head);
                actualizarArbol(calcularNiveles(listSize), raiz);
            } else {
                int* arraux = new int[arrCapacity];
                for(int i = 0; i < listaux->getSize(); i++) {
                    if(i < indice) {
                        arraux[i] = listaux->arr[i];
                    } else if(i == indice) {
                        arraux[i] == valor;
                    } else {
                        arraux[i] = listaux->arr[i - 1];
                    }
                }
                delete[] listaux->arr;
                listaux->arr = arraux;
                listaux->size += 1;
                actualizarArbol(calcularNiveles(listSize), raiz);
            }
        }
    }
}
void ListArr::insert_left(int valor) {
    if (head->getSize() < head->getCapacity()) {   //si hay espacio, entonces
        for (int i = head->getSize(); i > 0; i--) {
            head->arr[i] = head->arr[i - 1];
        }
        head->arr[0] = valor;
        head->size += 1;
        actualizarArbol(calcularNiveles(listSize), raiz);
    } else {
        ListNode* nuevo = new ListNode(arrCapacity);
        nuevo->arr[0] = valor;
        nuevo->size += 1;
        nuevo->next = head;
        head = nuevo;
        listSize++;
        destruirArbol(calcularNiveles(listSize - 1), raiz);
        raiz = crearArbol(calcularNiveles(listSize));
        unirArbol(calcularNiveles(listSize), raiz, head);
        actualizarArbol(calcularNiveles(listSize), raiz);
    }
}
void ListArr::insert_right(int valor) {
    SumNode* aux = raiz;
    ListNode* listaux;
    for(int i = 0; i < calcularNiveles(listSize)- 1; i++) {
        if(aux->der->getSize() != 0) {
            aux = aux->der;
        } else {
            aux = aux->izq;
        }
    } //en este punto nos posicionamos en el SumNode que tiene el ultimo indice
    if(aux->listaDer == nullptr or aux->listaDer->getSize() == 0) {
        listaux = aux->listaIzq;
    } else {
        listaux = aux->listaDer;
    } //en este punto nos posicionamos en el listNode que contiene el ultimo indice

    if (listaux->getSize() == listaux->getCapacity()) { //si la capacidad está llena
        //creamos nuevo nodo
        ListNode* nuevo = new ListNode(arrCapacity);
        nuevo->arr[0] = valor; //al nuevo nodo le asignamos el valor dado
        nuevo->size += 1;
        nuevo->next = listaux->next;
        listaux->next = nuevo; //al nodo auxiliar, el cual es el ultimo, le asignamos como next al nuevo nodo
        listSize++;
        destruirArbol(calcularNiveles(listSize - 1), raiz);
        raiz = crearArbol(calcularNiveles(listSize));
        unirArbol(calcularNiveles(listSize), raiz, head);
        actualizarArbol(calcularNiveles(listSize), raiz);
    } else {
        listaux->arr[listaux->getSize()] = valor; //si la capacidad no está llena
        listaux->size += 1;
        actualizarArbol(calcularNiveles(listSize), raiz);
    }
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
    ListNode* copyhead = head;
    for(int i = 0; i < listSize; i++) {
        for(int j = 0; j < copyhead->getSize(); j++) {
            if(copyhead->arr[j] == valor) {
                return true;
            }
        }
        copyhead = copyhead->next;
    }
    return false;
}
int ListArr::delete_left() {
    SumNode* aux = raiz;
    ListNode* listaux;
    if(raiz->getSize() == 0) {
        cout << "No podemos eliminar elementos ya que ListArr esta vacio" << endl;
        return -1;
    } else {
        for(int i = 0; i < calcularNiveles(listSize) - 1; i++) {
            if(aux->izq->getSize() != 0) {
                aux = aux->izq;
            } else {
                aux = aux->der;
            }
        } //en este punto aux va a ser el SumNode que contiene el ListNode con el primer elemento
        if(aux->listaIzq->getSize() != 0) {
            listaux = aux->listaIzq;
        } else {
            listaux = aux->listaDer;
        }//en este punto listaux es el ListNode que contiene al primer elemento
        if(listaux->getSize() == 1) {
            listaux->size -= 1;
            actualizarArbol(calcularNiveles(listSize), raiz);
            return listaux->arr[0];
        } else {
            int salida = listaux->arr[0];
            for(int i = 1; i < listaux->getSize(); i++) {
                listaux->arr[i - 1] = listaux->arr[i];
            }
            listaux->size -= 1;
            actualizarArbol(calcularNiveles(listSize), raiz);
            return salida;
        }

    }
}
int ListArr::delete_right() {
    SumNode* aux = raiz;
    ListNode* listaux;
    if(raiz->getSize() == 0) {
        cout << "No podemos eliminar elementos ya que ListArr esta vacio" << endl;
        return -1;
    } else {
        for(int i = 0; i < calcularNiveles(listSize) - 1; i++) {
            if(aux->der->getSize() != 0) {
                aux = aux->der;
            } else {
                aux = aux->izq;
            }
        } //en este punto aux va a ser el SumNode que contiene el ListNode con el ultimo elemento
        if(aux->listaDer->getSize() != 0) {
            listaux = aux->listaDer;
        } else {
            listaux = aux->listaIzq;
        }//en este punto listaux es el ListNode que contiene al ultimo elemento
        listaux->size -= 1;
        return listaux->arr[listaux->getSize()];
    }
}