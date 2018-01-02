#ifndef VALOR_H_INCLUDED
#define VALOR_H_INCLUDED

class Nodo; /// PARA EVIAR LA DECLARACION A LA MISMA ESTRUCTURA DENTRO DE NODO

struct Valor{
    int valor;
    Valor * anterior_en_hoja;
    Valor * anterior_en_nodo;
    Valor * siguiente_en_hoja;
    Valor * siguiente_en_nodo;
    Nodo * nodo;                /// REFERENCIA AL NODO / HOJA QUE DEBE REDIRIGIR EL VALOR
    Nodo * nodo_interno;        /// REFERENCIA AL NODO INTERNO EN EL QUE SE ENCUENTRA EL VALOR
};


#endif // VALOR_H_INCLUDED
