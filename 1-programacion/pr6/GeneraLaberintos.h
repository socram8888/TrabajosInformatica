#ifndef _GENERA_LABERINTOS_H_
#define _GENERA_LABERINTOS_H_

#include <string>
#include "Celda.h"

class GeneraLaberintos
{
public:
	// Constructor
	GeneraLaberintos ();

    // Establece el tamanyo del laberinto a generar
    bool fijarTamanyo (int nColumnas, int nFilas);

	// Dibuja el mapa del laberinto con paredes y espacios
	void dibujar ();
	
	// Guardar en un fichero la definicion del laberinto
	bool guardarFichero (std::string nombre);

	// Genera el laberinto según el algoritmo descrito en el enunciado
	void generar ();
	
private:

	static const int MAX_TAMX = 100;
	static const int MAX_TAMY = 100;

	// Estados psibles de las celdas de un laberinto
	static const char PARED = 'P';		
	static const char ESPACIO = 'E';

	typedef char Laberinto[MAX_TAMX][MAX_TAMY];	// Definicion de un laberinto

	typedef Celda ListaVecinos[4];		// Definicion de una lista de celdas vecinas

	Laberinto mapa;		// Instancia de un laberinto

	int tamX, tamY;		// Tamaño del laberinto


	// Establece el estado de una celda con el valor indicado
	void marcarCelda (Celda c, char valor);
	
	// Calcula el punto inicial (salida del laberinto) del algoritmo
	void calcularSalida (Celda &salida);

    // Comprueba si las coordenadas de la celda están dentro del laberinto
    // y corresponden a una celda no visitada (pared)    
	bool celdaValida (int x, int y);	
	
	// Obtiene una lista de vecinos validos de una celda	
	int obtenerVecinos (Celda celda, ListaVecinos listaVecinos, ListaVecinos intermedios);
	
	// Obtiene un vecino aleatorio no visitado de la celda indicada
	bool obtenerVecinoAleatorio (Celda celda, Celda &aleatorio, Celda &intermedio);
};

#endif
