#include <iostream>

using namespace std;

#include "arbol_bp.h"
#include "funciones_extra.h"

int main()
{
    Arbol_BP * A = new Arbol_BP();
    /**tomar_valores_de_archivo(A);
    sacar_valores_de_archivo(A);
    A->pintar();**/

    for(int i = 10 ; i <= 560 ; i+=10){
        A->agregar(i);
    }
    A->sacar(190);
    A->sacar(170);
    A->pintar();
    /**for(int i = 10 ; i <= 190 ; i+=10){
        A->agregar(i);
    }**/
    /**A->agregar(95);
    A->sacar(70);
    A->agregar(125);
    A->agregar(135);**/

    /**A->sacar(10);
    A->sacar(130);
    A->sacar(170);
    A->sacar(180);
    A->sacar(110);
    A->sacar(20);
    A->sacar(90);
    A->sacar(150);
    A->pintar();**/

    /**for(int i = 10 ; i <= 100 ; i+=10){
        A->agregar(i);
    }
    A->agregar(35);
    A->agregar(45);
    A->sacar(60);
    A->sacar(70);
    A->sacar(10);
    A->sacar(20);
    A->pintar();**/
    return 0;
}
