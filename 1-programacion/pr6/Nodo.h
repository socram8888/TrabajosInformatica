
#ifndef HAVE_NODO_H
#define HAVE_NODO_H

template <class T>
class Nodo
{
    public:
        Nodo(T&);
        Nodo(T&, Nodo*);
        void cambiarValor(T&);
        void cambiarSiguiente(Nodo*);
        T& valor();
        Nodo*& siguiente();

    private:
        T _valor;
        Nodo* _siguiente;    
};

#include "Nodo.cpp"

#endif
