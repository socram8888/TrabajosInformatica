
/**
 * Análisis de costes de coloración de grafos
 * @author Marcos Vives Del Sol
 */

#include "voraz_algo.h"
#include "backtracking_algo.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define EXECS 25

/*
 El backtracking es muchísimo más lento que el algoritmo voraz, pero también es
 más eficiente en el sentido de que es capa de realizar el coloreado con la
 menor cantidad de colores diferentes posibles
*/

int main()
{
    ofstream vorazDat;
    vorazDat.open("voraz.dat");

    ofstream vorazSolDat;
    vorazSolDat.open("voraz_sol.dat");

    ofstream btDat;
    btDat.open("bt.dat");

    ofstream btSolDat;
    btSolDat.open("bt_sol.dat");

    srand(time(NULL));

    for (unsigned n = 5; n <= 20; n++)
    {
        cout << " - " << n << endl;
        Grafo g(n);
        vector<unsigned> c(n);

        unsigned long long vorazAccesses = 0;
        unsigned long long vorazColors = 0;
        unsigned long long btAccesses = 0;
        unsigned long long btColors = 0;

        for (unsigned it = 0; it < EXECS; it++)
        {
            unsigned long long acc;

            g.creaGrafoND50();

            acc = g.getAccesos();
            vorazColors += colorear_voraz(g, c);
            vorazAccesses += (g.getAccesos() - acc);

            acc = g.getAccesos();
            btColors += colorear_backtracking(g, c);
            btAccesses += (g.getAccesos() - acc);
        }

        vorazDat << n << ' ' << (double) vorazAccesses / (double) EXECS << endl;
        vorazSolDat << n << ' ' << (double) vorazColors / (double) EXECS << endl;
        btDat << n << ' ' << (double) btAccesses / (double) EXECS << endl;
        btSolDat << n << ' ' << (double) btColors / (double) EXECS << endl;
    }

    return 0;
}

