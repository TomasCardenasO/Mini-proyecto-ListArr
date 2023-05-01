#ifndef Node_H
#define Node_H

class Node {
protected:
    int capacity;
    int size;
public:
    int getCapacity() {
        return this->capacity;
    }
    int getSize() {
        return this->size;
    }
};

#endif