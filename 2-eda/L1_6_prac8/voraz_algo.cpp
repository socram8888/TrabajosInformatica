
/**
 * Implementación de un algoritmo voraz para coloreado de grafos
 * @author Marcos Vives Del Sol
 */

#include "voraz_algo.h"
using namespace std;

/**
 * Colorea un grafo de modo que no haya dos nodos conectados con el mismo
 * color.
 * @param g Grafo
 * @param c Colores
 * @return Color más alto requerido
*/
unsigned colorear_voraz(Grafo& g, vector<unsigned>& c)
{
    c.resize(g.size());
    vector<bool> b(g.size());
    unsigned highest = 0;

    for (unsigned i = 0; i < g.size(); i++)
    {
        fill(b.begin(), b.begin() + i, false);

        for (unsigned j = 0; j < i; j++)
            if (g(i, j))
                b[c[j]] = true;

        unsigned ca = 0;
        while (b[ca])
            ca++;

        c[i] = ca;
        if (ca > highest)
            highest = ca;
    }

    return highest;
}

/*

mejor: x*(x-1)/2 w l
peor: x*(x*(x+3)-4)/6 w l, 

unsigned colorear_voraz(Grafo& g, vector<unsigned>& c)
{
    if (c.size() != g.size())
        c = vector<unsigned>(g.size());

    unsigned highest = 0;

    for (unsigned i = 0; i < g.size(); i++)
    {
        unsigned ca = 0;

        unsigned j = 0;
        while (j < i && ca < i)
        {
            if (g(i, j) && c[j] == ca)
            {
                ca++;
                j = 0;
            }
            else
                j++;
        }

        c[i] = ca;
        if (ca > highest)
            highest = ca;
    }

    return highest;
}
*/
