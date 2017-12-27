#include <iostream>
#include "arbol_bp.h"
#include "funciones_extra.h"
using namespace std;

int main(){
    Arbol_BP * A = new Arbol_BP();
    ///escribir_en_archivo();
    tomar_valores_de_archivo(A);
    /**for(int i = 1000 ; i >= 1 ; i--){
        A->agregar(i);
    }**/
    /**for(int i = 1 ; i <= 1000 ; i++){
        A->agregar(i);
    }**/

    A->pintar();
    return 0;
}
