#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "funciones_extra.h"
using namespace std;

void escribir_en_archivo(){
    srand(time(NULL));
    ofstream archivo("valores.txt");
    if(archivo.is_open()){
        for(int i = 1 ; i <= 1000 ; i++){
            archivo << rand() % 800000 + 1 << "\t" ;
            if(i % 10 == 0)
                archivo << "\n";
        }
        archivo.close();
    }else cout << "No se ha podido abrir el archivo" << endl;
}

void tomar_valores_de_archivo(Arbol_BP * A){
    ifstream archivo("valores.txt");
    int x;
    if(archivo.is_open()){
        while(true){
            archivo >> x;
            if(archivo.eof())
                break;
            A->agregar(x);
        }
    }
}

void sacar_valores_de_archivo(Arbol_BP * A){
    ifstream archivo("valores_sacar_copia.txt");
    int x;
    if(archivo.is_open()){
        while(true){
            archivo >> x;
            if(archivo.eof())
                break;
            A->sacar(x);
        }
    }
}
