#include <iostream>
#include "nodo.h"

using namespace std;

int main(){
    Nodo * A = new Nodo();
    Nodo * B = new Nodo();

    A->nueva_hoja();
    B->nuevo_nodo();

    A->agregar_en_hoja(5);
    A->agregar_en_hoja(4);
    A->agregar_en_hoja(3);
    A->agregar_en_hoja(2);
    A->agregar_en_hoja(1);
    A->pintar_hoja();

    A->sacar(1);
    A->sacar(2);
    A->sacar(3);
    A->pintar_hoja();
    return 0;
}
