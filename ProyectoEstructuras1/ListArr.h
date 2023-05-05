#include "ListArrADT.h"
#include "ListNode.h"
#include "SumNode.h"
#ifndef ListArr_H
#define ListArr_H

class ListArr: public ListArrADT {
private:
    int arrCapacity; //Capacidad de los arreglos internos
    ListNode* head;
    SumNode* raiz;
    void actualizarArbol();
    void unirArbol();
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