
#ifndef HAVE_LISTA_CPP
#define HAVE_LISTA_CPP

#include "Lista.h"

template <class T>
Lista<T>::Lista()
{
    _cabeza = NULL;
    _cantidad = 0;
}

template <class T>
bool Lista<T>::sacar(uint indice, T &valor)
{
    Nodo<T>** ptrnodo;

    if (!indiceANodo(indice, ptrnodo) || *ptrnodo == NULL)
        return false;

    valor = (*ptrnodo)->valor;
    return true;
}

template <class T>
bool Lista<T>::borrar(uint indice)
{
    Nodo<T>** ptrnodo;

    if (!indiceANodo(indice, ptrnodo))
        return false;

    Nodo<T>* eliminar = *ptrnodo;
    *ptrnodo = eliminar->siguiente;
    delete eliminar;
    _cantidad--;

    return true;
}

template <class T>
bool Lista<T>::introducir(uint indice, const T &valor)
{
    Nodo<T>** ptrnodo;

    if (!indiceANodo(indice, ptrnodo))
        return false;
        
    Nodo<T>* siguiente = *ptrnodo;
    *ptrnodo = new Nodo<T>;
    (*ptrnodo)->valor = valor;
    (*ptrnodo)->siguiente = siguiente;
    _cantidad++;

    return true; 
}

template <class T>
uint Lista<T>::cantidad() {
    return _cantidad;
}

template <class T>
bool Lista<T>::indiceANodo(uint indice, Nodo<T>** &ptrnodo)
{
    ptrnodo = &_cabeza;

    while (*ptrnodo != NULL && indice > 0)
    {
        ptrnodo = &((*ptrnodo)->siguiente);
        indice--;
    }

    return indice == 0;
}

template <class T2>
ostream& operator<<(ostream& salida, Lista<T2>& lista)
{
	T2 elemento;
	int i = 0;

	while (lista.sacar(i++, elemento)) {
		salida << " - " << elemento << endl;
	}

	return salida;
}

#endif
