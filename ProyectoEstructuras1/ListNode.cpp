#include "ListNode.h"
#include <iostream>

using namespace std;

ListNode::ListNode(int capacity) {
    this->capacity = capacity;
    this->arr = new int[capacity];
    this->size = 0;
    this->next = nullptr;

}
ListNode::~ListNode() {
    delete[] arr;
}
int ListNode::getCapacity() {
    return capacity;
}
int ListNode::getSize() {
    return size;
}
