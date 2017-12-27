#include "nodo.h"
#include <iostream>

using namespace std;

enum{VACIO = 0,PRINCIPIO,ENMEDIO,FINAL};

///     **************************************************************************************************
///     CONSTRUCTOR
///     **************************************************************************************************
Nodo::Nodo(int ord){
    principio = NULL;
    mitad = NULL;
    anterior = NULL;
    orden = ord;
    cuantos = 0;
    mayores = 0;
    menores = 0;
    donde = VACIO;
    es_hoja = false;
    encontrado = false;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
}

///     **************************************************************************************************
///     DESTRUCTOR
///     **************************************************************************************************
Nodo::~Nodo(){
    Valor * p;
    while(principio){
        p = principio;
        principio = principio->siguiente_en_hoja;
        delete p;
    }
    principio = NULL;
    mitad = NULL;
    anterior = NULL;
    orden = 0;
    cuantos = 0;
    mayores = 0;
    menores = 0;
    donde = VACIO;
    es_hoja = false;
    encontrado = false;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
}

///     **************************************************************************************************
///     CONSTRUCTOR EN CODIGO PARA LAS HOJAS
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::nueva_hoja(int ord){
    principio = NULL;
    mitad = NULL;
    anterior = NULL;
    orden = ord;
    cuantos = 0;
    mayores = 0;
    menores = 0;
    donde = VACIO;
    es_hoja = true;
    encontrado = false;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
}

///     **************************************************************************************************
///     DESTRUCTOR EN CODIGO PARA LAS HOJAS
///     ELIMINA LOS VALORES DENTRO DE UNA HOJA Y POR LA ESTRUCTURA DEL PROGRAMA LOS ELIMINA DE LOS NODOS
///     INTERNOS. HAY QUE REINICIAR CADA NODO INTERNO UNA VEZ SE ELIMINA LA ULTIMA HOJA.
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::terminar_hoja(){
    Valor * p;
    while(principio){
        p = principio;
        principio = principio->siguiente_en_hoja;

        /// SACA LOS VALORES DE LOS NODOS INTERNOS REAJUSTANDO SUS SIGUIENTES Y ANTERIORES RESPECTO AL NODO
        if(p->anterior_en_nodo)
            p->anterior_en_nodo->siguiente_en_nodo = p->siguiente_en_nodo;
        if(p->siguiente_en_nodo)
            p->siguiente_en_nodo->anterior_en_nodo = p->anterior_en_nodo;

        delete p;
    }
    principio = NULL;
    mitad = NULL;
    anterior = NULL;
    orden = 0;
    cuantos = 0;
    mayores = 0;
    menores = 0;
    donde = VACIO;
    es_hoja = false;
    encontrado = false;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
}

///     **************************************************************************************************
///     CONSTRUCTOR EN CODIGO PARA LOS NODOS
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::nuevo_nodo(int ord){
    principio = NULL;
    mitad = NULL;
    anterior = NULL;
    orden = ord;
    cuantos = 0;
    mayores = 0;
    menores = 0;
    donde = VACIO;
    es_hoja = false;
    encontrado = false;
    padre = NULL;
    auxiliar_izquierdo = NULL;
    auxiliar_derecho = NULL;
}

///     **************************************************************************************************
///     BUSCAR
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
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
                }else if(!p->siguiente_en_hoja){
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
                p = p->siguiente_en_hoja;
            }
        }
    }
    donde = FINAL;
    encontrado = false;
    return;
}

///     **************************************************************************************************
///     AGREGAR EN HOJA
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::agregar_en_hoja(int a){
    buscar(a);
    Valor * q = new Valor;
    lugar_agregado = q;

    q->valor = a;
    q->nodo = NULL;
    q->siguiente_en_nodo = NULL;
    q->anterior_en_nodo = NULL;
    q->nodo_interno = NULL;

    if(donde == VACIO){
        principio = q;
        mitad = q;

        q->siguiente_en_hoja = NULL;
        q->anterior_en_hoja = NULL;

        ///mayores++;
    }else{
        Valor * p = mitad;
        if(p->valor <= a){  /// Aumenta los mayores
            mayores++;
            Valor * r;
            while(p){
                r = p;
                if(p->valor > a)    /// Se corta en el momento en que p es mayor
                    break;
                p = p->siguiente_en_hoja;
            }
            if(!p){ /// Llegó después del final en la busqueda
                q->siguiente_en_hoja = NULL;
                q->anterior_en_hoja = r;
                r->siguiente_en_hoja = q;
            }else{
                q->anterior_en_hoja = p->anterior_en_hoja;
                if(q->anterior_en_hoja)
                    q->anterior_en_hoja->siguiente_en_hoja = q;
                q->siguiente_en_hoja = p;
                q->siguiente_en_hoja->anterior_en_hoja = q;
            }
        }else{              /// Aumenta los menores
            menores++;
            while(p){
                if(p->valor <= a)
                    break;
                p = p->anterior_en_hoja;
            }
            if(!p){ /// Llegó antes del principio en la busqueda
                q->siguiente_en_hoja = principio;
                q->anterior_en_hoja = NULL;
                principio->anterior_en_hoja = q;
                principio = q;
            }else{
                q->siguiente_en_hoja = p->siguiente_en_hoja;
                if(q->siguiente_en_hoja)
                    q->siguiente_en_hoja->anterior_en_hoja = q;
                q->anterior_en_hoja = p;
                p->siguiente_en_hoja = q;
            }
        }
    }
    cuantos++;
    /// CHECAR LA CANTIDAD DE CUANTOS Y EL ORDEN PARA MANTENER EL SPLIT.
    if(mayores - menores > 1){
        mitad = mitad->siguiente_en_hoja;
        mayores--;
        menores++;
        return;
    }else if(menores - mayores > 1){
        mitad = mitad->anterior_en_hoja;
        menores--;
        mayores++;
        return;
    }
}

///     **************************************************************************************************
///     AGREGAR EN NODO
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::agregar_en_nodo(Valor * q){
    buscar(q->valor);

    if(donde == VACIO){
        principio = q;
        mitad = q;

        q->siguiente_en_nodo = NULL;
        q->anterior_en_nodo = NULL;
    }else{
        Valor * p = mitad;
        if(p->valor <= q->valor){  /// Aumenta los mayores
            mayores++;
            Valor * r;
            while(p){
                r = p;
                if(p->valor > q->valor)    /// Se corta en el momento en que p es mayor
                    break;
                p = p->siguiente_en_nodo;
            }
            if(!p){ /// Llegó después del final en la busqueda
                q->siguiente_en_nodo = NULL;
                q->anterior_en_nodo = r;
                r->siguiente_en_nodo = q;
            }else{
                q->anterior_en_nodo = p->anterior_en_nodo;
                if(q->anterior_en_nodo)
                    q->anterior_en_nodo->siguiente_en_nodo = q;
                q->siguiente_en_nodo = p;
                q->siguiente_en_nodo->anterior_en_nodo = q;
            }
        }else{              /// Aumenta los menores
            menores++;
            while(p){
                if(p->valor <= q->valor)
                    break;
                p = p->anterior_en_nodo;
            }
            if(!p){ /// Llegó antes del principio en la busqueda
                q->siguiente_en_nodo = principio;
                q->anterior_en_nodo = NULL;
                principio->anterior_en_nodo = q;
                principio = q;
            }else{
                q->siguiente_en_nodo = p->siguiente_en_nodo;
                if(q->siguiente_en_nodo)
                    q->siguiente_en_nodo->anterior_en_nodo = q;
                q->anterior_en_nodo = p;
                p->siguiente_en_nodo = q;
            }
        }
    }
    cuantos++;
    if(mayores - menores > 1){
        mitad = mitad->siguiente_en_nodo;
        mayores--;
        menores++;
        return;
    }else if(menores - mayores > 1){
        mitad = mitad->anterior_en_nodo;
        menores--;
        mayores++;
        return;
    }
}

///     **************************************************************************************************
///     SACAR
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
int Nodo::sacar(int a){
    buscar(a);
    if(!encontrado)
        return 0;
    else{
        Valor * p;
        if(donde == PRINCIPIO){
            p = principio;
            principio = p->siguiente_en_hoja;

        }else if(donde == FINAL){
            p = anterior->siguiente_en_hoja;
            anterior->siguiente_en_hoja = NULL;

        }else{
            p = anterior->siguiente_en_hoja;
            anterior->siguiente_en_hoja = p->siguiente_en_hoja;
            anterior->siguiente_en_hoja->anterior_en_hoja = anterior;

        }
        if(p->valor < mitad->valor)             /// MENOR QUE LA MITAD
            menores--;
        else if(mitad->valor < p->valor)        /// MAYOR QUE LA MITAD
            mayores--;
        else{                                   /// ES LA MITAD
            mitad = mitad->siguiente_en_hoja;
            mayores--;
        }

        if(mayores - menores > 1){
            mitad = mitad->siguiente_en_hoja;
            mayores--;
            menores++;
        }else if(menores - mayores > 1){
            mitad = mitad->anterior_en_hoja;
            menores--;
            mayores++;
        }
        delete p;

        cuantos--;
        return 1;
    }
}

///     **************************************************************************************************
///     SACAR DE NODO
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::sacar_de_nodo(Valor * p){
    cuantos--;
    if(p->siguiente_en_nodo)
        p->siguiente_en_nodo->anterior_en_nodo = p->anterior_en_nodo;
    if(p->anterior_en_nodo)
        p->anterior_en_nodo->siguiente_en_nodo = p->siguiente_en_nodo;

    if(p->valor < mitad->valor)             /// MENOR QUE LA MITAD
        menores--;
    else if(mitad->valor < p->valor)        /// MAYOR QUE LA MITAD
        mayores--;
    else{                                   /// ES LA MITAD
        mitad = mitad->siguiente_en_nodo;
        mayores--;
    }

    p->siguiente_en_nodo = NULL;
    p->anterior_en_nodo = NULL;

    /// NO HAY MITAD
    if(mayores - menores > 1){
        mitad = mitad->siguiente_en_nodo;
        mayores--;
        menores++;
    }else if(menores - mayores > 1){
        mitad = mitad->anterior_en_nodo;
        menores--;
        mayores++;
    }
}

///     **************************************************************************************************
///     PINTAR HOJA
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::pintar_hoja(){
    Valor * p = principio;
    if(mitad)
        cout << "Mitad: " << mitad->valor << endl << endl;
    while(p){
        cout << "Valor: " << p->valor << endl;
        p = p->siguiente_en_hoja;
    }
    cout << endl;
}

///     **************************************************************************************************
///     PINTAR NODO
///     DESCRIPCION:
///     PARAMENTROS:
///     RETORNO:
///     **************************************************************************************************
void Nodo::pintar_nodo(){
    Valor * p = principio;
    if(mitad)
        cout << "Mitad: " << mitad->valor << endl << endl;
    while(p){
        cout << "Valor: " << p->valor << endl;
        p = p->siguiente_en_nodo;
    }
}

///     **************************************************************************************************
///     OBTENER ORDEN DEL NODO
///     PARAMETROS: NADA
///     RETORNO: ENTERO QUE INDICA EL ORDEN DEL NODO
///     **************************************************************************************************
int Nodo::obtener_orden(){
    return orden;
}

///     **************************************************************************************************
///     OBTENER LA CANTIDAD DE ELEMENTOS EN EL NODO / HOJA
///     PARAMETROS: NADA
///     RETORNO: ENTERO QUE INDICA LA CANTIDAD DE ELEMENTOS EN EL NODO / HOJA
///     **************************************************************************************************
int Nodo::obtener_cuantos(){
    return cuantos;
}

///     **************************************************************************************************
///     OBTENER EL LUGAR AGREGADO
///     **************************************************************************************************
Valor * Nodo::obtener_lugar_agregado(){
    return lugar_agregado;
}

///     **************************************************************************************************
///     OBTENER EL PRINCIPIO DE UN NODO / HOJA
///     **************************************************************************************************
Valor * Nodo::obtener_principio(){
    return principio;
}

///     **************************************************************************************************
///     OBTENER LA MITAD DE UN NODO / HOJA
///     **************************************************************************************************
Valor * Nodo::obtener_mitad(){
    return mitad;
}

///     **************************************************************************************************
///     OBTENER EL AUXILIAR DERECHO DE UN NODO / HOJA
///     **************************************************************************************************
Nodo * Nodo::obtener_auxiliar_derecho(){
    return auxiliar_derecho;
}

///     **************************************************************************************************
///     ESTABLECER EL AUXILIAR DERECHO DE UN NODO / HOJA
///     **************************************************************************************************
void Nodo::establecer_auxiliar_derecho(Nodo * p){
    auxiliar_derecho = p;
}

///     **************************************************************************************************
///     ESTABLECER EL AUXILIAR IZQUIERDO DE UN NODO / HOJA
///     **************************************************************************************************
void Nodo::establecer_auxiliar_izquierdo(Nodo * p){
    auxiliar_izquierdo = p;
}

///     **************************************************************************************************
///     OBTENER EL AUXILIAR IZQUIERDO DE UN NODO / HOJA
///     **************************************************************************************************
Nodo * Nodo::obtener_auxiliar_izquierdo(){
    return auxiliar_izquierdo;
}

///     **************************************************************************************************
///     OBTENER EL PADRE DE UN NODO / HOJA
///     **************************************************************************************************
Nodo * Nodo::obtener_padre(){
    return padre;
}

///     **************************************************************************************************
///     ESTABLECE EL PADRE DE UN NODO
///     **************************************************************************************************
void Nodo::establecer_padre(Nodo * p){
    padre = p;
}

///     **************************************************************************************************
///     NODO ES HOJA
///     NOS DICE SI UN DETERMINADO NODO ES HOJA O NO
///     PARAMETROS: NADA
///     RETORNO: BOOLEANO QUE INDICA SI EL NODO ES HOJA
///     **************************************************************************************************
bool Nodo::nodo_es_hoja(){
    if(es_hoja)
        return true;
    else
        return false;
}
