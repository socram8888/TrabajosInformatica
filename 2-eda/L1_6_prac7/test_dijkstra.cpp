
/**
 * Prueba de funcionamiento de Dijkstra
 * @author Marcos Vives Del Sol
 */

#include "grafo.h"
#include "dijkstra.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;

#define NODOS 8
#define NODO_INICIAL 0

int main()
{
    srand(0);

    Grafo g = Grafo(NODOS);

    cout << "Arco entre 0 y 1 no creado: " << g(0, 1) << endl;
    g(0, 1) = 9001;
    cout << "Arco entre 0 y 1 creado: " << g(0, 1) << endl;

    try
    {
        g(99, 99);
        cout << "¡¡¡ NO HA OCURRIDO LA EXCEPCION !!!" << endl;
    }
    catch (const out_of_range &e)
    {
        cout << "Excepcion accediendo a arco desde 88 a 9999" << endl;
    }

    g.creaGrafoND(3, 30);

    vector<float> pvecino;
    vector<unsigned> vecino;
    dijkstra(g, NODO_INICIAL, pvecino, vecino);

    for (unsigned nodo = 0; nodo < g.size(); nodo++)
    {
        cout << nodo << ": ";

        unsigned nodoActual = nodo;
        float pesoTotal = 0;

        while (nodoActual != NODO_INICIAL)
        {
            cout << nodoActual << " -> ";
            pesoTotal += pvecino[nodoActual];
            nodoActual = vecino[nodoActual];
        }

        cout << nodoActual << " (peso total: " << pesoTotal << ")" << endl;
    }

    return 0;
}
