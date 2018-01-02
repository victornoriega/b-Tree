#include <iostream>
#include <limits>
#include "arbol_bp.h"
#include "math.h"

using namespace std;

///     **************************************************************************************************
///     CONSTRUCTOR
///     **************************************************************************************************
Arbol_BP::Arbol_BP(int ord){
    altura = 0;
    orden = ord;
    raiz = NULL;
    orden_minimo = ceil(orden / 2.0);
}

///     **************************************************************************************************
///     DESTRUCTOR
///     **************************************************************************************************
Arbol_BP::~Arbol_BP(){
    int valor_minimo = numeric_limits<int>::min();
    Nodo * hoja1 = buscar_hoja(valor_minimo);
    Nodo * hoja2;

    orden_minimo = ceil(orden / 2.0);

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
                }else if(/**r == p->obtener_principio()**/ !r->anterior_en_nodo){              /// R ES EL PRINCIPIO PERO HAY UN ELEMENTO SIGUIENTE
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
///     DESCRIPCION: FUNCION NECESARIA PARA SACAR ELEMENTOS QUE ESTAN DENTRO DEL ARBOL
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
bool Arbol_BP::sacar(int a){
    /// HOJA DONDE DEBERIA ESTAR EL VALOR

    Nodo * p = buscar_hoja(a);
    if(!p){
        return false;
    }else{
        /// SE PUEDE SACAR DE LA HOJA
        if(p->obtener_cuantos() > (orden / 2)){
            /// BUSCAR EL VALOR DENTRO DE LA HOJA
            Valor * valor_a_sacar = p->obtener_principio();
            while(valor_a_sacar){
                if(valor_a_sacar->valor == a)
                    break;
                valor_a_sacar = valor_a_sacar->siguiente_en_hoja;
            }
            if(!valor_a_sacar)
                return false;

            /// EL VALOR NO ESTA ENTRE LOS NODOS INTERNOS
            if(!valor_a_sacar->nodo_interno)
                p->sacar_de_hoja(a);
            /// EL VALOR ESTA DENTRO DE LOS NODOS INTERNOS HAY QUE ACTUALIZARLO
            else{
                Nodo * nodo_interno = valor_a_sacar->nodo_interno;
                Nodo * nodo = valor_a_sacar->nodo;

                valor_a_sacar->nodo_interno = NULL;
                valor_a_sacar->nodo = NULL;

                nodo_interno->sacar_de_nodo(valor_a_sacar);

                if(valor_a_sacar->siguiente_en_hoja){
                    valor_a_sacar->siguiente_en_hoja->nodo_interno = nodo_interno;
                    valor_a_sacar->siguiente_en_hoja->nodo = nodo;

                    nodo_interno->agregar_en_nodo(valor_a_sacar->siguiente_en_hoja);
                }else{
                    cout << "No hay siguiente dentro de la hoja" << endl;
                }
                p->sacar_de_hoja(valor_a_sacar->valor);
            }
            return true;
        /// LA CANTIDAD DE ELEMENTOS EN LA HOJA ES LA MINIMA
        }else{
            /// LA HOJA ANTERIOR PUEDE PRESTARLE A LA HOJA Y COMPARTEN PADRE
            if(p->obtener_auxiliar_izquierdo() && p->obtener_auxiliar_izquierdo()->obtener_cuantos() > (orden/2) &&
               p->obtener_auxiliar_izquierdo()->obtener_padre() == p->obtener_padre()){
                empujar_izquierdo(p, p->obtener_auxiliar_izquierdo(), a);

            /// LA HOJA SIGUIENTE PUEDE PRESTARLE A LA HOJA Y COMPARTEN PADRE
            }else if(p->obtener_auxiliar_derecho() && p->obtener_auxiliar_derecho()->obtener_cuantos() > (orden/2) &&
                     p->obtener_auxiliar_derecho()->obtener_padre() == p->obtener_padre()){
                empujar_derecho(p, p->obtener_auxiliar_derecho(), a);

            /// La HOJA ANTERIOR NO PUEDE PRESTARLE PERO PUEDEN COMBINARSE Y COMPARTEN PADRE
            }else if(p->obtener_auxiliar_izquierdo() && p->obtener_auxiliar_izquierdo()->obtener_padre() == p->obtener_padre()){
                combinar(p, p->obtener_auxiliar_izquierdo(), a);

            /// LA HOJA SIGUIENTE NO PUEDE PRESTARLE PERO PUEDEN COMBINARSE Y COMPARTEN PADRE
            }else if(p->obtener_auxiliar_derecho() && p->obtener_auxiliar_derecho()->obtener_padre() == p->obtener_padre()){
                combinar(p, p->obtener_auxiliar_derecho(), a);
            }
        }
    }
    return true;
}

///     **************************************************************************************************
///     EMPUJAR IZQUIERDO
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::empujar_izquierdo(Nodo * p, Nodo * q, int a){
    Nodo * hoja_actual = p;
    Nodo * hoja_izquierda = q;
    Nodo * nodo_interno;
    Nodo * nodo;

    Valor * valor_prestado = hoja_izquierda->obtener_principio();

    /// OBTENER EL ULTIMO ELEMENTO DEL NODO IZQUIERDO
    while(true){
        if(!valor_prestado->siguiente_en_hoja)
            break;
        valor_prestado = valor_prestado->siguiente_en_hoja;
    }

    Valor * valor_a_sacar = hoja_actual->obtener_principio();
    /// OBTENER EL VALOR A SACAR DE LA HOJA
    while(valor_a_sacar){
        if(valor_a_sacar->valor == a)
            break;
        valor_a_sacar = valor_a_sacar->siguiente_en_hoja;
    }
    /// NO SE ENCONTRO EL VALOR EN LA HOJA
    if(!valor_a_sacar)
        return;

    int valor_izquierdo = valor_prestado->valor;
    hoja_izquierda->sacar_de_hoja(valor_izquierdo);

    /// EL VALOR A SACAR TIENE REFERENCIA A NODO INTERNO
    if(valor_a_sacar->nodo_interno){
        nodo_interno = valor_a_sacar->nodo_interno;
        nodo = valor_a_sacar->nodo;

        valor_a_sacar->nodo_interno = NULL;
        valor_a_sacar->nodo = NULL;

        nodo_interno->sacar_de_nodo(valor_a_sacar);

        hoja_actual->sacar_de_hoja(a);
        hoja_actual->agregar_en_hoja(valor_izquierdo);

        hoja_actual->obtener_lugar_agregado()->nodo_interno = nodo_interno;
        hoja_actual->obtener_lugar_agregado()->nodo = nodo;

        nodo_interno->agregar_en_nodo(hoja_actual->obtener_lugar_agregado());
    /// EL VALOR A SACAR NO TIENE NODO INTERNO HAY QUE ACTUALIZAR LA HOJA
    }else{
        nodo_interno = hoja_actual->obtener_principio()->nodo_interno;
        nodo = hoja_actual->obtener_principio()->nodo;

        hoja_actual->obtener_principio()->nodo_interno = NULL;
        hoja_actual->obtener_principio()->nodo = NULL;

        nodo_interno->sacar_de_nodo(hoja_actual->obtener_principio());

        hoja_actual->sacar_de_hoja(a);
        hoja_actual->agregar_en_hoja(valor_izquierdo);

        hoja_actual->obtener_lugar_agregado()->nodo_interno = nodo_interno;
        hoja_actual->obtener_lugar_agregado()->nodo = nodo;

        nodo_interno->agregar_en_nodo(hoja_actual->obtener_lugar_agregado());
    }
}

///     **************************************************************************************************
///     EMPUJAR DERECHO
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Arbol_BP::empujar_derecho(Nodo *p, Nodo *q, int a){
    Nodo * hoja_actual = p;
    Nodo * hoja_derecha = q;
    Nodo * nodo_interno;
    Nodo * nodo;

    /// VALOR QUE SE SACARA DE LA HOJA ACTUAL
    Valor * valor_a_sacar = hoja_actual->obtener_principio();
    while(valor_a_sacar){
        if(valor_a_sacar->valor == a)
            break;
        valor_a_sacar = valor_a_sacar->siguiente_en_hoja;
    }
    if(!valor_a_sacar)
        return;

    /// TOMAR EL PRINCIPIO DEL NODO DERECHO
    Valor * valor_prestado = hoja_derecha->obtener_principio();

    int valor_derecho = valor_prestado->valor;

    /// AMBOS ESTAN EN NODOS INTERNOS
    if(valor_prestado->nodo_interno && valor_a_sacar->nodo_interno){
        int valor_actual = valor_a_sacar->valor;

        Valor * auxiliar;
        Nodo * nodo_interno;
        Nodo * nodo;

        nodo_interno = valor_a_sacar->nodo_interno;
        nodo = valor_a_sacar->nodo;

        if(valor_a_sacar->siguiente_en_hoja){
            auxiliar = valor_a_sacar->siguiente_en_hoja;
            auxiliar->nodo_interno = nodo_interno;
            auxiliar->nodo = nodo;

            valor_a_sacar->nodo_interno = NULL;
            valor_a_sacar->nodo = NULL;

            nodo_interno->sacar_de_nodo(valor_a_sacar);
            nodo_interno->agregar_en_nodo(auxiliar);

            hoja_actual->sacar_de_hoja(valor_actual);
            hoja_actual->agregar_en_hoja(valor_derecho);
        }else{
            cout << "No hay nodo siguiente en la hoja" << endl;
        }

        /// *******************************************************************************************
        valor_actual = hoja_derecha->obtener_principio()->valor;

        nodo_interno = valor_prestado->nodo_interno;
        nodo = valor_prestado->nodo;

        if(valor_prestado->siguiente_en_hoja){
            auxiliar = valor_prestado->siguiente_en_hoja;
            auxiliar->nodo_interno = nodo_interno;
            auxiliar->nodo = nodo;

            valor_prestado->nodo_interno = NULL;
            valor_prestado->nodo = NULL;

            nodo_interno->sacar_de_nodo(valor_prestado);
            nodo_interno->agregar_en_nodo(auxiliar);

            hoja_derecha->sacar_de_hoja(valor_actual);
        }else{
            cout << "No hay nodo siguiente en la hoja" << endl;
        }
    /// SOLO EL VALOR PRESTADO ESTA EN UN NODO
    }else if(valor_prestado->nodo_interno){
        hoja_actual->sacar_de_hoja(a);
        hoja_actual->agregar_en_hoja(valor_prestado->valor);

        nodo_interno = valor_prestado->nodo_interno;
        nodo = valor_prestado->nodo;

        valor_prestado->nodo_interno = NULL;
        valor_prestado->nodo = NULL;

        nodo_interno->sacar_de_nodo(valor_prestado);
        if(valor_prestado->siguiente_en_hoja){
            valor_prestado->siguiente_en_hoja->nodo_interno = nodo_interno;
            valor_prestado->siguiente_en_hoja->nodo = nodo;
            nodo_interno->agregar_en_nodo(valor_prestado->siguiente_en_hoja);

            hoja_derecha->sacar_de_hoja(valor_prestado->valor);
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
    /// P ES UN NODO INTERNO LLENO
    Nodo * q = new Nodo();
    q->nuevo_nodo();

    Valor * valor_subir = p->obtener_mitad();
    p->sacar_de_nodo(valor_subir);

    Valor * a1 = p->obtener_mitad();
    Valor * a2;

    if(!p->obtener_hermano_derecho()){
        p->establecer_hermano_derecho(q);
        q->establecer_hermano_izquierdo(p);
    }else{
        q->establecer_hermano_derecho(p->obtener_hermano_derecho());
        q->obtener_hermano_derecho()->establecer_hermano_izquierdo(q);
        q->establecer_hermano_izquierdo(p);
        p->establecer_hermano_derecho(q);
    }

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
        p->sacar_de_hoja(x2->valor);
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
///     COMBINAR HOJAS
///     PARAMETROS: NADA
///     RETORNO: NADA
///     **************************************************************************************************
void Arbol_BP::combinar(Nodo * p, Nodo * q, int a){
    /// P TIENE LA MINIMA CANTIDAD DE VALORES Y Q NO LE PUEDE PRESTAR
    /// SE TIENE QUE SACAR UN VALOR DE P
    Nodo * hoja_actual = p;
    Nodo * hoja_hermana = q;

    Nodo * nodo_padre = p->obtener_padre();

    Nodo * nodo_interno;
    Nodo * nodo;

    /// TOMAR EL VALOR QUE SE SACARA DE P
    Valor * auxiliar = hoja_actual->obtener_principio();
    while(auxiliar){
        if(auxiliar->valor == a)
            break;
        auxiliar = auxiliar->siguiente_en_hoja;
    }
    if(!auxiliar)
        return;

    /// LA HOJA HERMANA ES DERECHA      COMBINAR EN P
    if(hoja_hermana == hoja_actual->obtener_auxiliar_derecho()){
        if(auxiliar->nodo_interno){
            /// METER LOS VALORES DE LA HOJA HERMANA EN LA HOJA ACTUAL
            /// *********************************************************************
            nodo_interno = hoja_hermana->obtener_principio()->nodo_interno;
            nodo = hoja_hermana->obtener_principio()->nodo;

            hoja_hermana->obtener_principio()->nodo_interno = NULL;
            hoja_hermana->obtener_principio()->nodo = NULL;

            nodo_interno->sacar_de_nodo(hoja_hermana->obtener_principio());

            Valor * copia = hoja_hermana->obtener_principio();
            while(copia){
                hoja_actual->agregar_en_hoja(copia->valor);
                copia = copia->siguiente_en_hoja;
            }
            hoja_hermana->terminar_hoja();
            /// *********************************************************************

            /// ACTUALIZAR LA HOJA Y SACAR EL VALOR
            /// *********************************************************************
            nodo_interno = auxiliar->nodo_interno;
            nodo = auxiliar->nodo;

            auxiliar->nodo_interno = NULL;
            auxiliar->nodo = NULL;

            nodo_interno->sacar_de_nodo(auxiliar);
            auxiliar->siguiente_en_hoja->nodo_interno = nodo_interno;
            auxiliar->siguiente_en_hoja->nodo = nodo;
            nodo_interno->agregar_en_nodo(auxiliar->siguiente_en_hoja);

            hoja_actual->sacar_de_hoja(auxiliar->valor);
            /// *********************************************************************

        }else{
            /// METER LOS VALORES DE LA HOJA HERMANA EN LA HOJA ACTUAL
            /// *********************************************************************
            nodo_interno = hoja_hermana->obtener_principio()->nodo_interno;
            nodo = hoja_hermana->obtener_principio()->nodo;

            hoja_hermana->obtener_principio()->nodo_interno = NULL;
            hoja_hermana->obtener_principio()->nodo = NULL;

            nodo_interno->sacar_de_nodo(hoja_hermana->obtener_principio());

            Valor * copia = hoja_hermana->obtener_principio();
            while(copia){
                hoja_actual->agregar_en_hoja(copia->valor);
                copia = copia->siguiente_en_hoja;
            }
            hoja_hermana->terminar_hoja();

            /// SACAR EL VALOR
            /// *********************************************************************
            hoja_actual->sacar_de_hoja(auxiliar->valor);
            /// *********************************************************************
        }
    /// LA HOJA HERMANA ES IZQUIERDA    COMBINAR EN Q
    }else if(hoja_hermana == hoja_actual->obtener_auxiliar_izquierdo()){
        /// METER LOS VALORES DE LA HOJA ACTUAL EN LA HOJA HERMANA
        /// *********************************************************************
        nodo_interno = hoja_actual->obtener_principio()->nodo_interno;
        nodo = hoja_actual->obtener_principio()->nodo;

        hoja_actual->obtener_principio()->nodo_interno = NULL;
        hoja_actual->obtener_principio()->nodo = NULL;

        nodo_interno->sacar_de_nodo(hoja_actual->obtener_principio());

        hoja_actual->sacar_de_hoja(auxiliar->valor);

        Valor * copia = hoja_actual->obtener_principio();
        while(copia){
            hoja_hermana->agregar_en_hoja(copia->valor);
            copia = copia->siguiente_en_hoja;
        }
        hoja_actual->terminar_hoja();
    }
    if(nodo_padre->obtener_cuantos() >= orden / 2){
        cout << "El padre esta bien es nodo interno" << endl;
    }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() >= 1){
        cout << "El padre esta bien es raiz" << endl;
    }else{
        cout << "El padre necesita de iterar " << endl;
        Nodo * nodo_auxiliar = nodo_padre;
        while(!combinar_nodos_internos(nodo_auxiliar)){
            nodo_auxiliar = nodo_auxiliar->obtener_padre();
        }
    }
}

///     **************************************************************************************************
///     COMBINAR NODOS INTERNOS
///     PARAMETROS: NADA
///     RETORNO: NADA
///     **************************************************************************************************
/**bool Arbol_BP::combinar_nodos_internos(Nodo * p){
    /// P ES UN NODO INTERNO
    Nodo * nodo_interno = p;
    Nodo * nodo_padre = nodo_interno->obtener_padre();
    Nodo * nodo_hermano;

    Valor * valor_a_subir;
    Valor * valor_a_bajar;

    /// EL HERMANO DERECHO PUEDE PRESTARLE AL NODO
    if(p->obtener_hermano_derecho() && p->obtener_hermano_derecho()->obtener_cuantos() > orden/2 &&
       p->obtener_hermano_derecho()->obtener_padre() == p->obtener_padre()){
        cout << "El hermano derecho le presta" << endl;
        nodo_hermano = nodo_interno->obtener_hermano_derecho();
        /// BUSCAR EL NODO HERMANO DENTRO DEL PADRE
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_hermano)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        if(!valor_a_bajar){
            cout << "Esto no deberia de suceder" << endl;
            return false;
        }
        /// TOMAR EL VALOR QUE SE VA A SUBIR
        valor_a_subir = nodo_hermano->obtener_principio();

        valor_a_bajar->nodo = NULL;
        valor_a_bajar->nodo_interno = NULL;
        nodo_padre->sacar_de_nodo(valor_a_bajar);

        valor_a_bajar->nodo_interno = nodo_interno;
        valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();

        nodo_interno->agregar_en_nodo(valor_a_bajar);
        valor_a_bajar->nodo->establecer_padre(nodo_interno);

        valor_a_subir->nodo = NULL;
        valor_a_bajar->nodo_interno = NULL;
        nodo_hermano->sacar_de_nodo(valor_a_subir);

        valor_a_subir->nodo = nodo_hermano;
        valor_a_bajar->nodo_interno = nodo_padre;
        nodo_padre->agregar_en_nodo(valor_a_bajar);

        return true;
    /// EL HERMANO IZQUIERDO PUEDE PRESTARLE AL NODO
    }else if(p->obtener_hermano_izquierdo() && p->obtener_hermano_izquierdo()->obtener_cuantos() > orden/2 &&
             p->obtener_hermano_izquierdo()->obtener_padre() == p->obtener_padre()){

        cout << "El hermano izquierdo le presta" << endl;
        nodo_hermano = nodo_interno->obtener_hermano_izquierdo();

        /// SELECCIONAR EL VALOR A BAJAR
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_interno)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        if(!valor_a_bajar){
            cout << "Esto no deberia de suceder" << endl;
            return false;
        }
        /// SELECCIONAR EL VALOR A SUBIR
        valor_a_subir = nodo_hermano->obtener_principio();
        Valor * aux;
        while(valor_a_subir){
            aux = valor_a_subir;
            valor_a_subir = valor_a_subir->siguiente_en_nodo;
        }
        if(!valor_a_subir)
            valor_a_subir = aux;

        valor_a_bajar->nodo = NULL;
        valor_a_bajar->nodo_interno = NULL;
        nodo_padre->sacar_de_nodo(valor_a_bajar);

        valor_a_bajar->nodo_interno = nodo_interno;
        valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();

        nodo_interno->agregar_en_nodo(valor_a_bajar);
        nodo_interno->establecer_auxiliar_izquierdo(valor_a_subir->nodo);
        nodo_interno->obtener_auxiliar_izquierdo()->establecer_padre(nodo_interno);

        valor_a_subir->nodo = NULL;
        valor_a_subir->nodo_interno = NULL;
        nodo_hermano->sacar_de_nodo(valor_a_subir);

        valor_a_subir->nodo = nodo_interno;
        valor_a_subir->nodo_interno = nodo_padre;
        nodo_padre->agregar_en_nodo(valor_a_subir);
        return true;
    /// TIENE HERMANO DERECHO PERO NO PUEDE PRESTARLE NORMALMENTE
    }else if(p->obtener_hermano_derecho() && p->obtener_hermano_derecho()->obtener_padre() == p->obtener_padre()){
        cout << "El hermano derecho no puede prestarle normalmente" << endl;
        nodo_hermano = nodo_interno->obtener_hermano_derecho();
        /// BUSCAR EL VALOR A BAJAR
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_hermano)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        /// EL NODO PADRE PUEDE BAJAR NORMALMENTE
        if(nodo_padre->obtener_cuantos() > orden/2 && nodo_padre != raiz){

            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            nodo_interno->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_hermano->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_interno;
                nodo_interno->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();
            return true;
        /// EL NODO PADRE NO PUEDE BAJAR NORMALMENTE
        }else if(nodo_padre != raiz){
            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            nodo_interno->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_hermano->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_interno;
                nodo_interno->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();
            return false;
        /// EL NODO PADRE ES RAIZ PERO PERMITE SUBFLUJO
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() > 1){
            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            nodo_interno->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_hermano->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_interno;
                nodo_interno->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();
            return true;
        /// LA ALTURA TIENE QUE DISMINUIR
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() == 1){

            nodo_hermano->establecer_padre(NULL);
            nodo_interno->establecer_padre(NULL);

            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            nodo_interno->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_hermano->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_interno;
                nodo_interno->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();
            nodo_padre->terminar_nodo();
            raiz = nodo_interno;
            altura--;
            return true;
        }
    /// TIENE HERMANO IZQUIERDO PERO NO PUEDE PRESTARLE NORMALMENTE
    }else if(p->obtener_hermano_izquierdo() && p->obtener_hermano_izquierdo()->obtener_padre() == p->obtener_padre()){

        cout << "El hermano izquierdo no puede prestarle normalmente" << endl;
        nodo_hermano = nodo_interno->obtener_hermano_izquierdo();
        /// BUSCAR EL VALOR A BAJAR
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_interno)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        /// EL NODO PADRE PUEDE BAJAR NORMALMENTE
        if(nodo_padre->obtener_cuantos() > orden/2 && nodo_padre != raiz){
            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_interno->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_hermano;
                nodo_hermano->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            return true;
        /// EL NODO PADRE NO PUEDE BAJAR NORMALMENTE
        }else if(nodo_padre != raiz){
            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_interno->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_hermano;
                nodo_hermano->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            return false;
        /// EL NODO PADRE ES RAIZ PERO PERMITE SUBFLUJO
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() > 1){
            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_interno->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_hermano;
                nodo_hermano->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            return true;
        /// LA ALTURA TIENE QUE DISMINUIR
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() >= 1){

            nodo_hermano->establecer_padre(NULL);
            nodo_interno->establecer_padre(NULL);

            valor_a_bajar->nodo = NULL;
            valor_a_bajar->nodo_interno = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);

            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            Valor * copia = nodo_interno->obtener_principio();
            Valor * copia2;
            Nodo * nodo_auxiliar;
            while(copia){
                copia2 = copia;
                copia = copia->siguiente_en_nodo;

                nodo_auxiliar = copia2->nodo;
                copia2->nodo = NULL;
                copia2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(copia2);

                copia2->nodo = nodo_auxiliar;
                copia2->nodo_interno = nodo_hermano;
                nodo_hermano->agregar_en_nodo(copia2);
                copia2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            nodo_padre->terminar_nodo();
            altura--;
            raiz = nodo_hermano;
            return true;
        }
    }
    return true;
}**/

bool Arbol_BP::combinar_nodos_internos(Nodo * p){
    Nodo * nodo_interno = p;
    Nodo * nodo_padre = nodo_interno->obtener_padre();
    Nodo * nodo_hermano;

    Valor * valor_a_subir;
    Valor * valor_a_bajar;

    /// EL NODO TIENE HERMANO DERECHO Y PUEDE PRESTARLE
    if(p->obtener_hermano_derecho() && p->obtener_hermano_derecho()->obtener_cuantos() > orden/2 &&
       p->obtener_hermano_derecho()->obtener_padre() == p->obtener_padre()){

        cout << "Tiene hermano derecho y puede prestarle" << endl;

        nodo_hermano = nodo_interno->obtener_hermano_derecho();
        /// OBTENER EL VALOR QUE SE BAJARA
        /// **********************************************************************
        valor_a_bajar = p->obtener_padre()->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_hermano)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        /// **********************************************************************

        /// OBTENER EL VALOR QUE SE SUBIRA
        /// **********************************************************************
        valor_a_subir = nodo_hermano->obtener_principio();
        /// **********************************************************************

        /// ACTUALIZAR PUNTEROS VALOR A BAJAR
        /// **********************************************************************
        valor_a_bajar->nodo = NULL;
        valor_a_bajar->nodo_interno = NULL;

        nodo_interno->obtener_padre()->sacar_de_nodo(valor_a_bajar);

        valor_a_bajar->nodo_interno = nodo_interno;
        valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
        valor_a_bajar->nodo->establecer_padre(nodo_interno);
        nodo_interno->agregar_en_nodo(valor_a_bajar);
        /// **********************************************************************

        /// ACTUALIZAR PUNTEROS VALOR A SUBIR
        /// **********************************************************************
        nodo_hermano->establecer_auxiliar_izquierdo(valor_a_subir->nodo);

        valor_a_subir->nodo = NULL;
        valor_a_subir->nodo_interno = NULL;

        nodo_hermano->sacar_de_nodo(valor_a_subir);

        valor_a_subir->nodo_interno = nodo_interno->obtener_padre();
        valor_a_subir->nodo = nodo_hermano;
        nodo_interno->obtener_padre()->agregar_en_nodo(valor_a_subir);
        /// **********************************************************************

        return true;
    /// EL NODO TIENE HERMANO IZQUIERDO Y PUEDE PRESTARLE
    }else if(p->obtener_hermano_izquierdo() && p->obtener_hermano_izquierdo()->obtener_cuantos() > orden/2 &&
             p->obtener_hermano_izquierdo()->obtener_padre() == p->obtener_padre()){

        cout << "Tiene hermano izquierdo y puede prestarle" << endl;

        nodo_hermano = nodo_interno->obtener_hermano_izquierdo();
        /// OBTENER EL VALOR QUE SE BAJARA
        /// **********************************************************************
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_interno)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        /// **********************************************************************

        /// OBTENER EL VALOR QUE SE VA A SUBIR
        /// **********************************************************************
        valor_a_subir = nodo_hermano->obtener_principio();
        while(true){
            if(!valor_a_subir->siguiente_en_nodo)
                break;
            valor_a_subir = valor_a_subir->siguiente_en_nodo;
        }
        /// **********************************************************************
        /// ACTUALIZAR PUNTEROS VALOR A BAJAR
        /// **********************************************************************
        valor_a_bajar->nodo = NULL;
        valor_a_bajar->nodo_interno = NULL;
        nodo_padre->sacar_de_nodo(valor_a_bajar);

        valor_a_bajar->nodo_interno = nodo_interno;
        valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();

        nodo_interno->establecer_auxiliar_izquierdo(valor_a_subir->nodo);
        nodo_interno->obtener_auxiliar_izquierdo()->establecer_padre(nodo_interno);
        nodo_interno->agregar_en_nodo(valor_a_bajar);
        /// **********************************************************************

        /// ACTUALIZAR PUNTEROS VALOR A SUBIR
        /// **********************************************************************
        valor_a_subir->nodo = NULL;
        valor_a_subir->nodo_interno = NULL;

        nodo_hermano->sacar_de_nodo(valor_a_subir);

        valor_a_subir->nodo_interno = nodo_padre;
        valor_a_subir->nodo = nodo_interno;

        nodo_padre->agregar_en_nodo(valor_a_subir);
        /// **********************************************************************
        return true;
    /// EL NODO TIENE HERMANO DERECHO PERO NO PUEDE PRESTAR NORMALMENTE     COMBINAR EN P
    }else if(p->obtener_hermano_derecho() && p->obtener_hermano_derecho()->obtener_padre() == p->obtener_padre()){

        cout << "Tiene hermano derecho pero no puede prestarle directamente" << endl;

        nodo_hermano = nodo_interno->obtener_hermano_derecho();

        /// OBTENER EL VALOR QUE SE BAJARA
        /// **********************************************************************
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_hermano)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        /// **********************************************************************

        /// EL NODO PADRE PUEDE BAJAR UN VALOR
        if(nodo_padre != raiz && nodo_padre->obtener_cuantos() > orden/2){

            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_interno->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            /// COPIAR EL NODO HERMANO EN EL NODO INTERNO
            /// **********************************************************************
            Valor * auxiliar = nodo_hermano->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(auxiliar2);
                nodo_interno->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_interno;
                auxiliar2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();

            return true;
        /// EL NODO PADRE NO PUEDE BAJAR NORMALMENTE
        }else if(nodo_padre != raiz){

            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_interno->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            /// COPIAR EL NODO HERMANO EN EL NODO INTERNO
            /// **********************************************************************
            Valor * auxiliar = nodo_hermano->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(auxiliar2);
                nodo_interno->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_interno;
                auxiliar2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();

            return false;
        /// EL NODO PADRE ES LA RAIZ Y PUEDE TENER SUBFLUJO
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() > 1){
            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_interno->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            /// COPIAR EL NODO HERMANO EN EL NODO INTERNO
            /// **********************************************************************
            Valor * auxiliar = nodo_hermano->obtener_principio();
            Valor * auxiliar2;
            ///
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                ///
                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(auxiliar2);
                nodo_interno->agregar_en_nodo(auxiliar2);

                ///
                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_interno;
                auxiliar2->nodo->establecer_padre(nodo_interno);
            }
            nodo_hermano->terminar_nodo();

            return true;
        /// EL NODO PADRE ES LA RAIZ Y SE TIENE QUE COMBINAR DISMINUYENDO LA ALTURA
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() == 1){

            nodo_hermano->establecer_padre(NULL);
            nodo_interno->establecer_padre(NULL);

            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_interno->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_interno;
            valor_a_bajar->nodo = nodo_hermano->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_interno);

            /// COPIAR EL NODO HERMANO EN EL NODO INTERNO
            /// **********************************************************************
            Valor * auxiliar = nodo_hermano->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_hermano->sacar_de_nodo(auxiliar2);
                nodo_interno->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_interno;
                auxiliar2->nodo->establecer_padre(nodo_interno);

            }
            nodo_hermano->terminar_nodo();
            nodo_padre->terminar_nodo();
            raiz = nodo_interno;
            altura--;
            return true;
        }
    /// EL NODO TIENE HERMANO IZQUIERDO PERO NO PUEDE PRESTAR NORMALMENTE       COMBINAR EN Q
    }else if(p->obtener_hermano_izquierdo() && p->obtener_hermano_izquierdo()->obtener_padre() == p->obtener_padre()){

        cout << "Tiene hermano izquierdo pero no puede prestarle normalmente................................" << endl;

        nodo_hermano = nodo_interno->obtener_hermano_izquierdo();
        /// OBTENER EL VALOR QUE SE BAJARA
        /// **********************************************************************
        valor_a_bajar = nodo_padre->obtener_principio();
        while(valor_a_bajar){
            if(valor_a_bajar->nodo == nodo_interno)
                break;
            valor_a_bajar = valor_a_bajar->siguiente_en_nodo;
        }
        /// **********************************************************************

        /// EL NODO PADRE PUEDE BAJAR UN VALOR
        if(nodo_padre != raiz && nodo_padre->obtener_cuantos() > orden/2){
            cout << "1" << endl;
            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            /// COPIAR EL NODO INTERNO EN EL NODO HERMANO
            /// **********************************************************************
            Valor * auxiliar = nodo_interno->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(auxiliar2);
                nodo_hermano->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_hermano;
                auxiliar2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            return true;
        /// EL NODO PADRE NO PUEDE BAJAR NORMALMENTE
        }else if(nodo_padre != raiz){
            cout << "2" << endl;
            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            /// COPIAR EL NODO INTERNO EN EL NODO HERMANO
            /// **********************************************************************
            Valor * auxiliar = nodo_interno->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(auxiliar2);
                nodo_hermano->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_hermano;
                auxiliar2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            return false;
        /// EL NODO PADRE ES LA RAIZ Y PUEDE TENER SUBFLUJO
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() > 1){
            cout << "3" << endl;
            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            /// COPIAR EL NODO INTERNO EN EL NODO HERMANO
            /// **********************************************************************
            Valor * auxiliar = nodo_interno->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(auxiliar2);
                nodo_hermano->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_hermano;
                auxiliar2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();

            return true;
        /// EL NODO PADRE ES LA RAIZ Y SE TIENE QUE COMBINAR DISMINUYENDO LA ALTURA
        }else if(nodo_padre == raiz && nodo_padre->obtener_cuantos() == 1){
            cout << "4" << endl;
            nodo_hermano->establecer_padre(NULL);
            nodo_interno->establecer_padre(NULL);

            /// ACTUALIZANDO PUNTEROS DEL VALOR A BAJAR
            /// **********************************************************************
            valor_a_bajar->nodo_interno = NULL;
            valor_a_bajar->nodo = NULL;
            nodo_padre->sacar_de_nodo(valor_a_bajar);
            nodo_hermano->agregar_en_nodo(valor_a_bajar);

            /// SACAR EL VALOR A BAJAR Y METERLO EN EL NUEVO NODO
            /// **********************************************************************
            valor_a_bajar->nodo_interno = nodo_hermano;
            valor_a_bajar->nodo = nodo_interno->obtener_auxiliar_izquierdo();
            valor_a_bajar->nodo->establecer_padre(nodo_hermano);

            /// COPIAR EL NODO INTERNO EN EL NODO HERMANO
            /// **********************************************************************
            Valor * auxiliar = nodo_interno->obtener_principio();
            Valor * auxiliar2;
            Nodo * nodo_auxiliar;
            while(auxiliar){
                auxiliar2 = auxiliar;
                auxiliar = auxiliar->siguiente_en_nodo;

                nodo_auxiliar = auxiliar2->nodo;
                auxiliar2->nodo = NULL;
                auxiliar2->nodo_interno = NULL;

                nodo_interno->sacar_de_nodo(auxiliar2);
                nodo_hermano->agregar_en_nodo(auxiliar2);

                auxiliar2->nodo = nodo_auxiliar;
                auxiliar2->nodo_interno = nodo_hermano;
                auxiliar2->nodo->establecer_padre(nodo_hermano);
            }
            nodo_interno->terminar_nodo();
            nodo_padre->terminar_nodo();
            raiz = nodo_hermano;
            altura--;
            return true;
        }
    }
    return true;
}
///     **************************************************************************************************
///     BAJAR
///     PARAMETROS: NADA
///     RETORNO: NADA
///     **************************************************************************************************

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
    ///Valor * primero;
    while(hoja){
        cout << "Hoja" << endl;
        ///cout << "Mitad: " << hoja->obtener_mitad()->valor << endl;
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
            /**if(p->nodo_interno)
                imprimir_nodos_internos(p->nodo_interno);**/
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
    /**if(raiz->obtener_mitad()){
        cout << "Hay mitad y es: " << raiz->obtener_mitad()->valor << endl;
    }**/
    ///cout << "Mitad de la raiz: " << raiz->obtener_mitad()->valor << endl;
    cout << "Altura: " << altura << endl;
}


void Arbol_BP::imprimir_nodos_internos(Nodo * p){
    Nodo * hermano_derecho = p;
    Valor * primero = hermano_derecho->obtener_principio();
    while(hermano_derecho){
        primero = hermano_derecho->obtener_principio();
        while(primero){
            cout << "Valores dentro del nodo interno: " << primero->valor << endl;
            primero = primero->siguiente_en_nodo;
        }
        hermano_derecho = hermano_derecho->obtener_hermano_derecho();
    }
}
