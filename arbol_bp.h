#ifndef ARBOL_BP_H_INCLUDED
#define ARBOL_BP_H_INCLUDED

#include "nodo.h"
class Arbol_BP{
    int orden;
    Nodo * raiz;
public:
    Arbol_BP();
    Arbol_BP(int);
    Nodo * buscar_hoja(int);
    bool es_hoja(Nodo *);
    void pintar();
};

#endif // ARBOL_BP_H_INCLUDED
