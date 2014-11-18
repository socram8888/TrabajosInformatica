
#include "ResuelveLaberinto.h"
#include "sysdep.h"
#include "Pila.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

ResuelveLaberinto::ResuelveLaberinto()
{
    srand(time(NULL));
}

bool ResuelveLaberinto::leerFichero(string ruta)
{
	bool ok;
	ifstream fich;

	fich.open(ruta.c_str());
	ok = leerTam(fich) && leerFilas(fich);
	fich.close();

	return ok;
}

bool ResuelveLaberinto::leerTam(istream& entrada)
{
	string buffer;

	getline(entrada, buffer);
	tamY = atoi(buffer.c_str());
	if (tamY < 1 || tamY > MAX_TAMY)
		return false;

	getline(entrada, buffer);
	tamX = atoi(buffer.c_str());
	if (tamX < 1 || tamX > MAX_TAMX)
		return false;

	return true;
}

bool ResuelveLaberinto::leerFilas(istream& entrada)
{
	int i;

	for (i = 0; i < tamY; i++)
	{
		if (!leerColumnas(entrada, i))
			return false;
	}

	return true;
}

bool ResuelveLaberinto::leerColumnas(istream& entrada, int fila)
{
	string buffer;
	int i;

	getline(entrada, buffer);

	if (buffer.length() < tamX) {
		return false;
	}

	for (i = 0; i < tamX; i++) {
		if (!celdaValida(buffer[i]))
			return false;

		mapa[i][fila] = buffer[i];
	}

	return true;
}

bool ResuelveLaberinto::celdaValida(char celda)
{
	switch (celda)
	{
		case PARED:
		case ESPACIO:
		case CAMINO:
		case VISITADO:
			return true;
	}

	return false;
}

char ResuelveLaberinto::celdaACaracter(char celda)
{
	switch (celda)
	{
		case PARED:
			return '\xDB';
		case CAMINO:
			return '\xFA';
	}

	return ' ';
}

void ResuelveLaberinto::dibujar()
{
	int x, y;

	for (y = 0; y < tamY; y++)
	{
		for (x = 0; x < tamX; x++)
			cout << celdaACaracter(mapa[x][y]);
		cout << '\n';
	}
}

void ResuelveLaberinto::dimeTamanyo(int &nFilas, int &nColumnas) 
{
	 nFilas = tamX;
	 nColumnas = tamY;
}

void ResuelveLaberinto::marcarCelda(Celda celda, char valor)
{
	mapa[celda.dameX()][celda.dameY()] = valor;
}

bool ResuelveLaberinto::comprobarValida(Celda celda)
{
	int x, y;

	x = celda.dameX();
	y = celda.dameY();

	if (x < 0 || x >= tamX || y < 0 || y >= tamY)
		return false;

	return mapa[x][y] == ESPACIO;
}

bool ResuelveLaberinto::comprobarSalida(Celda celda)
{
	bool salida = false;
	int x, y;

	x = celda.dameX();
	y = celda.dameY();

	if (x == 0 || x == tamX - 1)
		return true;

	if (y == 0 || y == tamY - 1)
		return true;

	return false;
}

int ResuelveLaberinto::obtenerVecinos(Celda centro, ListaVecinos &listaVecinos)
{
	int x, y;
	int vecinos = 0;
	Celda colindante;

	x = centro.dameX();
	y = centro.dameY();

	colindante = Celda(x - 1, y);
	if (comprobarValida(colindante))
		listaVecinos[vecinos++] = colindante;

	colindante = Celda(x + 1, y);
	if (comprobarValida(colindante))
		listaVecinos[vecinos++] = colindante;

	colindante = Celda(x, y - 1);
	if (comprobarValida(colindante))
		listaVecinos[vecinos++] = colindante;

	colindante = Celda(x, y + 1);
	if (comprobarValida(colindante))
		listaVecinos[vecinos++] = colindante;

	return vecinos;
}

bool ResuelveLaberinto::obtenerVecinoAleatorio(Celda celda, Celda &vecino)
{
	ListaVecinos listaVecinos;
	int vecinos;

	vecinos = obtenerVecinos(celda, listaVecinos);
	if (vecinos == 0)
		return false;

	vecino = listaVecinos[rand() % vecinos];
	return true;
}

bool ResuelveLaberinto::resolver(int fila, int columna)
{
	Celda actual(fila, columna);
	if (!comprobarValida(actual)) {
		cerr << "Celda inicial no valida";
		return false;
	}

	Pila<Celda> recorrido;
	recorrido.meter(actual);
	marcarCelda(actual, CAMINO);

	while (true)
	{
		if (obtenerVecinoAleatorio(actual, actual))
		{
			recorrido.meter(actual);
	        marcarCelda(actual, CAMINO);
		}
		else
		{
            marcarCelda(actual, VISITADO);
            recorrido.sacar();
			recorrido.cima(actual);
		}

		if (recorrido.numElementos() == 0)
			return false;

		if (comprobarSalida(actual))
			return true;

        display_move(0, 0);
		dibujar();
		sysdep_sleep(10);
	}
}
