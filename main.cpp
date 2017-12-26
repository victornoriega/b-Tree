#include <iostream>
#include "arbol_bp.h"

using namespace std;

int main(){
    Arbol_BP * A = new Arbol_BP();

    /**A->agregar(9);
    A->agregar(8);
    A->agregar(7);
    A->agregar(6);
    A->agregar(5);
    A->agregar(4);
    A->agregar(3);
    A->agregar(2);
    A->agregar(1);**/

    A->agregar(1);
    A->agregar(2);
    A->agregar(3);
    A->agregar(4);
    A->agregar(5);
    A->agregar(6);
    A->agregar(7);
    A->agregar(8);
    A->agregar(9);

    A->pintar();
    return 0;
}
