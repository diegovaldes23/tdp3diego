#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

class Heap;//Forward declaration
#include "Heap.h"
#include "Node.h"

#define EPS 1.0e-6

using namespace std;


/*
    * Clase que representa un problema de programacion lineal
    
    *Se basa en implementacion de libro "Numerical Recipes in C" W.PRESS et al, Cambridge University press, 2d Ed, 1992. pag 439
*/
class Simplex{ 
public:
    int m; // Numero total de restricciones
    int n; // Numero de variables
    bool isSolved; // Indica si el metodo solve ha sido llamado.
    int icase; // Indica el estado de la solucion del problema despues de solve, 0:Solucion encontrada 1:Solucion no acotada -1:Solucion no factible
    vector<int> izrov; // indice de variables que son cero en la solucion
    vector<int> iposv; // indice de variables que constituyen la solucion. Si indice >=n entonces la variable es artificial y no se cuenta en la solucion
    vector<float> solution;
    int simplx(); // Metodo que ejecuta el algoritmo simplex
    void maxValue(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax);
    void locatePivot(int *ip, int kp);
    void exchangeParameters(int i1, int k1, int ip, int kp);
    vector<float> segundaLinea; // Segunda línea del archivo






    std::vector<std::vector<float>> initialA; // Matriz inicial  --> de aqui pueden calcular el LB
    std::vector<std::vector<float>> a; //***** Matriz del problema: incluye c,a,b inicialmente se transforma a la solucion por piveoteo*****
    int m1; // numero de restricciones <=
    int m2; // numero de restricciones >=
    int m3; // numero de restricciones =

    Simplex(string nombre_archivo); // Constructor con archivo de entrada
    Simplex(vector<vector<float>> a, int m1, int m2, int m3); // Constructor con matriz de entrada
    ~Simplex();
    vector<float> solve(); // Metodo que ejecuta metodo simplex
    void insertConstraint(float b, int var, int type); // Agrega una restriccion var<=b (tipo 1), var>=b (tipo 2), var=b (tipo 3) 
    Simplex *copy();
    vector<float> getSolution(); // Retorna la solucion del problema de tamaño n+1 [Z,x1,...,xn] Z: valor funcion objetivo, xi: valor de la variable i
    void printProblemMatrix(); // Imprime la matriz del problema
    void printSolution(); // Imprime la solucion del problema
    
    //Atributos para branch and bound
    Heap *pendientes;
    //Metodos para branch and bound
    void Branch(Simplex *simplex);
    
    float elegirMayor(vector<float> par);
    float elegirMenor(vector<float> par);
    float mismoindice(float buscar,vector<float> par);
    bool factibilidad(vector<float> indice_enteros,vector<float> UB);
    
};
#endif

