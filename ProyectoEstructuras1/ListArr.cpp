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

}
void ListArr::insert(int valor, int indice) {
    //tenemos que tomar en cuenta el indice. Pues necesitamos buscar el listnode adecuado.
    SumNode* auxiliar = raiz;                    //recordar
    for (int i = 0; i < calcularNiveles(listSize)) {
        if (i == 0) { 
            if (indice > aux->izq->getSize()) {
                auxiliar = auxiliar->izq;
            }
            else {
                auxiliar = auxiliar->der;
            }
        }
        else {
            if (indice > aux->izq->getSize()) {
                auxiliar = auxiliar->izq;
            }
            else {
                auxiliar = aux->der;
                indice = indice - auxiliar->izq->getSize();

            }
        }
    }
    //en este punto ya llegamos al sumnode deseado
    if (indice > auxiliar->listaIzq->getSize()) {           //pueden mejorar las condiciones, pero el tema es que esta condición es para verificar si trabajamos con listader o listaizq
        int copia[arrCapacity] = auxiliar->listaIzq->arr//copia de nuestro arreglo  
        if (indice != auxiliar->listaIzq->getSize()) {          //y conociendo eso, tenemos 2 posibles casos, que el arreglo esté lleno o no
            for (int i = 0; i <= auxiliar->listaIzq->getSize(); i++) { //en este caso no está lleno, asi que es suficiente con copiar los datos
                if (i < indice) {
                    auxiliar->listaIzq->arr[i] = copia[i];

                }                                           //hasta encontrarse con el indice, copiarlo
                else if (i == indice) {
                    auxiliar->listaIzq->arr[i] = valor;
                }
                else {
                    auxiliar->listaIzq->arr[i] = copia[i - 1];                //y luego seguir copiando los datos de antes.
                }
            }

        }                                                    
        else {
            for (int i = 0; i <= auxiliar->listaDer->getSize(); i++) {            // el otro caso es que el nodo ya esté lleno, asi que hacemos lo mismo
                if (i < indice) {
                    auxiliar->listaIzq->arr[i] = copia[i];

                }
                else if (i == indice) {
                    auxiliar->listaIzq->arr[i] = valor;
                }
                else {
                    auxiliar->listaIzq->arr[i] = copia[i - 1];
                }
            }
             ListNode* nuevo = new ListNode(arrCapacity);            //pero esta vez le estamos creando un nuevo nodo
            nuevo->arr[0] = copia[arrCapacity - 1];  //al nuevo nodo le damos el último valor de la copia
            nuevo->next = auxiliar->listaIzq->next; //conecto nuevo con el next anterior  auxiliar->listIzq->next
            auxiliar->listaIzq->next = nuevo; //se conecta nuestor head con nuevo y nuevo con el next de antes    
            listSize++;
            destruirArbol(calcularNiveles(listSize), raiz);
            crearArbol(calcularNiveles(listSize));
            unirArbol(calcularNiveles(listSize), raiz, head);
            actualizarArbol(calcularNiveles(listSize), raiz);
         
    }
    else {
        int copia[arrCapacity] = auxiliar->listaDer->arr//copia de nuestro arreglo            acá es lo mismo, pero con el listder

        if (indice != auxiliar->listaDer->getSize()) {
            for (int i = 0; i <= auxiliar->listaDer->getSize(); i++) {
                if (i < indice) {
                    auxiliar->listaDer->arr[i] = copia[i];

                }
                else if (i == indice) {
                    auxiliar->listaDer->arr[i] = valor;
                }
                else {
                    auxiliar->listaDer->arr[i] = copia[i - 1];
                }
            }

        }                                                    
        else {
            for (int i = 0; i <= auxiliar->listaDer->getSize(); i++) {
                if (i < indice) {
                    auxiliar->listaDer->arr[i] = copia[i];

                }
                else if (i == indice) {
                    auxiliar->listaDer->arr[i] = valor;
                }
                else {
                    auxiliar->listaDer->arr[i] = copia[i - 1];
                }
            }
            ListNode* nuevo = new ListNode(arrCapacity);
            nuevo->arr[0] = copia[arrCapacity - 1];  //al nuevo nodo le damos el último valor de la copia
            nuevo->next = auxiliar->listaDer->next; //conecto nuevo con el next anterior  auxiliar->listIzq->next
            auxiliar->listaDer->next = nuevo; //se conecta nuestor head con nuevo y nuevo con el next de antes    
            listSize++;
            destruirArbol(calcularNiveles(listSize), raiz);
            crearArbol(calcularNiveles(listSize));
            unirArbol(calcularNiveles(listSize), raiz, head);
            actualizarArbol(calcularNiveles(listSize), raiz);
        }

    }
}
void ListArr::insert_left(int valor) {
    int copia[arrCapacity] = head->arr //copia de nuestro arreglo 


        if (head->getSize() < head->getCapacity()) {   //si hay espacio, entonces 
            for (int i = 0; i <= head->getSize(); i++) {
                if (i == 0) {
                    head->arr[0] = valor;  //ponemos el valor en la posición 0
                }
                else {
                    head->arr[i] = copia[i - 1]; //se copian los valores de copia en arr
                }
            }
        }
        else {
            for (int i = 0; i <= head->getSize(); i++) { //si el espacio está lleno (tal vez puedo específicar más)
                if (i == 0) {
                    head->arr[0] = valor;
                }
                else {
                    head->arr[i] = copia[i - 1];
                }
            }//hacemos la misma copia que antes, pero tenemos que crear un nuevo nodo
            ListNode* nuevo = new ListNode(arrCapacity);
            nuevo->arr[0] = copia[arrCapacity - 1];  //al nuevo nodo le damos el último valor de la copia
            nuevo->next = head->next; //conecto nuevo con el next anterior
            head->next = nuevo; //se conecta nuestor head con nuevo y nuevo con el next de antes
            listSize++;
            destruirArbol(calcularNiveles(listSize), raiz);
            crearArbol(calcularNiveles(listSize));
            unirArbol(calcularNiveles(listSize), raiz, head);
            actualizarArbol(calcularNiveles(listSize), raiz);

        }




}
void ListArr::insert_right(int valor) {
    ListNode* aux = head; //creamos un arreglo que nos permita llegar hasta el último listndode
    for (int i = 0; i < listSize; i++) {
        aux = aux->next; //no es necesario el if, pues solo recorre hasta listsize

    }
    if (aux->getSize() == aux->getCapacity()) { //si la capacidad está llena
        //creamos nuevo nodo
        ListNode* nuevo = new ListNode(arrCapacity);
        nuevo->arr[0] = valor; //al nuevo nodo le asignamos el valor dado
        aux->next = nuevo; //al nodo auxiliar, el cual es el ultimo, le asignamos como next al nuevo nodo
        listSize++;
        destruirArbol(calcularNiveles(listSize), raiz);
        crearArbol(calcularNiveles(listSize));
        unirArbol(calcularNiveles(listSize), raiz, head);
        actualizarArbol(calcularNiveles(listSize), raiz);

    }
    else() {
        aux->arr[aux->getSize()] = valor //si la capacidad no está llena
    }

}
void ListArr::print() {

}
bool ListArr::find(int valor) {

}
int ListArr::delete_left() {

}
int ListArr::delete_right() {

}