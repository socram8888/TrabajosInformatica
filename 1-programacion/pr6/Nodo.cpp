
#ifndef HAVE_NODO_CPP
#define HAVE_NODO_CPP

#include "Nodo.h"
#include <cstring>

// Esta interfaz representa un nodo para su uso en listas enlazadas

// Constructor dado un valor inicial
template <class T>
Nodo<T>::Nodo(T& valor) {
    _valor = valor;
    _siguiente = NULL;
}

// Constructor dado un valor y el siguiente nodo
template <class T>
Nodo<T>::Nodo(T& valor, Nodo* siguiente) {
    _valor = valor;
    _siguiente = siguiente;
}

// Getter para obtener el valor contenido. Se devuelve por referencia de modo que se puede alterar el contenido de valor.
template <class T>
T& Nodo<T>::valor() {
    return _valor;
}

// Getter para obtener el puntero al siguiente nodo. Puede devolver NULL si es el último. Se devuelve por referencia de modo que se puede alterar el puntero al siguiente nodo.
template <class T>
Nodo<T>*& Nodo<T>::siguiente() {
    return _siguiente;
}

#endif
