#include <iostream>

using namespace std;

#include "arbol_bp.h"
#include "funciones_extra.h"

int main()
{
    Arbol_BP * A = new Arbol_BP();
    tomar_valores_de_archivo(A);
    sacar_valores_de_archivo(A);
    /**for(int i = 10 ; i <= 1090 ; i+=10){
        A->agregar(i);
    }**/

    A->pintar();

    return 0;
}
