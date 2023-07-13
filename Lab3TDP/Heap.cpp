#include "Heap.h"

/// @brief Constructor de la clase Heap
/// @param capacity : Capacidad del heap
Heap::Heap(int capacity) {
    this->capacity = capacity;
    data = new Node*[capacity];
    size = 0;
}
/// @brief destructor de la clase Heap
Heap::~Heap() {
    delete[] data;
}
/// @brief Función que intercambia dos nodos
/// @param i : indice del primer nodo 
/// @param j : indice del segundo nodo
void Heap::swap(int i, int j) {
    Node *temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

/// @brief Función que devuelve el indice del hijo izquierdo
/// @param i: indice del nodo
/// @return : indice del hijo izquierdo
int Heap::left_idx(int i) {
    return 2 * i + 1;
}
/// @brief Función que devuelve el indice del hijo derecho
/// @param i : indice del nodo
/// @return : indice del hijo derecho
int Heap::right_idx(int i) {
    return 2 * i + 2;
}
/// @brief Función que devuelve el indice del padre
/// @param i : indice del nodo
/// @return : indice del padre
int Heap::parent_idx(int i) {
    return (i - 1) / 2;
}
/// @brief Función que devuelve el nodo con mayor UB
/// @return : nodo con mayor UB
Node* Heap::pop() {
    if (size == 0) {
        return nullptr;
    }
    Node* s = data[0];
    data[0] = data[size - 1];
    size--;
    heapify(0);
    return s;
}
/// @brief Función que agrega un nodo al heap
/// @param s : nodo a agregar
void Heap::push(Node* s) {
    cout<<"push"<<endl;
    if (size == capacity) {
        Node** temp = new Node*[capacity * 2];
        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = capacity * 2;
    }
    data[size] = s;
    size++;
    int i = size - 1;
    while (i > 0) {
        int p = parent_idx(i);
        if (data[i]->UB[0] > data[p]->UB[0]) {
            swap(i, p);
            i = p;
        }
        else {
            break;
        }
    }
}
/// @brief Función que reordena el heap
/// @param i : indice del nodo
void Heap::heapify(int i) {
    int l = left_idx(i);
    int r = right_idx(i);
    int largest = i;
    if (l < size && data[l]->UB[0] > data[i]->UB[0]) {
        largest = l;
    }
    if (r < size && data[r]->UB[0] > data[largest]->UB[0]) {
        largest = r;
    }
    if (largest != i) {
        swap(i, largest);
        heapify(largest);
    }
}

bool Heap::isEmpty(){
    return size == 0;
}