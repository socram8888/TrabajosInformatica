
/**
 * Prueba de eficiencia de Dijkstra
 * @author Marcos Vives Del Sol
 */

#include "grafo.h"
#include "dijkstra.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

#define EXECS 50

/**
 * Ejecuta EXECS iteraciones de Dijkstra con grafos aleatorios.
 * @param size Tamaño del grafo
 * @return Número medio de pasos por iteración.
*/
double dijkstraBenchmark(unsigned int size)
{
    Grafo g = Grafo(size);
    vector<float> pvecino;
    vector<unsigned> vecino;
    unsigned long long pasos = 0;

    for (unsigned exec = 0; exec < EXECS; exec++)
    {
        g.creaGrafoND(3, 30);
        unsigned pasosInicio = g.getAccesos();
        dijkstra(g, 0, pvecino, vecino);
        pasos += g.getAccesos() - pasosInicio;
    }

    return (double) pasos / (double) EXECS;
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
    calculoCoste(5, 100, 5, func, f);
    f.close();
}

int main()
{
    srand(time(NULL));
    generateFunctionSteps("dijkstra.dat", dijkstraBenchmark);
    return 0;
}
