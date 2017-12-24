#ifndef VALOR_H_INCLUDED
#define VALOR_H_INCLUDED

class Nodo; /// PARA EVIAR LA DECLARACION A LA MISMA ESTRUCTURA DENTRO DE NODO

struct Valor{
    int valor;
    Valor * anterior_en_hoja;
    Valor * anterior_en_nodo;
    Valor * siguiente_en_hoja;
    Valor * siguiente_en_nodo;
    Nodo * nodo;
};

#endif // VALOR_H_INCLUDED
