#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

#include "Simplex.h"


using namespace std;

int main() {
    clock_t t_ini, t_fin; // Para medir el tiempo de ejecucion
    double secs=0;// Para medir el tiempo de ejecucion
    int k, numVeces;// Para medir el tiempo de ejecucion

    Simplex *simplex;//Simplex 
    string nombreArchivo;//Nombre del archivo a leer

    //cout << "Cuantas veces quieres que se resuelva el problema? ";
    //cin >> numVeces;
    numVeces = 1;

    /*
    cout << endl << "Indique el nombre de archivo:";
    cin >> nombreArchivo;*/
    cout << endl << "Resolviendo el problema " << nombreArchivo <<", "<< numVeces << " veces..." << endl;
    
    //Leer el archivo
    for (k=0; k<numVeces; k++) {
         
        simplex = new Simplex("sistema.txt");
        t_ini = clock();  
        simplex->Branch(simplex);
        t_fin = clock();
        secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
        delete simplex;
    }
    //Mostrar el tiempo promedio
    cout << endl << "Tiempo promedio: " << secs/numVeces << " segundos" << endl;
    

    return 0;
}
