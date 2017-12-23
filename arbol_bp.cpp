#include "arbol_bp.h"
#include <iostream>
#include <limits>

using namespace std;

/// BUSCAR LA HOJA DONDE SE DEBERIA INSERTAR EL VALOR
Nodo * Arbol_BP::buscar_hoja(int a){
    Nodo * p = raiz;
    Valor * r;
    if(!p)
        return NULL;
    else{

        /***************************
        /// CREAR BIEN LAS HOJAS Y DESTINGUIRLAS DE LOS NODOS INTERNOS PARA QUE ESTO TERMINE ... O EMPIECE
        ****************************/

        while(!es_hoja(p)){ /// Mientras sea nodo interno
            r = p->obtener_principio();
            while(r){
                if(!r->anterior && !r->siguiente){  /// R ES EL UNICO ELEMENTO DENTRO DEL NODO
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
                    }else if(r->valor <= a && a < r->siguiente->valor){
                        p = r->nodo;
                        break;
                    }
                }else if(r->siguiente){             /// R ESTA AL FINAL DEL NODO
                    if(r->valor <= a){
                        p = r->nodo;
                        break;
                    }
                }else{                              /// R ESTA EN MEDIO DEL NODO
                    if(r->valor <= a && a < r->siguiente->valor){
                        p = r->nodo;
                        break;
                    }
                }
                r = r->siguiente;
            }
        }
    }
    return p;
}

bool Arbol_BP::es_hoja(Nodo * p){
    if(p->nodo_es_hoja())
        return true;
    else
        return false;
}

void Arbol_BP::pintar(){
    /// PONER ESTE VALOR COMO CONSTANTE
    int valor_minimo = numeric_limits<int>::min();
    Nodo * hoja = buscar_hoja(valor_minimo);
    Valor * p;
    while(hoja){
        p = hoja->obtener_principio();
        while(p){
            cout << "Valor: " << p->valor << endl;
            p = p->siguiente;
        }
        hoja = hoja->obtener_auxiliar_derecho();
    }
}
