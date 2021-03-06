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
    Nodo * hermano_izquierdo;
    Nodo * hermano_derecho;
    Nodo * padre;
    Nodo * auxiliar_derecho;
    Nodo * auxiliar_izquierdo;

public:
    Nodo(int ord = ORDEN_RECOMENDADO);
    ~Nodo();

    void nueva_hoja(int ord = ORDEN_RECOMENDADO);   /// CONSTRUCTOR EN CODIGO PARA LAS HOJAS
    void terminar_hoja();   /// DESTRUCTOR EN CODIGO P/HOJAS - NODOS
    void nuevo_nodo(int ord = ORDEN_RECOMENDADO);   /// CONSTRUCTOR EN CODIGO PARA LOS NODOS
    void terminar_nodo();

    void buscar(int);
    void agregar_en_hoja(int);
    void agregar_en_nodo(Valor *);
    bool sacar_de_hoja(int);
    void sacar_de_nodo(Valor *);

    /// FUNCIONES UTILES
    Valor * obtener_lugar_agregado();
    Valor * obtener_principio();
    Valor * obtener_mitad();
    Valor * obtener_anterior();

    Nodo * obtener_auxiliar_izquierdo();
    void establecer_auxiliar_izquierdo(Nodo *);
    Nodo * obtener_auxiliar_derecho();
    void establecer_auxiliar_derecho(Nodo *);
    Nodo * obtener_padre();
    void establecer_padre(Nodo *);
    Nodo * obtener_nodo_interno();
    void establecer_nodo_interno(Nodo *);

    Nodo * obtener_hermano_derecho();
    void establecer_hermano_derecho(Nodo *);
    Nodo * obtener_hermano_izquierdo();
    void establecer_hermano_izquierdo(Nodo *);


    int obtener_cuantos();
    int obtener_orden();
    bool nodo_es_hoja();

    bool fue_encontrado();

    void pintar_hoja();
    void pintar_nodo();
};

#endif // NODO_H_INCLUDED
