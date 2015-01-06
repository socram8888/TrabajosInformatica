
#include "listaatleta.h"
#include <strings.h>

int ListaAtleta::buscarPorNombre(string nombre)
{
	Atleta atleta;
	int pos = 0;

	bool encontrado = false;
	while (sacar(pos, atleta) && !encontrado)
	{
		if (strcasecmp(nombre.c_str(), atleta.devuelveNombre().c_str()) == 0)
			encontrado = true;
		else
			pos++;
	}

	if (!encontrado)
		pos = -1;

	return pos;
}

int ListaAtleta::buscarPorDorsal(int dorsal)
{
	Atleta atleta;
	int pos = 0;

	bool encontrado = false;
	while (sacar(pos, atleta) && !encontrado)
	{
		if (atleta.devuelveDorsal() == dorsal)
			encontrado = true;
		else
			pos++;
	}

	if (!encontrado)
		pos = -1;

	return pos;
}

void ListaAtleta::insertarPorTiempo(Atleta &atleta)
{
	Atleta otro;
	int pos = 0;

	bool encontrado = false;
	while (sacar(pos, otro) && !encontrado)
	{
		if (atleta.devuelveTiempo() > atleta.devuelveTiempo())
			encontrado = true;
		else
			pos++;
	}

	introducir(pos, atleta);
}
