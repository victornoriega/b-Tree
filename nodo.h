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
    /// NO SE SI PONERLES MAS PARAMETROS COMO LOS PADRES O LAS HOJAS ANTERIORES O SIGUIENTES
    /// CONSTRUCTOR EN CODIGO PARA LAS NUEVAS HOJAS
    void nueva_hoja(int);
    /// CONSTRUCTOR EN CODIGO PARA LOS NUEVOS NODOS INTERNOS
    void nuevo_nodo_interno(int);

    Valor * obtener_principio();
    Nodo * obtener_auxiliar_izquierdo();
    Nodo * obtener_auxiliar_derecho();
    bool nodo_es_hoja();

    int sacar(int);

    void buscar(int);
    void agregar(int);
    int borrar(int);
    int obtener_cuantos();
    void pintar();
};

#endif // NODO_H_INCLUDED
