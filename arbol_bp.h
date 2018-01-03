#ifndef ARBOL_BP_H_INCLUDED
#define ARBOL_BP_H_INCLUDED

#include "nodo.h"
#define ORDEN_RECOMENDADO 5
class Arbol_BP{
    int altura;
    int orden;
    int orden_minimo;
    Nodo * raiz;
public:
    Arbol_BP(int ord = ORDEN_RECOMENDADO);
    ~Arbol_BP();

    Nodo * buscar_hoja(int);
    void agregar(int);
    bool sacar(int);
    void subir(Nodo *, Nodo *);
    bool crecer(Nodo *);

    void dividir_hoja(Nodo *, Nodo*);
    void partir_raiz();
    void pintar();
    void empujar_izquierdo(Nodo *, Nodo *, int);
    void empujar_derecho(Nodo *, Nodo *, int);
    void combinar(Nodo *, Nodo *, int);
    bool combinar_nodos_internos(Nodo *, int);
    bool bajar(Nodo *, Nodo *, Nodo *);
    void imprimir_nodos_internos(Nodo *);
};

#endif // ARBOL_BP_H_INCLUDED
