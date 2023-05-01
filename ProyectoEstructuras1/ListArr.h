#include "ListArrADT.h"
#ifndef ListArr_H
#define ListArr_H

class ListArr: public ListArrADT {
private:
    int arrCapacity; //Capacidad de los arreglos internos
    struct ListNode {
        int arrCapacity;
        int* arr;
        int size;
        ListNode* next;
        ListNode(int arrCapacity) {
            this->arrCapacity = arrCapacity;
            this->arr = new int[arrCapacity];
            this->size = 0;
            this->next = nullptr;
        }
        ~ListNode() {
            delete[] arr;
        }
    };
    struct SumNode {
        int totalCapacity;
        int totalSize;
        ListNode* left;
        ListNode* right;
        SumNode() {
            
        }
    };
public:
    ListArr(int b);
    ~ListArr();
    int size();
    void insert_left(int v);
    void insert_right(int v);
    void insert(int v, int i);
    void print();
    bool find(int v);
    int delete_left();
    int delete_right();
};

#endif