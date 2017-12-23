#include "nodo.h"
#include <iostream>

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
Nodo::Nodo(int o){
    principio = NULL;
    anterior = NULL;
    mitad = NULL;
    donde = VACIO;
    encontrado = false;
    cuantos = 0;
    orden = o;
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
    q->nodo_derecho = NULL;
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
