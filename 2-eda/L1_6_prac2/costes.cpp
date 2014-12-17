
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> // rand y srand
#include <time.h>
using namespace std;

unsigned int fa(unsigned int n, float &pasos)
{
	// func fa(n: Nat) dev k: Nat
	unsigned int i, j, k;

	k = 0; pasos++; // k ← 0

	for (i = 1; i <= n; i++) // para i ← 1 hasta n
	{
		pasos++; // Comparación exitosa del for exterior

		for (j = 1, pasos++; j < i; j++) // para j ← 1 hasta i-1
		{
			pasos++; // Comparación exitosa del for interior
			k += j; pasos++; // k ← k + j
		} // fpara
		pasos++; // Comparación fallida del for interior
	} // fpara
	pasos++; // Comparación exitosa del for exterior

	return k;
}

float faAux(unsigned int n)
{
	float pasos = 0;
	fa(n, pasos);
	return pasos;
}

bool fb(const vector<bool> &v, float &pasos) {
	// func fb(v: Vector[1..n] de {0,1}) dev cic:Bool
	unsigned int a, b;
	bool cic;

	a = 0; pasos++; // a ← 1
	b = v.size() - 1; pasos++; // b ← n

	while (a < b && v[a] == v[b]) // mientras (a < b) ∧ (v[a] = v[b]) hacer
	{
		pasos++; // Comparación exitosa del while

		a++; pasos++; // a ← a + 1
		b--; pasos++; // b ← b - 1
	} // fmientras
	pasos++; // Comparación fallida del while

	pasos++;
	if (a >= b) // si (a >= b) entonces
	{
		cic = true; pasos++; // cic ← cierto
	}
	else
	{
		cic = false; pasos++; // cic ← cierto
	}

	return cic;
}

inline bool randBool()
{
	return (rand() & 1) == 1;
}

vector<bool> genRandomBoolVector(unsigned int len)
{
	vector<bool> v;
	while (len-- > 0)
		v.push_back(randBool());
	return v;
}

static const float NUM_ITERS = 100000;

float fbRandomMean(unsigned int n)
{
	vector<bool> v;
	unsigned int i;
	float pasos = 0;

	for (i = 0; i < NUM_ITERS; i++)
	{
		v = genRandomBoolVector(n);
		fb(v, pasos);
	}

	return pasos / NUM_ITERS;
}

vector<bool> genFalseBoolVector(unsigned int len)
{
	vector<bool> v;
	while (len-- > 0)
		v.push_back(false);
	return v;
}

float fbAux(unsigned int n)
{
	vector<bool> v;
	float pasos = 0;

	v = genFalseBoolVector(n);
	fb(v, pasos);

	return pasos;
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
void evaluar(unsigned int inicio, unsigned int fin, unsigned int inc, float (*func)(unsigned int), ostream& output)
{
	unsigned int n;
	float pasos;

	for (n = inicio; n <= fin; n += inc) {
		pasos = func(n);
		output << n << ' ' << pasos << endl;
	}
}

/**
 * Genera el archivo el archivo con los datos necesarios para representar los pasos
 * @param filename Nombre del archivo de salida
 * @param func Función a representar
 * @param iters Número de iteraciones que ejecutar la función. El resultado es la media de todas las iteraciones.
*/
void generateFunctionSteps(string filename, float (*func)(unsigned int))
{
	ofstream f;
	f.open(filename.c_str());
	evaluar(4, 100, 4, func, f);
	f.close();
}

int main()
{
	srand(time(NULL));

	generateFunctionSteps("at.dat", faAux);
	generateFunctionSteps("bt.dat", fbAux);
	generateFunctionSteps("bt_random.dat", fbRandomMean);
	
	return 0;
}
