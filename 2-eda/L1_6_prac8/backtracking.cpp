
/**
 * Prueba de algoritmo voraz para colorear nodos
 * @author Marcos Vives Del Sol
 */

#include "backtracking_algo.h"
#include <iostream>
#include <stdlib.h>

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

    cout << endl << "Colores requeridos: " << colorear_backtracking(g, c) + 1 << endl;
    for (unsigned i = 0; i < c.size(); i++)
        cout << c[i] << ' ';
    cout << endl << endl;

    return 0;
}
