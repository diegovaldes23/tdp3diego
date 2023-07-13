#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 

class Simplex;//Forward declaration

using namespace std;
/*
    * Clase que representa un nodo del branch and bound
    
*/
class Node {
public:

    Simplex *simplexNode;//Simplex que guarda el nodo
    Node *padre;//Nodo padre
    Node *Izq;//Nodo hijo izquierdo
    Node *Der;//Nodo hijo derecho

    vector<float> UB;//Vector de parametros
    vector<float> LB;//Vector de parametros

    //Constructor
    Node(Simplex *simplexNode,Node *padre,Node *Izq,Node *Der);
    //Destructor
    ~Node();
    //Metodos
    void print();
};
#endif