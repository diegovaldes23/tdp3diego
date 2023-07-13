#include "Simplex.h"

int main() {

    Simplex *simplex1 = new Simplex("sistema.txt");

    /* Lo siguiente debiese ser un while que efectua el branching
     y llama a simplex->solve() en cada iteracion por ambas ramas.
     falta :
     - calcular LB
     - la parte que seleciona la variable a branchear solo entre las variables restringidas a enteros
     - aqui se hace un copy, pero podrian pensar en hacer un clone
     - el archivo de entrada es ligeramente diferente a este ya que tiene una linea que indica las variables restringidas a enteros
     - realizar la optimizacion
     - tomar el tiempo de ejecucion en un main

     Para optimizar estan las siguientes ideas:
     - se podria branchear en mas de dos ramas
     - se podria de vez en cuando hacer búsqueda en profundidad, obtener una solucion posible y guardarla. De esta forma se podrian podar nodos que no lleven a mejores soluciones que esta Z_sol>UB_Nodo.
    o descartar dicha solucion porque Z_sol<LB_Todos_los_nodos.
     - se podria particularizar la solucion a una clase de problemas, por ejemplo si las variables son binarias las busquedas en profundidad son mas eficases.
     - se podrían mejorar los tipos de datos para que sean mas eficientes las operaciones intermedias. 

    */

    vector<float> par1 = simplex1->solve(); // retorna [Z,x1,...,xn] sino []
    simplex1->printProblemMatrix();
    cout << "Solucion: " << endl;
    for(int i = 0; i < par1.size(); i++) {
        cout << par1[i] << " ";
    }
    cout << endl;

    Simplex *simplex2 = simplex1->copy(); // Aqui falla porque se necesita un clone
    Simplex *simplex3 = simplex1->copy(); // Aqui falla porque se necesita un clone

    cout<< "Insertando restricciones x2<=5" << endl; // tipo 1 : <=
    simplex2->insertConstraint(5, 2, 1); // ojo que variables aqui cominezan con indice =1
    simplex2->printProblemMatrix();
    vector<float> par2 = simplex2->solve(); // retorna [Z,x1,...,xn] sino []
    for(int i = 0; i < par2.size(); i++) {
        cout << par2[i] << " ";
    }
    cout<< endl;
    // notar que falta hacer una funcion para truncar y calcular LB

    cout<< "Insertando restricciones x2>=6" << endl; // tipo 2 : >=
    simplex3->insertConstraint(6, 2, 2); // (b,var,tipo) ojo que variables aqui cominezan con indice =1
    simplex3->printProblemMatrix();
    vector<float> par3 = simplex3->solve(); // retorna [Z,x1,...,xn] sino []
    for(int i = 0; i < par3.size(); i++) {
        cout << par3[i] << " ";
    }
    cout<< endl;

    Simplex *simplex4 = simplex3->copy(); // Aqui falla porque se necesita un clone
    Simplex *simplex5 = simplex3->copy(); // Aqui falla porque se necesita un clone

    cout<< "Insertando restricciones x1>=2" << endl; // tipo 2 : >=
    simplex5->insertConstraint(2, 1, 2); // (b,var,tipo) ojo que variables aqui cominezan con indice =1
    simplex5->printProblemMatrix();
    vector<float> par5 = simplex5->solve(); // retorna [Z,x1,...,xn] sino []
    for(int i = 0; i < par5.size(); i++) {
        cout << par5[i] << " ";
    }
    cout<< endl;
    if (par5.size() == 0) {
        cout << "No hay solucion" << endl;
    }

    cout<< "Insertando restricciones x1<=1" << endl; // tipo 1 : <=
    simplex4->insertConstraint(1, 1, 1); // (b,var,tipo) ojo que variables aqui cominezan con indice =1
    simplex4->printProblemMatrix();
    vector<float> par4 = simplex4->solve(); // retorna [Z,x1,...,xn] sino []
    for(int i = 0; i < par4.size(); i++) {
        cout << par4[i] << " ";
    }
    cout<< endl;
    if (par4.size() == 0) {
        cout << "No hay solucion" << endl;
    }

    Simplex *simplex6 = simplex4->copy(); // Aqui falla porque se necesita un clone
    cout<< "Insertando restricciones x2<=6" << endl; // tipo 1 : <=
    simplex6->insertConstraint(6, 2, 1); // (b,var,tipo) ojo que variables aqui cominezan con indice =1
    simplex6->printProblemMatrix();
    vector<float> par6 = simplex6->solve(); // retorna [Z,x1,...,xn] sino []
    for(int i = 0; i < par6.size(); i++) {
        cout << par6[i] << " ";
    }
    cout<< endl;
    if (par6.size() == 0) {
        cout << "No hay solucion" << endl;
    }


}