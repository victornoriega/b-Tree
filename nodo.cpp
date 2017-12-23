#include "nodo.h"
#include <iostream>
#include <limits>
using namespace std;

enum{VACIO,PRINCIPIO,ENMEDIO,FINAL};
Nodo::Nodo(){
    principio = NULL;
    anterior = NULL;
    mitad = NULL;
    donde = VACIO;
    encontrado = false;
    cuantos = 0;
    orden = 0;
    mayores = 0;
    menores = 0;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
    es_hoja = false;
}
/// HACER EL CONSTRUCTOR EN CODIGO PARA EL ARBOL
Nodo::Nodo(int ord){
    principio = NULL;
    anterior = NULL;
    mitad = NULL;
    donde = VACIO;
    encontrado = false;
    cuantos = 0;
    orden = ord;
    mayores = 0;
    menores = 0;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
    es_hoja = false;
}
/// HACER EL DESTRUCTOR EN CODIGO PARA EL ARBOL
Nodo::~Nodo(){
    Valor * p = principio;
    while(principio){
        p = principio;
        principio = principio->siguiente;
        free(p);
    }
    principio = NULL;
    anterior = NULL;
    mitad = NULL;
    donde = VACIO;
    encontrado = false;
    cuantos = 0;
    orden = 0;
    mayores = 0;
    menores = 0;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
    es_hoja = false;
}

/// CONSTRUCTOR EN CODIGO PARA LAS NUEVAS HOJAS
void Nodo::nueva_hoja(int ord){
    principio = NULL;
    anterior = NULL;
    mitad = NULL;
    donde = VACIO;
    encontrado = false;
    cuantos = 0;
    orden = ord;
    mayores = 0;
    menores = 0;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
    es_hoja = true;
}

/// CONSTRUCTOR EN CODIGO PARA LOS VERTICES INTERNOS
void Nodo::nuevo_nodo_interno(int ord){
    principio = NULL;
    anterior = NULL;
    mitad = NULL;
    donde = VACIO;
    encontrado = false;
    cuantos = 0;
    orden = ord;
    mayores = 0;
    menores = 0;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
    es_hoja = false;
}

/// ESTO DEBERIA DAR LA HOJA DONDE SE INSERTARA EL VALOR
void Nodo::buscar(int a){
    Valor * p = principio;
    if(!p){
        donde = VACIO;
        encontrado = false;
        return;
    }else{
        while(p){
            if(p->valor == a){
                encontrado = true;
                if(p == principio){
                    donde = PRINCIPIO;
                }else if(!p->siguiente){
                    donde = FINAL;
                }else{
                    donde = ENMEDIO;
                }
                return;
            }else if(p->valor > a){
                if(principio == p){
                    donde = PRINCIPIO;
                }else{
                    donde = ENMEDIO;
                }
                return;
            }else{
                anterior = p;
                p = p->siguiente;
            }
        }
    }
    donde = FINAL;
    encontrado = false;
    return;
}

void Nodo::agregar(int a){
    buscar(a);
    Valor * q = (Valor *)malloc(sizeof(Valor));
    q->valor = a;
    q->nodo = NULL;
    if(donde == VACIO){
        principio = q;
        mitad = q;

        q->siguiente = NULL;
        q->anterior = NULL;
    }else{
        Valor * p = mitad;
        if(p->valor <= a){  /// Aumenta los mayores
            mayores++;
            Valor * r;
            while(p){
                r = p;
                if(p->valor > a)    /// Se corta en el momento en que p es mayor
                    break;
                p = p->siguiente;
            }
            if(!p){ /// Llegó después del final en la busqueda
                q->siguiente = NULL;
                q->anterior = r;
                r->siguiente = q;
            }else{
                q->anterior = p->anterior;
                if(q->anterior)
                    q->anterior->siguiente = q;
                q->siguiente = p;
                q->siguiente->anterior = q;
            }
        }else{              /// Aumenta los menores
            menores++;
            while(p){
                if(p->valor <= a)
                    break;
                p = p->anterior;
            }
            if(!p){ /// Llegó antes del principio en la busqueda
                q->siguiente = principio;
                q->anterior = NULL;
                principio->anterior = q;
                principio = q;
            }else{
                q->siguiente = p->siguiente;
                if(q->siguiente)
                    q->siguiente->anterior = q;
                q->anterior = p;
                p->siguiente = q;
            }
        }
    }
    cuantos++;
    /// CHECAR LA CANTIDAD DE CUANTOS Y EL ORDEN PARA MANTENER EL SPLIT.
    if(mayores - menores > 1){
        mitad = mitad->siguiente;
        mayores--;
        menores++;
        return;
    }
    if(menores - mayores > 1){
        mitad = mitad->anterior;
        menores--;
        mayores++;
        return;
    }
}

Valor * Nodo::obtener_principio(){
    return principio;
}

Nodo * Nodo::obtener_auxiliar_izquierdo(){
    return auxiliar_izquierdo;
}

Nodo * Nodo::obtener_auxiliar_derecho(){
    return auxiliar_derecho;
}

bool Nodo::nodo_es_hoja(){
    if(es_hoja)
        return true;
    else
        return false;
}

void Nodo::pintar(){
    Valor * p = principio;
    cout << "En la mitad: " << mitad->valor << endl;
    cout << "Cuantos: " << cuantos << endl;
    cout << "Mayores: " << mayores << endl;
    cout << "Menores: " << menores << endl;
    while(p){
        cout << "Valor: " << p->valor << endl;
        p = p->siguiente;
    }
}
