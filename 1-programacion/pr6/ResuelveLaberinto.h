
#ifndef HAVE_RESUELVELABERINTO_H
#define HAVE_RESUELVELABERINTO_H

#include "Celda.h"
#include <string>
#include <fstream>
using namespace std;

class ResuelveLaberinto
{
	public:
		ResuelveLaberinto();
		bool leerFichero(string ruta);
		void dimeTamanyo(int &nFilas, int &nColumnas);

		void dibujar();
		bool resolver(int fila, int columna);

	private:
		static const char PARED = 'P';
		static const char ESPACIO = 'E';
		static const char CAMINO = 'C';
		static const char VISITADO = 'V';

		static const int MAX_TAMX = 100;
		static const int MAX_TAMY = 100;
		typedef char Laberinto[MAX_TAMX][MAX_TAMY];
		typedef Celda ListaVecinos[4];

		Laberinto mapa;
		int tamX, tamY;		// Tamaño del laberinto

		bool leerTam(istream& entrada);
		bool leerFilas(istream& entrada);
		bool leerColumnas(istream& entrada, int fila);

		bool celdaValida(char);
		char celdaACaracter(char celda);

		void marcarCelda(Celda c, char valor);
		bool comprobarValida(Celda c);
		bool comprobarSalida(Celda c);

		int obtenerVecinos(Celda celda, ListaVecinos &listaVecinos);
		bool obtenerVecinoAleatorio(Celda celda, Celda &vecino);
};

#endif
