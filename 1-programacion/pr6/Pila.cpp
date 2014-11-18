
#ifndef HAVE_PILA_CPP
#define HAVE_PILA_CPP

#include <cstdlib>
#include "Pila.h"

// Constructor de una pila vacia
template <class T>
Pila<T>::Pila()
{
    _cima = NULL;
    _cantidad = 0;
}

// Destructor de la pila: elimina todos los nodos de la memoria
template <class T>
Pila<T>::~Pila()
{
    while (sacar());
}

// Introduce un valor en la pila
template <class T>
void Pila<T>::meter(T& valor)
{
    _cima = new Nodo<T>(valor, _cima);
    _cantidad++;
}

// Elimina la cima de la pila. Devuelve false si la pila está vacía.
template <class T>
bool Pila<T>::sacar()
{
    bool ok = false;

    if (_cima)
    {
        Nodo<T>* anterior = _cima->siguiente();
        delete _cima;
        _cima = anterior;

        _cantidad--;
        ok = true;
    }

    return ok;
}

// Devuelve el número de elementos contenidos en la pila.
template <class T>
unsigned int Pila<T>::numElementos() {
    return _cantidad;
}

// Devuelve el valor contenido en la cima de la pila. Devuelve false si está vacía.
template <class T>
bool Pila<T>::cima(T& valor) {
    bool ok = false;
    
    if (_cima)
    {
        valor = _cima->valor();
        ok = true;
    }    

    return ok;
}

#endif
