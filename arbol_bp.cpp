#include <iostream>
#include <limits>
#include "arbol_bp.h"

using namespace std;

///     **************************************************************************************************
///     CONSTRUCTOR
///     **************************************************************************************************
Arbol_BP::Arbol_BP(int ord){
    orden = ord;
    raiz = NULL;
}

///     **************************************************************************************************
///     DESTRUCTOR
///     **************************************************************************************************
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
            ///cout << "Principio del padre: " << p->obtener_principio()->valor << endl;
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
                }else if(r == p->obtener_principio()){              /// R ES EL PRINCIPIO PERO HAY UN ELEMENTO SIGUIENTE
                    if(a < r->valor){
                        p = p->obtener_auxiliar_izquierdo();
                        break;
                    }else if(r->valor <= a && a < r->siguiente_en_nodo->valor){
                        p = r->nodo;
                        break;
                    }
                }else if(!r->siguiente_en_nodo){                    /// R ESTA AL FINAL DEL NODO
                    if(r->valor <= a){
                        p = r->nodo;
                        break;
                    }
                }else{                                              /// R ESTA EN MEDIO DEL NODO
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

///     **************************************************************************************************
///     AGREGAR
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::agregar(int a){
    Nodo * p = buscar_hoja(a);
    if(!p){                                     /// LA RAIZ ES NULA
        p = new Nodo();
        p->nueva_hoja();
        raiz = p;

        p->agregar_en_hoja(a);
    }else{
        /// cout << "Principio de la hoja: " << p->obtener_principio()->valor << endl;
        if(p->obtener_cuantos() < orden - 1){   /// EXISTE RAIZ Y TIENE ESPACIO
            p->agregar_en_hoja(a);
        }else{                                  /// EXISTE RAIZ PERO NO TIENE ESPACIO
            p->agregar_en_hoja(a);

            Nodo * q = new Nodo();
            q->nueva_hoja();

            dividir_hoja(p,q);                  /// SE DIVIDE LA HOJA

            subir(p,q);
        }
    }
}

///     **************************************************************************************************
///     SUBIR
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::subir(Nodo * p, Nodo * q){
    if(!p->obtener_padre()){                /// P NO TIENE PADRE, CREANDO NUEVA RAIZ
        Nodo * z = new Nodo();              /// SE CREA UN NUEVO NODO RAIZ
        z->nuevo_nodo();
        raiz = z;

        p->establecer_padre(z);             /// SE ESTABLECEN LOS PADRES
        q->establecer_padre(z);

        z->establecer_auxiliar_izquierdo(p);                /// SE VINCULA P AL AUX IZQ DEL PADRE
        z->agregar_en_nodo(q->obtener_principio());         /// SE AGREGA EL VALOR INICIAL DE Q
        q->obtener_principio()->nodo = q;                   /// EL PRINCIPIO DE LA HOJA HACE REFERENCIA A LA HOJA
        q->obtener_principio()->nodo_interno = z;           /// SE LE DICE AL VALOR INICIAL EN QUE NODO INTERNO ESTA


    }else{
        if(p->obtener_padre()->obtener_cuantos() < orden - 1){              /// P TIENE PADRE Y ESTE TIENE ESPACIO
            p->obtener_padre()->agregar_en_nodo(q->obtener_principio());    /// SE AGREGA EL PRINCIPIO DE Q AL PADRE
            q->establecer_padre(p->obtener_padre());                        /// SE ESTABLECE EL PADRE DE Q

            q->obtener_principio()->nodo = q;                                /// EL PRINCIPIO DE LA HOJA HACE REFERENCIA A LA HOJA
            q->obtener_principio()->nodo_interno = q->obtener_padre();      /// SE LE DICE AL VALOR INICIAL EN QUE NODO INTERNO ESTA
        }else{
            p->obtener_padre()->agregar_en_nodo(q->obtener_principio());    /// SE AGREGA EL PRINCIPIO DE Q AL PADRE
            q->establecer_padre(p->obtener_padre());                        /// SE ESTABLECE EL PADRE DE Q

            q->obtener_principio()->nodo = q;                                /// EL PRINCIPIO DE LA HOJA HACE REFERENCIA A LA HOJA
            q->obtener_principio()->nodo_interno = q->obtener_padre();      /// SE LE DICE AL VALOR INICIAL EN QUE NODO INTERNO ESTA
        }
    }
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
        cout << "Hoja" << endl;
        p = hoja->obtener_principio();
        while(p){
            cout << "Valor: " << p->valor << endl;
            p = p->siguiente_en_hoja;
        }
        cout << endl;
        hoja = hoja->obtener_auxiliar_derecho();
    }
}
