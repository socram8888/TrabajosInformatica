
/**
 * Implementación del algoritmo Dijkstra
 * @author Marcos Vives Del Sol
 */

#include <cmath>
#include "dijkstra.h"
#include <iostream>

void dijkstra(Grafo& grafo, unsigned inicio, vector<float>& pvecino, vector<unsigned>& vecino)
{
    unsigned dim = grafo.size();
    vecino = vector<unsigned>(dim, inicio);
    vector<bool> b = vector<bool>(dim, false);

    pvecino = vector<float>(dim);
    for (unsigned i = 0; i < dim; i++)
        pvecino[i] = grafo(inicio, i);

    b[inicio] = true;

    for (unsigned i = 1; i < dim; i++)
    {
        unsigned m = ~0;
        float min = INFINITY;

        for (unsigned j = 0; j < dim; j++)
        {
            if (!b[j] && 0 < pvecino[j] && pvecino[j] < min)
            {
                m = j;
                min = pvecino[j];
            }
        }

        b[m] = true;

        for (unsigned j = 0; j < dim; j++)
        {
            float pa;
            if (!b[j] && (pa = pvecino[m] + grafo(m, j)) < pvecino[j])
            {
                pvecino[j] = pa;
                vecino[j] = m;
            }
        }
    }
}