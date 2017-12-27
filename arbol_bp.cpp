#include <iostream>
#include <limits>
#include "arbol_bp.h"

using namespace std;

///     **************************************************************************************************
///     CONSTRUCTOR
///     **************************************************************************************************
Arbol_BP::Arbol_BP(int ord){
    altura = 0;
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
        /// ***********************************************
        altura = 0;
        /// ***********************************************
    }else{
        if(p->obtener_cuantos() < orden - 1){   /// EXISTE RAIZ Y TIENE ESPACIO
            p->agregar_en_hoja(a);
        }else{                                  /// EXISTE RAIZ PERO NO TIENE ESPACIO
            p->agregar_en_hoja(a);

            /**if(a == 1){
                Valor * y3 = p->obtener_principio();
                while(y3){
                    cout << "En p, Valor: " << y3->valor << endl;
                    y3 = y3->siguiente_en_hoja;
                }
                Nodo * a1 = p->obtener_padre();
                Valor * b1 = a1->obtener_principio();
                while(b1){
                    cout << "En el padre de la hoja: " << b1->valor << endl;
                    b1 = b1->siguiente_en_nodo;
                }
            }**/

            Nodo * q = new Nodo();
            q->nueva_hoja();

            dividir_hoja(p,q);                  /// SE DIVIDE LA HOJA

            /**if(a == 1){
                Valor * y1 = p->obtener_principio();
                Valor * y2 = q->obtener_principio();

                while(y1){
                    cout << "En p, Valor: " << y1->valor << endl;
                    y1 = y1->siguiente_en_hoja;
                }
                while(y2){
                    cout << "En q, Valor: " << y2->valor << endl;
                    y2 = y2->siguiente_en_hoja;
                }
                if(p->obtener_padre()){
                    Valor * y4 = p->obtener_padre()->obtener_principio();
                    while(y4){
                        cout << "Padre del nodo     asddd: " << y4->valor << endl;
                        y4 = y4->siguiente_en_nodo;
                    }
                }
            }**/
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
    /// P y Q SON HOJAS
    Valor * a33 = p->obtener_principio();
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
        /// ***********************************************
        altura += 1;
        /// ***********************************************
    }else{
        if(p->obtener_padre()->obtener_cuantos() < orden - 1){              /// P TIENE PADRE Y ESTE TIENE ESPACIO
            p->obtener_padre()->agregar_en_nodo(q->obtener_principio());    /// SE AGREGA EL PRINCIPIO DE Q AL PADRE
            q->establecer_padre(p->obtener_padre());                        /// SE ESTABLECE EL PADRE DE Q

            q->obtener_principio()->nodo = q;                                /// EL PRINCIPIO DE LA HOJA HACE REFERENCIA A LA HOJA
            q->obtener_principio()->nodo_interno = p->obtener_padre();      /// SE LE DICE AL VALOR INICIAL EN QUE NODO INTERNO ESTA
        }else{
            p->obtener_padre()->agregar_en_nodo(q->obtener_principio());    /// SE AGREGA EL PRINCIPIO DE Q AL PADRE
            ///q->establecer_padre(p->obtener_padre());                        /// SE ESTABLECE EL PADRE DE Q

            q->obtener_principio()->nodo = q;                               /// EL PRINCIPIO DE LA HOJA HACE REFERENCIA A LA HOJA
            q->obtener_principio()->nodo_interno = p->obtener_padre();      /// SE LE DICE AL VALOR INICIAL EN QUE NODO INTERNO ESTA

            Nodo * auxiliar = p->obtener_padre();                   /// AUXILIAR ES UN NODO INTERNO
            while(!crecer(auxiliar)){                               /// INDICA SI SE NECESITA CRECER
                auxiliar = auxiliar->obtener_padre();
            }
        }
    }
}

///     **************************************************************************************************
///     CRECER
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
bool Arbol_BP::crecer(Nodo * p){
    Nodo * q = new Nodo();
    q->nuevo_nodo();

    Valor * valor_subir = p->obtener_mitad();
    p->sacar_de_nodo(valor_subir);

    Valor * a1 = p->obtener_mitad();
    Valor * a2;
    while(a1){
        a2 = a1;
        a1 = a1->siguiente_en_nodo;
        p->sacar_de_nodo(a2);
        q->agregar_en_nodo(a2);
        a2->nodo->establecer_padre(q);
    }

    q->establecer_auxiliar_izquierdo(valor_subir->nodo);
    q->obtener_auxiliar_izquierdo()->establecer_padre(q);
    valor_subir->nodo = q;

    if(!p->obtener_padre()){
        Nodo * r = new Nodo();
        r->nuevo_nodo();
        raiz = r;
        r->establecer_auxiliar_izquierdo(p);
        r->agregar_en_nodo(valor_subir);
        p->establecer_padre(r);
        q->establecer_padre(r);
        valor_subir->nodo_interno = r;
        /// ***********************************************
        altura += 1;
        /// ***********************************************
        return true;
    }else{
        if(p->obtener_padre()->obtener_cuantos() < orden - 1){
            p->obtener_padre()->agregar_en_nodo(valor_subir);
            q->establecer_padre(p->obtener_padre());
            valor_subir->nodo_interno = p->obtener_padre();
            return true;
        }else{
            p->obtener_padre()->agregar_en_nodo(valor_subir);
            q->establecer_padre(p->obtener_padre());
            valor_subir->nodo_interno = p->obtener_padre();
            return false;
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

void Arbol_BP::partir_raiz(){
    Nodo * p = raiz;
    Valor * mitad_raiz = p->obtener_mitad();
    p->sacar_de_nodo(mitad_raiz);

    Valor * a1 = p->obtener_mitad();
    Valor * a2;

    Nodo * q = new Nodo();
    q->nuevo_nodo();

    Nodo * nueva_raiz = new Nodo();
    nueva_raiz->nuevo_nodo();
    raiz = nueva_raiz;

    altura++;

    while(a1){
        a2 = a1;
        a1 = a1->siguiente_en_nodo;
        p->sacar_de_nodo(a2);
        q->agregar_en_nodo(a2);
    }
    q->establecer_auxiliar_izquierdo(mitad_raiz->nodo);
    mitad_raiz->nodo = q;
    mitad_raiz->nodo_interno = nueva_raiz;
    nueva_raiz->establecer_auxiliar_izquierdo(p);

    p->establecer_padre(nueva_raiz);
    q->establecer_padre(nueva_raiz);
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
        if(hoja->obtener_padre()){
            Valor * a1 = hoja->obtener_padre()->obtener_principio();
            while(a1){
                cout << "Valor en el padre: " << a1->valor << endl;
                a1 = a1->siguiente_en_nodo;
            }
        }
        p = hoja->obtener_principio();
        while(p){
            cout << "Valor: " << p->valor << endl;
            p = p->siguiente_en_hoja;
        }
        cout << endl;
        hoja = hoja->obtener_auxiliar_derecho();
    }
    cout << "La altura del arbol es: " << altura << endl;
}
