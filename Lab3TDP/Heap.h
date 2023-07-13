#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include "Node.h"
using namespace std;

/*
    * Clase que representa un heap
*/

class Heap {
    public:
    Node **data;// array of pointers to Node
    int size; // current size
    int capacity; // max size
    Heap(int capacity);//Constructor
    ~Heap();//Destructor
    //Metodos
    void swap(int i, int j);
    int left_idx(int i);
    int right_idx(int i);
    int parent_idx(int i);
    Node* pop();
    void push(Node *s);
    void heapify(int i);
    bool isEmpty();
};

#endif