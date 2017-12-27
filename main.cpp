#include <iostream>
#include "arbol_bp.h"

using namespace std;

int main(){
    Arbol_BP * A = new Arbol_BP();

    /**for(int i = 1000 ; i >= 1 ; i--){
        A->agregar(i);
    }**/
    for(int i = 1 ; i <= 1000 ; i++){
        A->agregar(i);
    }

    A->pintar();
    return 0;
}
