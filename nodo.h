#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "valor.h"
#define ORDEN_RECOMENDADO 5
class Nodo{
    Valor * principio;
    Valor * mitad;
    Valor * anterior;
    Valor * lugar_agregado;
    int orden;
    int cuantos;
    int mayores;
    int menores;
    int donde;
    bool es_hoja;
    bool encontrado;
    Nodo * padre;
    Nodo * auxiliar_derecho;
    Nodo * auxiliar_izquierdo;

public:
    Nodo(int ord = ORDEN_RECOMENDADO);
    ~Nodo();

    void nueva_hoja(int ord = ORDEN_RECOMENDADO);   /// CONSTRUCTOR EN CODIGO PARA LAS HOJAS
    void terminar_hoja();   /// DESTRUCTOR EN CODIGO P/HOJAS - NODOS
    void nuevo_nodo(int ord = ORDEN_RECOMENDADO);   /// CONSTRUCTOR EN CODIGO PARA LOS NODOS

    void buscar(int);
    void agregar_en_hoja(int);
    void agregar_en_nodo(Valor *);
    int sacar(int);

    /// FUNCIONES UTILES
    Valor * obtener_lugar_agregado();
    Valor * obtener_principio();
    Nodo * obtener_auxiliar_izquierdo();
    Nodo * obtener_auxiliar_derecho();
    int obtener_cuantos();
    int obtener_orden();

    ///void dividir_hoja(Nodo *, Nodo *);

    void pintar_hoja();
    void pintar_nodo();
};

#endif // NODO_H_INCLUDED
