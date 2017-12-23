#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "valor.h"

class Nodo{
    Valor * principio;
    Valor * anterior;
    Valor * mitad;
    int donde;
    bool encontrado;
    int cuantos;
    int orden;
    int mayores;
    int menores;
    bool es_hoja;
    Nodo * padre;
    Nodo * auxiliar_izquierdo;
    Nodo * auxiliar_derecho;
public:
    Nodo();
    Nodo(int);
    ~Nodo();
    void buscar(int);
    void agregar(int);
    int borrar(int);
    int obtener_cuantos();
    void pintar();
};

#endif // NODO_H_INCLUDED
