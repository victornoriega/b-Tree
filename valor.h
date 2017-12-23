#ifndef VALOR_H_INCLUDED
#define VALOR_H_INCLUDED

#include "nodo.h"
class Nodo;

struct Valor{
    int valor;
    Valor * siguiente;
    Valor * anterior;

    /// PARA LA CAPA DE LLAVES
    Nodo * nodo;
};

#endif // VALOR_H_INCLUDED
