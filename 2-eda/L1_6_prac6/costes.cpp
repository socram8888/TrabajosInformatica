
/**
 * Realiza pruebas de velocidad en arboles, ABB y mapa de STL con un numero variable de elementos.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <time.h>
#include <limits>
#include "abb.h"
#include "tabla.h"
#include "alumno.h"
using namespace std;

unsigned int RUNS = 1000;

/**
 * Realiza una prueba de velocidad de busqueda en un mapa de STL
 * @param cnt Numero de elementos
 * @return Segundos por busqueda
*/
double mapBenchmark(unsigned int cnt)
{
	vector<string> dnis = vector<string>(cnt);
	map<string, Alumno> mapa;

	for (unsigned int i = 0; i < cnt; i++)
	{
		Alumno alumno = Alumno(0);
		string dni = alumno.getDNI();
		mapa[dni] = alumno;
		dnis[i] = dni;
	}

	Alumno alumno;
	clock_t start = clock();
	for (unsigned int run = 0; run < RUNS; run++)
		for (unsigned int i = 0; i < cnt; i++)
			alumno = mapa[dnis[i]];

	return (double) (clock() - start) / ((long long) CLOCKS_PER_SEC * RUNS * cnt);
}

/**
 * Realiza una prueba de velocidad de busqueda en un ABB
 * @param cnt Numero de elementos
 * @return Segundos por busqueda
*/
double abbBenchmark(unsigned int cnt)
{
	vector<string> dnis = vector<string>(cnt);
	ABB arbol;

	for (unsigned int i = 0; i < cnt; i++)
	{
		Alumno alumno = Alumno(0);
		string dni = alumno.getDNI();
		arbol.insertar(dni, alumno);
		dnis[i] = dni;
	}

	Alumno alumno;
	clock_t start = clock();
	for (unsigned int run = 0; run < RUNS; run++)
		for (unsigned int i = 0; i < cnt; i++)
			arbol.buscar(dnis[i], alumno);

	return (double) (clock() - start) / ((long long) CLOCKS_PER_SEC * RUNS * cnt);
}

/**
 * Realiza una prueba de velocidad de busqueda en una tabla
 * @param cnt Numero de elementos
 * @return Segundos por busqueda
*/
double tablaBenchmark(unsigned int cnt)
{
	vector<string> dnis = vector<string>(cnt);
	Tabla tabla = Tabla(cnt * 2);

	for (unsigned int i = 0; i < cnt; i++)
	{
		Alumno alumno = Alumno(0);
		string dni = alumno.getDNI();
		tabla.insertar(dni, alumno);
		dnis[i] = dni;
	}

	Alumno alumno;
	clock_t start = clock();
	for (unsigned int run = 0; run < RUNS; run++)
		for (unsigned int i = 0; i < cnt; i++)
			tabla.buscar(dnis[i], alumno);

	return (double) (clock() - start) / ((long long) CLOCKS_PER_SEC * RUNS * cnt);
}

/**
 * Escribe a un stream de salida el coste de la ejecución de una función
 * @param inicio Tamaño inicial de la entrada a la función
 * @param fin Tamaño final (inclusive) de la entrada a la función
 * @param inc Incremento del tamaño
 * @param iters Número de veces que ejecutar la función
 * @param func Función a ejecutar
 * @param output Salida
*/
void calculoCoste(unsigned int inicio, unsigned int fin, unsigned int inc, double (*func)(unsigned int), ostream& output)
{
	unsigned int n;
	double pasos;

	for (n = inicio; n <= fin; n += inc) {
		cout << " - " << n << endl;
		pasos = func(n);
		cout.precision(16);
		output << n << ' ' << scientific << pasos << endl;
	}
}

/**
 * Genera el archivo el archivo con los datos necesarios para representar los pasos
 * @param filename Nombre del archivo de salida
 * @param func Función a representar
 * @param iters Número de iteraciones que ejecutar la función. El resultado es la media de todas las iteraciones.
*/
void generateFunctionSteps(string filename, double (*func)(unsigned int))
{
	ofstream f;
	f.open(filename.c_str());
	calculoCoste(500, 5000, 500, func, f);
	f.close();
}

int main()
{
	cout << "Benchmark de mapa de STL" << endl;
	generateFunctionSteps("map.dat", mapBenchmark);

	cout << "Benchmark de ABB" << endl;
	generateFunctionSteps("abb.dat", abbBenchmark);

	cout << "Benchmark de tabla hash" << endl;
	generateFunctionSteps("tabla.dat", tablaBenchmark);
	
	return 0;
}

/*
 * Se puede deducir de la grafica que todos tienen una eficiencia muy alta,
 * y que el arbol binario no solo tiene un menor consumo de memoria, sino
 * que ademas es el mas rapido.
 */
