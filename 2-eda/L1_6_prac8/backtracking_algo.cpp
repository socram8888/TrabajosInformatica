
/**
 * Implementación de un algoritmo con backtracking para coloreado de grafos
 * @author Marcos Vives Del Sol
 */

#include <assert.h>
#include "backtracking_algo.h"
using namespace std;

/**
 * Función recursiva para colorear un grafo mediante backtracking.
 * @param g Grafo
 * @param colors Colores
 * @param node Nodo actual
 * @param colorsUsed Cantidad de colores usados hasta ahora
 * @param minColors Mínima cantidad de colores que se han empleado en
 *                  iteraciones anteriores
 * @param used Vector de booleanos de trabajo, debe tener un tamaño de n^2
 * @return True si la llamada ha conseguido mejorar el cálculo anterior
 */
bool recurse(Grafo& g, vector<unsigned>& colors, unsigned node, unsigned colorsUsed, unsigned& minColors, vector<bool>& used)
{
    assert(colors.size() == g.size());
    assert(node <= g.size());
    assert(colorsUsed <= g.size());
    assert(minColors <= g.size());
    assert(used.size() == g.size() * g.size());

    if (node == g.size())
    {
        if (colorsUsed < minColors)
        {
            minColors = colorsUsed;
            return true;
        }
        return false;
    }

    unsigned usedbase = g.size() * node; 
    unsigned bestColor = colors[node];

    fill(used.begin() + usedbase, used.begin() + usedbase + g.size(), false);
    for (unsigned i = 0; i < node; i++)
        if (g(node, i))
            used[usedbase + colors[i]] = true;

    bool improved = false;
    for (unsigned color = 0; color < minColors; color++)
        if (!used[usedbase + color])
        {
            colors[node] = color;
            if (recurse(g, colors, node + 1, max(colorsUsed, color), minColors, used))
            {
                bestColor = color;
                improved = true;
            }
        }

    colors[node] = bestColor;
    return improved;
}

/**
 * Colorea un grafo de modo que no haya dos nodos conectados con el mismo
 * color.
 * @param g Grafo
 * @param c Colores
 * @return Color más alto requerido
*/
unsigned colorear_backtracking(Grafo& g, vector<unsigned>& c)
{
    c.resize(g.size());
    for (unsigned i = 0; i < g.size(); i++)
        c[i] = i;

    vector<bool> used(g.size() * g.size());
    unsigned minColors = g.size();

    recurse(g, c, 0, 0, minColors, used);

    return minColors;
}
