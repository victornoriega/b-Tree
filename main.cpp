#include <iostream>
#include "arbol_bp.h"
#include "funciones_extra.h"
using namespace std;

int main(){
    Arbol_BP * A = new Arbol_BP();
    ///escribir_en_archivo();
    ///tomar_valores_de_archivo(A);
    /**for(int i = 2500000 ; i >= 1 ; i--){
        A->agregar(i);
    }**/
    /**for(int i = 1 ; i <= 25 ; i++){
        A->agregar(i);
    }**/
    A->agregar(36);
    A->agregar(92);
    A->agregar(13);
    A->agregar(21);
    A->agregar(156);
    A->agregar(2);
    A->agregar(5);
    A->agregar(49);
    A->agregar(37);
    A->agregar(76);
    A->agregar(43);
    A->agregar(62);
    A->agregar(25);
    A->agregar(87);
    A->agregar(66);
    A->agregar(99);
    A->agregar(72);
    A->agregar(74);
    A->agregar(115);
    A->agregar(75);
    A->sacar(21);
    A->sacar(13);
    ///A->sacar(21);
    ///A->agregar(87);
    ///A->agregar(156);

    /**for(int i = 0 ; i < 2500000 ; i++){
        A->agregar(i);
    }**/
    /**for(int i = 2500000 ; i >= 0 ; i--){
        A->agregar(i);
    }**/
    A->pintar();
    return 0;
}
