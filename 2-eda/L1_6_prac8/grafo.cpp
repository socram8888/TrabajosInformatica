
/**
 * Implementación de un grafo
 * @author Marcos Vives Del Sol
 */

#include <stdlib.h>
#include "grafo.h"

Grafo::Grafo(unsigned dim)
{
    this->dim = dim;
    accesos = 0;
    matriz = vector<vector<bool> >(dim, vector<bool>(dim, false));
}

vector<bool>::reference Grafo::operator()(unsigned origen, unsigned destino)
{
    accesos++;
    return matriz.at(origen).at(destino);
}

unsigned Grafo::size() const
{
    return dim;
}

void Grafo::creaGrafoND50()
{
    for (unsigned orig = 0; orig < dim; orig++)
    {
        (*this)(orig, orig) = true;
        for (unsigned dest = orig + 1; dest < dim; dest++)
        {
            bool p = rand() & 1;
            (*this)(orig, dest) = p;
            (*this)(dest, orig) = p;
        }
    }
}

unsigned Grafo::getAccesos() const
{
    return accesos;
}

void Grafo::incAccesos(unsigned x){ this->accesos += x; }