#include "Node.h"


/// @brief Constructor de la clase Node
/// @param simplexNode: Simplex que  va a guardar el nodo
/// @param par: Vector de parametros que va a guardar el nodo
Node::Node(Simplex *simplexNode,Node *padre,Node *hijoIzq,Node *hijoDer) {
    this->simplexNode = simplexNode;
    this->padre = padre;
    this->Izq = hijoIzq;
    this->Der = hijoDer;
}

/// @brief Destructor de la clase Node
Node::~Node() {
    // Implementación del destructor
}

/// @brief Función que devuelve el nodo
void Node::print() {
    for (int i = 0; i < UB.size(); i++)
    {
        cout << UB[i] << " ";
    }

    cout << endl;
    for (int i = 0; i < LB.size(); i++)
    {
        cout << LB[i] << " ";
    }
    
    

}
