
#ifndef HAVE_LISTAATLETA_H
#define HAVE_LISTAATLETA_H

#include "lista.h"
#include "atleta.h"

class ListaAtleta : public Lista<Atleta>
{
	public:
		int buscarPorNombre(string nombre);
		int buscarPorDorsal(int dorsal);
		void insertarPorTiempo(Atleta&);
};

#endif
