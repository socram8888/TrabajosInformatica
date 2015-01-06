
/**
 * Prueba de algoritmo voraz para colorear nodos
 * @author Marcos Vives Del Sol
 */

#include "voraz_algo.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define EXECS 50

/**
 * Ejecuta EXECS iteraciones de Dijkstra con grafos aleatorios.
 * @param size Tamaño del grafo
 * @return Número medio de pasos por iteración.
*/
double vorazBenchmark(unsigned int size)
{
    Grafo g = Grafo(size);
    vector<unsigned> colores;
    unsigned long long pasos = 0;

    for (unsigned exec = 0; exec < EXECS; exec++)
    {
        g.creaGrafoND50();
        unsigned pasosInicio = g.getAccesos();
        colorear_voraz(g, colores);
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

    Grafo g(8);
    vector<unsigned> c;
    g.creaGrafoND50();

    for (unsigned i = 0; i < g.size(); i++)
    {
        for (unsigned j = 0; j < g.size(); j++)
        {
            if (g(i, j))
                cout << "1 ";
            else
                cout << "0 ";
        }
        cout << endl;
    }

    cout << endl << "Colores requeridos: " << colorear_voraz(g, c) + 1 << endl;
    for (unsigned i = 0; i < c.size(); i++)
        cout << c[i] << ' ';
    cout << endl << endl;

    generateFunctionSteps("voraz_solo.dat", vorazBenchmark);
    return 0;
}
