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

            Nodo * q = new Nodo();
            q->nueva_hoja();

            dividir_hoja(p,q);                  /// SE DIVIDE LA HOJA
            subir(p,q);
        }
    }
}

///     **************************************************************************************************
///     SACAR
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
bool Arbol_BP::sacar(int a){
    Nodo * p = buscar_hoja(a);
    if(!p){
        return false;
    }else{
        if(p->obtener_cuantos() > (orden / 2)){                     /// LOS NUMEROS PERMITEN SACAR UN ELEMENTO
            p->sacar_de_hoja(a);
        }else{                                                      /// LA CANTIDAD DE ELEMENTOS ES LA MINIMA
            if(p->obtener_auxiliar_izquierdo() || p->obtener_auxiliar_derecho()){
                if(p->obtener_auxiliar_izquierdo() && p->obtener_auxiliar_izquierdo()->obtener_cuantos() > (orden / 2)){
                    empujar_izquierdo(p, p->obtener_auxiliar_izquierdo(), a);
                }else if(p->obtener_auxiliar_derecho() && p->obtener_auxiliar_derecho()->obtener_cuantos() > (orden / 2)){
                    empujar_derecho(p,p->obtener_auxiliar_derecho(),a);
                }else{      /// O LAS HOJAS NO EXISTEN O NO COMPLEN CON EL MINIMO NECESARIO

                }
            }
        }
    }
    return true;
}

///     **************************************************************************************************
///     SUBIR
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::subir(Nodo * p, Nodo * q){
    /// P y Q SON HOJAS
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
        a2->nodo_interno = q;
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

///     **************************************************************************************************
///     EMPUJAR IZQUIERDO
///     DESCRIPCION: SI LA HOJA IZQUIERDA A LA HOJA DONDE SE HARA LA ELIMINACION PUEDE PRESTAR UN VALOR A LA HOJA
///     SE TOMA EL VALOR MAYOR DENTRO DE LA HOJA IZQUERDA.
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::empujar_izquierdo(Nodo * p, Nodo * q, int a){
    Nodo * hoja_actual = p;
    Nodo * hoja_izquierda = q;

    Valor * valor_prestado = hoja_izquierda->obtener_principio();
    while(true){                                    /// OBTENER EL ULTIMO ELEMENTO DEL NODO IZQUIERDO
        if(!valor_prestado->siguiente_en_hoja)
            break;
        valor_prestado = valor_prestado->siguiente_en_hoja;
    }

    Valor * valor_a_sacar = hoja_actual->obtener_principio();
    while(true){                                    /// OBTENER EL VALOR A SACAR DE LA HOJA
        if(valor_a_sacar->valor == a)
            break;
        valor_a_sacar = valor_a_sacar->siguiente_en_hoja;
    }

    int valor_izquierdo = valor_prestado->valor;
    hoja_izquierda->sacar_de_hoja(valor_izquierdo);

    Nodo * nodo_interno;
    Nodo * nodo;
    if(valor_a_sacar->nodo_interno){                                        /// EL VALOR A SACAR ES EL PRINCIPIO DE LA HOJA
        nodo_interno = valor_a_sacar->nodo_interno;
        nodo_interno->sacar_de_nodo(valor_a_sacar);
        valor_a_sacar->nodo_interno = NULL;

        nodo = valor_a_sacar->nodo;
        valor_a_sacar->nodo = NULL;

        p->sacar_de_hoja(a);
        p->agregar_en_hoja(valor_izquierdo);

        p->obtener_lugar_agregado()->nodo = nodo;
        p->obtener_lugar_agregado()->nodo_interno = nodo_interno;

        nodo_interno->agregar_en_nodo(p->obtener_lugar_agregado());
    }
    else{                                                                  /// EL VALOR A SACAR ESTA EN LA HOJA
        nodo_interno = p->obtener_principio()->nodo_interno;
        nodo_interno->sacar_de_nodo(p->obtener_principio());
        p->obtener_principio()->nodo_interno = NULL;

        nodo = p->obtener_principio()->nodo;
        p->obtener_principio()->nodo = NULL;

        p->sacar_de_hoja(a);
        p->agregar_en_hoja(valor_izquierdo);

        p->obtener_lugar_agregado()->nodo = nodo;
        p->obtener_lugar_agregado()->nodo_interno = nodo_interno;

        nodo_interno->agregar_en_nodo(p->obtener_lugar_agregado());
    }
}

///     **************************************************************************************************
///     EMPUJAR DERECHO
///     DESCRIPCION: SI LA HOJA DERECHA A LA HOJA DONDE SE HARA LA ELIMINACION PUEDE PRESTAR UN VALOR A LA HOJA
///     SE TOMA EL VALOR MENOR DENTRO DE LA HOJA DERECHA.
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::empujar_derecho(Nodo *p, Nodo *q, int a){
    Nodo * hoja_actual = p;
    Nodo * hoja_derecha = q;

    Nodo * nodo_interno;
    Nodo * nodo;

    Valor * valor_a_sacar = hoja_actual->obtener_principio();         /// VALOR QUE SE SACARA DE LA HOJA ACTUAL
    while(true){
        if(valor_a_sacar->valor == a)
            break;
        valor_a_sacar = valor_a_sacar->siguiente_en_hoja;
    }

    Valor * valor_prestado = hoja_derecha->obtener_principio();        /// TOMAR EL PRINCIPIO DEL NODO DERECHO

    int valor_derecho = hoja_derecha->obtener_principio()->valor;

    if(valor_prestado->nodo_interno && valor_a_sacar->nodo_interno){    /// AMBOS ESTAN EN NODOS INTERNOS
        int auxiliar = valor_a_sacar->valor;
        Nodo * nodo_interno_hoja_act = valor_a_sacar->nodo_interno;
        valor_a_sacar->nodo_interno = NULL;
        Nodo * nodo_hoja_act = valor_a_sacar->nodo;
        valor_a_sacar->nodo = NULL;

        valor_a_sacar->siguiente_en_hoja->nodo_interno = valor_a_sacar->nodo_interno;
        valor_a_sacar->siguiente_en_hoja->nodo = valor_a_sacar->nodo;

        nodo_interno_hoja_act->sacar_de_nodo(valor_a_sacar);
        nodo_interno_hoja_act->agregar_en_nodo(valor_a_sacar->siguiente_en_hoja);

        hoja_actual->sacar_de_hoja(auxiliar);
        hoja_actual->agregar_en_hoja(valor_prestado->valor);

        /// *******************************************************************************************

        nodo_interno = valor_prestado->nodo_interno;
        nodo_interno->sacar_de_nodo(valor_prestado);
        nodo_interno->agregar_en_nodo(valor_prestado->siguiente_en_hoja);

        valor_prestado->siguiente_en_hoja->nodo_interno = valor_prestado->nodo_interno;
        valor_prestado->siguiente_en_hoja->nodo = valor_prestado->nodo;

        valor_prestado->nodo_interno = NULL;
        valor_prestado->nodo = NULL;

        hoja_derecha->sacar_de_hoja(valor_derecho);

    }else if(valor_prestado->nodo_interno){                 /// SOLO EL VALOR PRESTADO ESTA EN UN NODO
        hoja_actual->sacar_de_hoja(a);
        hoja_actual->agregar_en_hoja(valor_prestado->valor);

        nodo_interno = valor_prestado->nodo_interno;
        nodo_interno->sacar_de_nodo(valor_prestado);
        nodo_interno->agregar_en_nodo(valor_prestado->siguiente_en_hoja);

        valor_prestado->siguiente_en_hoja->nodo_interno = valor_prestado->nodo_interno;
        valor_prestado->siguiente_en_hoja->nodo = valor_prestado->nodo;

        valor_prestado->nodo_interno = NULL;
        valor_prestado->nodo = NULL;

        hoja_derecha->sacar_de_hoja(valor_derecho);
    }
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
    Valor * primero;
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

    Nodo * en_la_raiz = raiz;
    Valor * valores_raiz = en_la_raiz->obtener_principio();
    while(valores_raiz){
        cout << "En la raiz: " << valores_raiz->valor << endl;
        valores_raiz = valores_raiz->siguiente_en_nodo;
    }
    cout << "Altura: " << altura << endl;
}
