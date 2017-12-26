#include <iostream>
#include "arbol_bp.h"

using namespace std;

int main(){
    Arbol_BP * A = new Arbol_BP();
    Nodo * B = new Nodo();
    Nodo * C = new Nodo();

    /**B->agregar_en_hoja(5);
    C->agregar_en_nodo(B->obtener_lugar_agregado());

    B->agregar_en_hoja(4);
    C->agregar_en_nodo(B->obtener_lugar_agregado());

    B->agregar_en_hoja(3);
    C->agregar_en_nodo(B->obtener_lugar_agregado());

    B->agregar_en_hoja(2);
    C->agregar_en_nodo(B->obtener_lugar_agregado());

    B->agregar_en_hoja(1);
    C->agregar_en_nodo(B->obtener_lugar_agregado());

    B->pintar_hoja();
    C->pintar_nodo();**/

    /**A->agregar(15);
    A->agregar(14);
    A->agregar(13);
    A->agregar(12);
    A->agregar(11);
    A->agregar(10);
    A->agregar(9);
    A->agregar(8);
    A->agregar(7);
    A->agregar(6);
    A->agregar(5);
    A->agregar(4);
    A->agregar(3);
    A->agregar(2);
    A->agregar(1);**/

    /**A->agregar(1);
    A->agregar(2);
    A->agregar(3);
    A->agregar(4);
    A->agregar(5);
    A->agregar(6);
    A->agregar(7);
    A->agregar(8);
    A->agregar(9);
    A->agregar(10);
    A->agregar(11);
    A->agregar(12);
    A->agregar(13);
    A->agregar(14);
    A->agregar(15);**/
    for(int i = 1 ; i <= 2500000 ; i++){
        A->agregar(i);
    }

    A->pintar();
    return 0;
}
