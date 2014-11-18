
#ifndef HAVE_PILA_H
#define HAVE_PILA_H

#include "Nodo.h"

template <class T>
class Pila
{
    public:
        Pila();
        ~Pila();
        void meter(T&);
        bool sacar();
        unsigned int numElementos();
        bool cima(T&);
        
    private:
        Nodo<T>* _cima;
        unsigned int _cantidad;
};

#include "Pila.cpp"

#endif
