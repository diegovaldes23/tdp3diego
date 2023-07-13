#include "Simplex.h"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/*
Se genera el simplex a partir de un archivo de texto. 
El archivo debe tener la siguiente estructura:

m1 m2 m3
0 c1 c2 ... cn
b1 a11 a12 ... a1n
b2 a21 a22 ... a2n
...
bm am1 am2 ... amn

Donde:
m1: numero de restricciones de tipo 1 (<=)
m2: numero de restricciones de tipo 2 (>=)
m3: numero de restricciones de tipo 3 (==)
c1, c2, ..., cn: coeficientes de la funcion a maximizar
b1, b2, ..., bm: constantes de las restricciones
ai1, ai2, ..., ain: coeficientes de la restriccion i-esima
con i=1,..,m1+m2+m3
Las m1 primeras restricciones son de tipo 1 (<=)
Las m2 siguientes son de tipo 2 (>=)
Las m3 ultimas son de tipo 3 (==)
*/
float Simplex::elegirMenor(vector<float> numeros){
   
    double fraccionMasPequenia = abs(numeros[1] - trunc(numeros[1]));
    int numeroTruncado = trunc(numeros[1]);

    for (size_t i = 1; i < numeros.size(); ++i) {
         
        double fraccionActual = abs(numeros[i] - trunc(numeros[i]));

        if (fraccionActual < fraccionMasPequenia) {
            fraccionMasPequenia = fraccionActual;
            numeroTruncado = trunc(numeros[i]);
        }
    }

    return numeroTruncado;
}

float Simplex::elegirMayor(vector<float> numeros){
   double fraccionMasGrande = abs(numeros[1] - trunc(numeros[1]));
    int numeroTruncado = trunc(numeros[1]);

    for (size_t i = 1; i < numeros.size(); ++i) {
        double fraccionActual = abs(numeros[i] - trunc(numeros[i]));

        if (fraccionActual > fraccionMasGrande) {
            fraccionMasGrande = fraccionActual;
            numeroTruncado = trunc(numeros[i]);
        }
    }

    return numeroTruncado;
    
}

float Simplex::mismoindice(float buscar,vector<float> numeros){
     
     for (int i = 1; i < numeros.size(); i++)
     {
        if(trunc(numeros[i])== buscar){
            return i;
        }
     }
     return 0;
     

}

bool Simplex:: factibilidad(vector<float> indice_enteros,vector<float> UB){
    //Que recorra el vector de UB y que si hay un numero que no es entero, que retorne false

    for (int i = 1; i < UB.size(); i++)
    {
        for (int j = 1; j < indice_enteros.size(); j++)
        {
            if(i==indice_enteros[j]){
                if(trunc(UB[i])- UB[i] != 0){
                    return false;
                }
            }
        }
        
    }
    return true;

}
void Simplex::Branch(Simplex* simplex) {
    printf("Branching\n");
    
    // Crear el heap de nodos pendientes
    Heap* pendientes = new Heap(1000);

    // Resolver el simplex original
    vector<float> par1 = simplex->solve(); 

    //Crear vector para el LB
    vector<float> par2;
    
    par2.push_back(0);
    for (int i = 1; i < par1.size(); i++)
    {   
        double truncated = trunc(par1[i]);
        par2.push_back(truncated);
    }
    
    float suma = 0;
    for (int i = 1; i < initialA[0].size(); i++){  
        suma= suma + initialA[0][i]*par2[i];
    }

    par2[0]=suma;

    //Creacion del Node principal
    Node* node = new Node(simplex,nullptr,nullptr,nullptr);
    node->UB =par1;
    node->LB = par2;

    pendientes->push(node);  // Agregar el nodo al heap

    while(!pendientes->isEmpty()) {
        
        Node* node = pendientes->pop(); // Obtener el nodo con mayor UB del heap
        
        //Se imprime el node 
        /*
        node->print();
        node->simplexNode->printProblemMatrix();
        */
        //Calcular el numero fraccionario mayor y su siguiente +1
        float newnumero= elegirMayor(node->UB);
        float newnumero1= newnumero +1;

        //Encontrar el indice del numero fraccionario mayor con el metodo mismoindice
        float indice= mismoindice(newnumero, node->UB);
        
        //Ver si las variables estan como enteros
        bool factible = factibilidad(segundaLinea, node->UB);

        node->simplexNode->isSolved = factible;

        // Si el nodo es factible y su UB es menor que el LB del simplex, entonces se puede podar
        if (node->simplexNode->isSolved && node->UB[0] < node->LB[0]) {
            printf("Podar\n");
            continue;
        }
        
        // Si el nodo es factible y su UB es mayor que el LB del simplex, entonces se actualiza el LB del simplex
        if (node->simplexNode->isSolved && node->UB[0] > node->LB[0]) {
            printf("Actualizar LB\n");
            node->LB[0] = node->UB[0];
        }
        //Solucion
        if (node->simplexNode->isSolved && node->UB[0] == node->LB[0]) {
            printf("Solucion\n");
            node->print();
            
        }
        
        if (!isSolved == true){
            
            Simplex *simplex2 = simplex->copy(); 
            
            
            simplex2->insertConstraint(newnumero,indice,1);
            
            vector<float> par3 = simplex2->solve();

            Node* node1 = new Node(simplex2,nullptr,nullptr,nullptr);
            node1->UB =par3;
            node1->LB=node->LB;

            
            cout<<endl;
            node1->print();
            cout<<endl;
            node1->simplexNode->printProblemMatrix();
            
            
            Simplex *simplex3 = simplex->copy(); 

            simplex3->insertConstraint(newnumero1,indice,2);
            vector<float> par4 = simplex3->solve();

        
            Node* node2 =new Node(simplex3,nullptr,nullptr,nullptr);
            node2->UB =par4;
            node2->LB=node->LB;

            cout<<endl;
            node2->print();
            cout<<endl;
            node2->simplexNode->printProblemMatrix();
            
            pendientes->push(node1);

            if(node1->UB[0] < node->UB[0]){
                continue;
            }

            

            if(node2->UB[0] < node->UB[0]){
                continue;
            }
                
            pendientes->push(node2);
            
        }
        

        
        
        
    }
    

}

Simplex::Simplex(string fileName)
{
    string line;
    fstream file(fileName);
    stringstream charStream;
    string token;

    if (!file.is_open()){
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }
    // leyendo m1,m2,m3 en primera linea
    getline(file, line);
    charStream << line;
    getline(charStream, token, ' ');
    this->m1 = stoi(token);
    getline(charStream, token, ' ');
    this->m2 = stoi(token);
    getline(charStream, token, ' ');
    this->m3 = stoi(token);

    getline(file, line); // Leer la segunda línea
    charStream.clear();
    charStream << line;

    segundaLinea.push_back(0);
    while (getline(charStream, token, ' ')) {
        this->segundaLinea.push_back(stof(token)); // Guardar en el miembro segundaLinea utilizando this->
    }   
    
    // leyendo la matrix que incluye c,a,b: (m+1) x (n+1), donde n es el numero de variables y m=m1+m2+m3 el numero de restricciones
    while (getline(file, line)) {
        charStream.clear();
        charStream << line;
        vector<float> row;
        while (getline(charStream, token, ' '))
        {
            row.push_back(stof(token));
        }
        this->a.push_back(row);
    }

    this->n = a[0].size() - 1;
    this->m = m1 + m2 + m3;
    // si hay una cantidad distinta de resticciones a las indicadas: Error!
    if (m != (int)a.size() - 1){
        cout<<"Error en la cantidad de restricciones."<<endl;
        exit(1);
    }

    // si hay una cantidad distinta de variables a las indicadas: Error!
    for (int i = 1; i <= m; i++) {
        if (a[i][0] < 0.0 || (int)a[i].size() != n + 1){
            cout<<"Error en la cantidad de variables o constante menor que 0:" << i <<endl;
            exit(1);
        }
    }

    // EL metodo requiere una fila adicional al final de la matriz para calculos intermedios
    vector<float> row;
    for (int i = 0; i <= n; i++){
        row.push_back(0.0);
    }

    this->a.push_back(row);
    this->initialA = a;
    this->isSolved = false; // inicialmente aún no se ha resuelto
    file.close();
}


/*
Se copia la matriz a en el atributo a de la clase Simplex.
*/
Simplex::Simplex(vector<vector<float>> a, int m1, int m2, int m3)
{
    int m = m1 + m2 + m3;
    for (int i = 1; i <= m; i++) {
        if (a[i][0] < 0.0) {
            // Error al crear el Simplex, ya que no se permiten
            // constantes negativas para las restricciones.
            throw invalid_argument("La matriz ingresada no es valida.");
        }
    }

    this->initialA = a;
    this->a = a;
    this->m1 = m1;
    this->m2 = m2;
    this->m3 = m3;
    this->m = m;
    this->n = a[0].size() - 1;
    this->isSolved = false;
}

Simplex::~Simplex(){
}


/*
Basado en rutina simplx de Numerical Recipes
*/
vector<float> Simplex::solve() {

    icase = simplx();
    isSolved = true;
    if (icase != 0) { // No hay solucion
        vector<float> emptyVector;
        return emptyVector; 
    }

    vector<float> parameters(n + 1, 0.0); // vector de tamaño n+1 inicializado en 0
    
    parameters[0] = a[0][0]; // valor de Z resultante
    for (int i = 0; i < m; i++) {
        if (iposv[i] < n) { // si el indice correspnde a una variable (y no a una slack variable)
            parameters[iposv[i] + 1] = a[i + 1][0]; // se guarda el valor de la variable
        }
    }
    solution = parameters; // se guarda la solucion en el atributo solution

    return parameters;
}

/*
    retorna el estado de la solucion: 0 si se encontro una solucion, 1 si no hay solucion, 2 si hay infinitas soluciones
    Ejecuta el algorithmo  simplex
*/
int Simplex::simplx() {
    int i, ip, is, k, kh, kp, nl1;
    float q1, bmax;
    vector<int> l1;
    vector<int> l3;
    nl1 = n;
    // inicializacion de l1, l3, izrov, iposv
    izrov.clear();
    iposv.clear();
    for (k = 0; k < n; k++){
        l1.push_back(k);
        izrov.push_back(k);
    }
    for (i = 0; i < m; i++){
        iposv.push_back(n + i);
    }
    // Caso que origen no es factible
    if (m2 + m3){
        for (i = 0; i < m2; i++){ // inicializando m2 variables de holgura
            l3.push_back(1);
        }
        for (k = 0; k < n + 1; k++){ // computando nueva funcion Z
            q1 = 0.0;
            for (i = m1; i < m; i++){
                q1 += a[i + 1][k];
            }
            a[m + 1][k] = -q1;
        }
        for (;;){
            maxValue(m + 1, l1, nl1, 0, &kp, &bmax); // buscando la variable con mayor coeficiente en la funcion Z
            if (bmax <= EPS && a[m + 1][0] < -EPS){ // no hay solucion factible (Z auxiliar < 0)
                return -1; // icase -1
            }
            else if (bmax <= EPS && a[m + 1][0] <= EPS){ // solucion factible (Z auxiliar = 0)
                for (ip = m1 + m2; ip < m; ip++){
                    if (iposv[ip] == ip + n){ // se busca la variable de holgura correspondiente
                        maxValue(ip, l1, nl1, 1, &kp, &bmax);
                        if (bmax > EPS){
                            goto one;
                        }
                    }
                }
                for (i = m1; i < m1 + m2; i++){ // se cambia el signo de la restriccion de variables aun presentes
                    if (l3[i - m1] == 1){
                        for (k = 0; k < n + 1; k++){
                            a[i + 1][k] = -a[i + 1][k];
                        }
                    }
                }
                break;
            }
            locatePivot(&ip, kp);  // se busca el pivote
            if (ip == -1){ // caso no acotado (Z es infinito)
                return -1; // icase -1
            }
        one:
            exchangeParameters(m + 1, n, ip, kp); // intercambia variables
            if (iposv[ip] >= (n + m1 + m2)){
                for (k = 0; k < nl1; k++){
                    if (l1[k] == kp){
                        break;
                    }
                }
                --nl1;
                for (is = k; is < nl1; is++){
                    l1[is] = l1[is + 1];
                }
            }
            else {
                kh = iposv[ip] - m1 - n;
                if (kh >= 0 && l3[kh]){
                    l3[kh] = 0;
                    ++a[m + 1][kp + 1];
                    for (i = 0; i < m + 2; i++){
                        a[i][kp + 1] = -a[i][kp + 1];
                    }
                }
            }
            is = izrov[kp];
            izrov[kp] = iposv[ip];
            iposv[ip] = is;
        }
    }

    for (;;){
        maxValue(0, l1, nl1, 0, &kp, &bmax);
        if (bmax <= EPS){
            return 0; // icase = 0
        }
        locatePivot(&ip, kp);
        if (ip == -1){
            return 1; // icase  = 1
        }
        exchangeParameters(m, n, ip, kp);
        is = izrov[kp];
        izrov[kp] = iposv[ip];
        iposv[ip] = is;
    }
}

/*
   Simp1 en Numerical Recipes: Determina el maximo valor de una fila de la matriz a
*/
void Simplex::maxValue(int mm, vector<int> ll, int nll, int iabf, int *kp, float *bmax) {
    int k;
    float test;

    if (nll <= 0){
        *bmax = 0.0;
    }else {
        *kp = ll[0];
        *bmax = a[mm][*kp + 1];
        for (k = 1; k < nll; k++){
            if (iabf == 0){
                test = a[mm][ll[k] + 1] - (*bmax);
            } else{
                test = fabs(a[mm][ll[k] + 1]) - fabs(*bmax);
            }

            if (test > 0.0){
                *bmax = a[mm][ll[k] + 1];
                *kp = ll[k];
            }
        }
    }
}

/*
    Simp2 de numerical recipes: este metodo encuentra la fila en donde se
        encuentra el elemento que sirve como pivote.
*/
void Simplex::locatePivot(int *ip, int kp) {

    int k, i;
    float qp, q0, q, q1;

    kp = kp + 1;
    *ip = -1;
    for (i = 0; i < m; i++){
        if (a[i + 1][kp] < -EPS){
            break;
        }
    }

    if (i + 1 > m){
        return;
    }

    q1 = -a[i + 1][0] / a[i + 1][kp];
    *ip = i;
    for (i = *ip + 1; i < m; i++){
        if (a[i + 1][kp] < -EPS){
            q = -a[i + 1][0] / a[i + 1][kp];
            if (q < q1){
                *ip = i;
                q1 = q;
            } else if (q == q1) {
                qp = -1;
                q0 = -1;
                for (k = 0; k < n; k++){
                    qp = -a[*ip + 1][k + 1] / a[*ip + 1][kp];
                    q0 = -a[i + 1][k + 1] / a[i + 1][kp];
                    if (q0 != qp){
                        break;
                    }
                }
                if (q0 < qp){
                    *ip = i;
                }
            }
        }
    }
}

/*
    Simp3 de numerical recipes: intercambia variables izq y der
*/
void Simplex::exchangeParameters(int i1, int k1, int ip, int kp) {
    int kk, ii;
    float piv;

    piv = 1.0 / a[ip + 1][kp + 1];
    for (ii = 0; ii < i1 + 1; ii++){
        if (ii - 1 != ip){
            a[ii][kp + 1] *= piv;
            for (kk = 0; kk < k1 + 1; kk++){
                if (kk - 1 != kp){
                    a[ii][kk] -= a[ip + 1][kk] * a[ii][kp + 1];
                }
            }
        }
    }

    for (kk = 0; kk < k1 + 1; kk++){
        if (kk - 1 != kp){
            a[ip + 1][kk] *= -piv;
        }
    }

    a[ip + 1][kp + 1] = piv;
}


/*
Inserta una restriccion en la matriz A del tipo
var <=b tipo 1
var >=b tipo 2
var = b tipo 3
*/
void Simplex::insertConstraint(float b, int var, int type) {
    if (var == 0 || var > n || b < 0.0)
    {
        return;
    }

    vector<float> constraint(n + 1, 0.0);
    constraint[0] = b;
    constraint[var] = -1.0;

    switch (type)
    {
    case 1:
        this->initialA.insert(this->initialA.begin() + m1 + 1, constraint);
        m1++;
        break;
    case 2:
        this->initialA.insert(this->initialA.begin() + m1 + m2 + 1, constraint);
        m2++;
        break;
    case 3:
        this->initialA.insert(this->initialA.begin() + m + 1, constraint);
        m3++;
        break;
    default:
        return;
        break;
    }
    m++;
    isSolved = false; // La solucion ya no es valida
    a = initialA;    // Se copia la matriz inicial a la matriz de trabajo
    solution.clear(); // Se limpia la solucion
}

/*
    Generamos un objeto simplex nuevo
*/
Simplex* Simplex::copy() {
    Simplex*s = new Simplex(initialA, m1, m2, m3);
    s->izrov = this->izrov;
    s->iposv = this->iposv;
    s->isSolved = this->isSolved;
    s->icase = this->icase;
    s->a = this->a;
    s->solution = this->solution;
    return s;
}

vector<float> Simplex::getSolution() {
    if (isSolved && icase == 0) {
        return solution;
    }
    vector<float> empty;
    return empty;
}

/*
 Imprimimos la matriz original del problema
*/
void Simplex::printProblemMatrix()
{
    for (size_t i = 0; i < initialA.size(); i++) {
        for (size_t j = 0; j < initialA[0].size(); j++){
            string aij = to_string(initialA[i][j]);
            aij = aij.substr(0, aij.find(".") + 3);
            aij.insert(aij.begin(), 10 - aij.length(), ' ');
            cout << aij;
        }
        cout << endl;
    }
}

/*

*/
void Simplex::printSolution(){
    if (isSolved)    {
        int nm1m2;
        if (icase == 1){
            cout << "Caso no acotado -> solucion infinita." << endl;
        }
        else if (icase == -1) {
            cout << "Solucion vacia." << endl;
        } else {
            nm1m2 = n + m1 + m2;
            string txt[nm1m2];
            for (int i = 0; i < n; i++) {
                txt[i] = "x" + to_string(i + 1);
            }
            for (int i = n; i < nm1m2; i++){
                txt[i] = "y" + to_string(i + 1 - n);
            }

            cout << string(11, ' ');
            for (int i = 0; i < n; i++) {
                if (izrov[i] < nm1m2){
                    txt[izrov[i]].insert(txt[izrov[i]].begin(), 10 - txt[izrov[i]].length(), ' ');
                    cout << txt[izrov[i]];
                }
            }

            cout << endl;
            for (int i = 0; i < m + 1; i++){
                if (i == 0 || iposv[i - 1] < nm1m2){
                    if (i > 0){
                        cout << txt[iposv[i - 1]];
                    } else {
                        cout << "  ";
                    }

                    string ai0 = to_string(a[i][0]);
                    ai0 = ai0.substr(0, ai0.find(".") + 3);
                    ai0.insert(ai0.begin(), 10 - ai0.length(), ' ');
                    cout << ai0;
                    for (int j = 1; j < n + 1; j++){
                        if (izrov[j - 1] < nm1m2){
                            string aij = to_string(a[i][j]);
                            aij = aij.substr(0, aij.find(".") + 3);
                            aij.insert(aij.begin(), 10 - aij.length(), ' ');
                            cout << aij;
                        }
                    }
                    cout << endl;
                }
            }
        }
    } else{
        cout << "No esta resuelto." << endl;
    }
} 