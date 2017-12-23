#include <iostream>
#include "nodo.h"

using namespace std;

int main()
{
    Nodo A = Nodo(5);
    /**A.agregar(6);
    A.agregar(5);**/
    A.agregar(4);
    A.agregar(3);
    A.agregar(2);
    A.agregar(1);

    /**A.agregar(1);
    A.agregar(1);
    A.agregar(1);
    A.agregar(2);
    A.agregar(2);
    A.agregar(2);
    A.agregar(3);
    A.agregar(3);
    A.agregar(3);
    A.agregar(4);
    A.agregar(4);
    A.agregar(4);
    A.agregar(5);
    A.agregar(5);
    A.agregar(5);**/
    A.pintar();
    cout << "Hello world!" << endl;
    return 0;
}
