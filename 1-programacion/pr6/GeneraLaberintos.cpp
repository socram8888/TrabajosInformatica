#include <iostream>
#include <fstream>
#include <time.h>       // Incluye la funcion time()
#include <windows.h>    // Incluye la funcion Sleep()
#include <stack>

#include "GeneraLaberintos.h"
#include "sysdep.h"

using namespace std;

// 
GeneraLaberintos::GeneraLaberintos ()
: tamX(0), tamY(0)
{
	// Descomentar para generar laberintos de manera aleatoria
	// srand (time (NULL));	
}

// Establece el tamanyo del laberinto a generar
bool GeneraLaberintos::fijarTamanyo (int nColumnas, int nFilas)
{
    bool ok;
    
     // Comprobar el tamaño máximo permitido del laberinto a generar
	if ( nColumnas < 0 || nFilas < 0 || nColumnas > MAX_TAMX || nFilas > MAX_TAMY )
	{
		tamX = 0;
		tamY = 0;
		cerr << "Error: El tamanyo del laberinto es negativo o excede el maximo permitido" << endl;
		ok = false;
	}
	else
	{
		tamX = nColumnas;
		tamY = nFilas;
		ok = true;
	}
	
	return ok;
}

// Dibuja el mapa del laberinto con paredes y espacios
void GeneraLaberintos::dibujar ()
{
	for ( int i = 0; i < tamX; i++ )
	{
		for ( int j = 0; j < tamY; j++ )
			switch (mapa[i][j])
			{				
				case PARED: 
					cout << '\xDB';
					break;				
				case ESPACIO:
					cout << ' ';
					break;				
			}		
		cout << endl;
	}
}

// Guardar en un fichero la definicion del laberinto
bool GeneraLaberintos::guardarFichero (std::string nombre)
{
    bool ok;
	ofstream fichero (nombre.c_str());

	if (!fichero.is_open() )
		ok = false;
	else
	{		
		// Escribir el tamaño del laberinto (filas y columnas)
		fichero << tamX << endl;
		fichero << tamY << endl;
		
		// Para cada fila del laberinto, ...
		for ( int i = 0; i < tamX; i++ )
		{
			// ...escribir una linea con el estado de todas las celdas
			for ( int j = 0; j < tamY; j++ )
				fichero << mapa[i][j];			

			fichero << endl;
		}		

		ok = true;
	}
	
	return ok;
}

// Calcula el punto inicial (salida del laberinto) del algoritmo
// Nota: Las esquinas del laberinto se excluyen del calculo.
void GeneraLaberintos::calcularSalida (Celda &salida)
{
	int x, y;
	int lado = rand() % 4;

	switch (lado)
	{
		// Lado superior
		case 0:
			x = 1 + rand() % (tamX - 2);
			y = 0;
			break;
		// Lado inferior
		case 1:
			x = 1 + rand() % (tamX - 2);
			y = tamY - 1;
			break;
		// Lado izquierdo
		case 2:			
			x = 0;
			y = 1 + rand() % (tamY - 2);
			break;
		// Lado derecho
		case 3:			
			x = tamX - 1;
			y = 1 + rand() % (tamY - 2);
			break;
	}

	salida.fijar (x, y);	
}

// Establece el estado de una celda con el valor indicado
void GeneraLaberintos::marcarCelda (Celda c, char valor)
{
	int x, y;

	x = c.dameX();
	y = c.dameY();

	mapa[x][y] = valor;
}

// Comprueba si las coordenadas de la celda están dentro del laberinto
// y corresponden a una celda no visitada (pared)
bool GeneraLaberintos::celdaValida (int x, int y)
{
	bool celdaEnLaberinto = (x > 0) && (x < tamX - 1) && (y > 0) && (y < tamY - 1);
	bool ok;

	if (celdaEnLaberinto && mapa[x][y] == PARED)
		ok = true;
	else
		ok = false;
		
	return ok;
}

// Obtiene el número de vecinos validos de una celda
// Nota: Los vecinos adyacentes se calculan de dos en dos (vecino e intermedio),
// para conseguir que los pasillos del laberinto se generen correctamente con paredes en ambos lados
int GeneraLaberintos::obtenerVecinos (Celda celda, ListaVecinos listaVecinos, ListaVecinos listaIntermedios)
{
	int x, y;
	int numVecinos = 0;

	x = celda.dameX();
	y = celda.dameY();

	// Comprobar vecino superior	
	if (celdaValida (x + 2, y))
	{
		listaVecinos[numVecinos] = Celda(x + 2, y);
		listaIntermedios[numVecinos] = Celda(x + 1, y);
		numVecinos++;
	}

	// Comprobar vecino inferior
	if (celdaValida (x - 2, y))
	{
		listaVecinos[numVecinos] = Celda(x - 2, y);		
		listaIntermedios[numVecinos] = Celda(x - 1, y);
		numVecinos++;
	}

	// Comprobar vecino derecho	
	if (celdaValida (x, y + 2))
	{
		listaVecinos[numVecinos] = Celda(x, y + 2);		
		listaIntermedios[numVecinos] = Celda(x, y + 1);
		numVecinos++;
	}

	// Comprobar vecino izquierdo
	if (celdaValida (x, y - 2))
	{
		listaVecinos[numVecinos] = Celda(x, y - 2);
		listaIntermedios[numVecinos] = Celda(x, y - 1);
		numVecinos++;
	}

	return numVecinos;
}

// Obtiene un vecino aleatorio valido de la celda indicada
// Nota: Los vecinos adyacentes se calculan de dos en dos (vecino e intermedio),
// para conseguir que los pasillos del laberinto se generen correctamente con paredes en ambos lados
bool GeneraLaberintos::obtenerVecinoAleatorio (Celda celda, Celda &aleatorio, Celda &intermedio)
{	
	bool hayVecino;
	int numVecinos, vecinoAleatorio;
	ListaVecinos listaVecinos, listaIntermedios;	

	numVecinos = obtenerVecinos (celda, listaVecinos, listaIntermedios);

	if ( numVecinos == 0)
		hayVecino = false;
	else
	{
	    hayVecino = true;
		vecinoAleatorio = rand() % numVecinos;
		aleatorio = listaVecinos[vecinoAleatorio];
		intermedio = listaIntermedios[vecinoAleatorio];
	}

	return hayVecino;
}

// Genera el laberinto según el algoritmo descrito en el enunciado
void GeneraLaberintos::generar ()
{
	Celda actual, vecino, intermedio;

	// Definir una pila para guardar elementos de tipo Celda
	stack<Celda> celdas;

	// Inicializar el laberinto con sólo paredes
	for (int i = 0; i < tamX; i++)
		for (int j = 0; j < tamY; j++)
			mapa[i][j] = PARED;

	// Calcular la posicion inicial y establecer como celda actual
	calcularSalida (actual);

	// Marcar la celda actual como espacio
	marcarCelda (actual, ESPACIO);	

	// Apilar la posicion de la celda actual
	celdas.push(actual);

	do
	{
		// Obtener una celda vecina aleatoria no visitada
		if (obtenerVecinoAleatorio (actual, vecino, intermedio))
		{
			// Marcar el vecino aleatorio (y el intermedio) como espacios
			marcarCelda (vecino, ESPACIO);
			marcarCelda (intermedio, ESPACIO);

			display_move(0, 0);
		    dibujar();
		    Sleep( 5 );

			// Apilar la posicion de la celda actual
			celdas.push(actual);		

			// Establecer la celda vecina como actual
			actual = vecino;			
		}
		// Comprobar si la pila no esta vacia
		else if (!celdas.empty())
		{
			// Establecer la celda actual como la ultima guardada en la pila
			actual = celdas.top();

			// Desapilar la ultima celda almacenada en la pila
			celdas.pop();
		}

		// Descomentar para observar como se genera el laberinto paso a paso
	}
	// Continuar el bucle mientras la pila no este vacia
	while (!celdas.empty());
}

