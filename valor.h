#ifndef VALOR_H_INCLUDED
#define VALOR_H_INCLUDED

#include "nodo.h"
class Nodo;

struct Valor{
    int valor;
    Valor * siguiente;
    Valor * anterior;

    /// Para la capa de llaves
    Nodo * nodo_derecho;
};

#endif // VALOR_H_INCLUDED
