#include <iostream>
#include <limits>
#include "arbol_bp.h"

using namespace std;

Arbol_BP::Arbol_BP(int ord){
    orden = ord;
    raiz = NULL;
}

Arbol_BP::~Arbol_BP(){
    int valor_minimo = numeric_limits<int>::min();
    Nodo * hoja1 = buscar_hoja(valor_minimo);
    Nodo * hoja2;

    while(hoja1){
        hoja2 = hoja1;
        hoja1 = hoja1->obtener_auxiliar_derecho();
        hoja2->terminar_hoja();
    }
    raiz = NULL;
    orden = 0;
}

///     **************************************************************************************************
///     DIVIDIR HOJA
///     DADA UNA HOJA CON UNA CANTIDAD DE ELEMENTOS IGUAL AL ORDEN ESTA DEBE DIVIDIRSE
///     PARAMETROS: Nodo * INDICA LA DIRECCION DE LA HOJA LLENA
///                 Nodo * INDICA LA DIRECCION DE UNA HOJA VACIA QUE SE CONECTARA CON LA PRIMERA HOJA
///     RETORNO: NADA
///     **************************************************************************************************
void Arbol_BP::dividir_hoja(Nodo * p, Nodo * q){
    Valor * x1 = p->obtener_mitad();
    Valor * x2;
    while(x1){
        q->agregar_en_hoja(x1->valor);
        x2 = x1;
        x1 = x1->siguiente_en_hoja;
        p->sacar(x2->valor);
    }
    q->establecer_auxiliar_derecho(p->obtener_auxiliar_derecho());
    if(q->obtener_auxiliar_derecho()){
        Nodo * a = q->obtener_auxiliar_derecho();
        a->establecer_auxiliar_izquierdo(q);
    }
    q->establecer_auxiliar_izquierdo(p);
    p->establecer_auxiliar_derecho(q);

    q->establecer_padre(p->obtener_padre());
}

///     **************************************************************************************************
///     PINTAR LOS ELEMENTOS DENTRO DEL ARBOL
///     SE VA A LA PRIMERA HOJA DEL ARBOL Y RECORRE LAS HOJAS PINTANDO LOS ELEMENTOS
///     PARAMETROS: NADA
///     RETORNO: NADA
///     **************************************************************************************************
void Arbol_BP::pintar(){
    int valor_minimo = numeric_limits<int>::min();
    Nodo * hoja = buscar_hoja(valor_minimo);
    Valor * p;
    while(hoja){
        p = hoja->obtener_principio();
        while(p){
            cout << "Valor: " << p->valor << endl;
            p = p->siguiente_en_hoja;
        }
        hoja = hoja->obtener_auxiliar_derecho();
    }
}

///     **************************************************************************************************
///     BUSCAR HOJA
///     DESCRIPCION: BUSCA LA HOJA DONDE HABRA DE INSERTARSE EL NUEVO VALOR DENTRO DEL ARBOL
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
Nodo * Arbol_BP::buscar_hoja(int a){
    Nodo * p = raiz;
    Valor * r;
    if(!p)
        return NULL;
    else{
        while(!p->nodo_es_hoja()){ /// Mientras sea nodo interno
            r = p->obtener_principio();
            while(r){
                if(!r->anterior_en_nodo && !r->siguiente_en_nodo){  /// R ES EL UNICO ELEMENTO DENTRO DEL NODO
                    if(a < r->valor){
                        p = p->obtener_auxiliar_izquierdo();
                        break;
                    }else{
                        p = r->nodo;;
                        break;
                    }
                }else if(r == p->obtener_principio()){           /// R ES EL PRINCIPIO PERO HAY UN ELEMENTO SIGUIENTE
                    if(a < r->valor){
                        p = p->obtener_auxiliar_izquierdo();
                        break;
                    }else if(r->valor <= a && a < r->siguiente_en_nodo->valor){
                        p = r->nodo;
                        break;
                    }
                }else if(r->siguiente_en_nodo){             /// R ESTA AL FINAL DEL NODO
                    if(r->valor <= a){
                        p = r->nodo;
                        break;
                    }
                }else{                              /// R ESTA EN MEDIO DEL NODO
                    if(r->valor <= a && a < r->siguiente_en_nodo->valor){
                        p = r->nodo;
                        break;
                    }
                }
                r = r->siguiente_en_nodo;
            }
        }
    }
    return p;
}
