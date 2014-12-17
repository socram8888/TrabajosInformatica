
/**
 * Ejemplo útil de Dijkstra con retenes de bomberos y pueblos
 * @author Marcos Vives Del Sol
 */

#include "grafo.h"
#include "dijkstra.h"
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;

#define PUNTOS 10
#define RETENES 2

int main()
{
    srand(time(NULL));

    Grafo g = Grafo(PUNTOS);
    g.creaGrafoND(3, 30);

    cout << "Pesos:" << endl;
    for (unsigned x = 0; x < PUNTOS; x++)
    {
        cout << "   ";
        for (unsigned y = 0; y < PUNTOS; y++)
            printf("%4.1f ", g(x, y));
        cout << endl;
    }
    cout << endl;

    for (unsigned reten = 0; reten < RETENES; reten++)
    {
        cout << "========== RETEN " << reten << " ==========" << endl;

        vector<float> pvecino;
        vector<unsigned> vecino;
        dijkstra(g, reten, pvecino, vecino);

        for (unsigned nodo = RETENES; nodo < PUNTOS; nodo++)
        {
            cout << "Punto " << nodo << ": ";

            unsigned nodoActual = nodo;
            float pesoTotal = 0;

            while (nodoActual != reten)
            {
                cout << nodoActual << " -> ";
                pesoTotal += pvecino[nodoActual];
                nodoActual = vecino[nodoActual];
            }

            cout << nodoActual << " (peso total: " << pesoTotal << ")" << endl;
        }

        cout << endl;
    }

    return 0;
}
