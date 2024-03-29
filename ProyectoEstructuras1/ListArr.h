#include "ListArrADT.h"
#include "ListNode.h"
#include "SumNode.h"
#ifndef ListArr_H
#define ListArr_H

class ListArr: public ListArrADT {
private:
    int arrCapacity; //Capacidad de los arreglos internos
    ListNode* head;
    int listSize;
    SumNode* raiz;
    int calcularNiveles(int);
    SumNode* crearArbol(int);
    void destruirArbol(int, SumNode*);
    void unirArbol(int, SumNode*, ListNode*);
    void actualizarArbol(int, SumNode*);
public:
    ListArr(int);
    ~ListArr();
    int size();
    void insert_left(int);
    void insert_right(int);
    void insert(int, int);
    void print();
    bool find(int);
    int delete_left();
    int delete_right();
};

#endif