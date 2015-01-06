
#ifndef HAVE_LISTA_H
#define HAVE_LISTA_H

#include "Nodo.h"
#include "numutils.h"
#include <iostream>
using namespace std;

template <class T>
class Lista
{
    public:
        Lista();
        bool sacar(uint indice, T &valor);
        bool borrar(uint indice);
        bool introducir(uint indice, const T &valor);
        uint cantidad();

		// Debe redefinirse T, con otro nombre: http://www.cplusplus.com/forum/general/23865/#msg125444
		template <class T2>
		friend ostream& operator<<(ostream& salida, const Lista<T2>& lista);

    private:
        Nodo<T> *_cabeza;
        uint _cantidad;
        bool indiceANodo(uint indice, Nodo<T>** &nodo);
};

#include "Lista.cpp"

#endif
