
/**
 * Implementación de un grafo
 * @author Marcos Vives Del Sol
 */

#include <math.h>
#include <stdlib.h>
#include "grafo.h"

Grafo::Grafo(unsigned dim)
{
    this->dim = dim;
    accesos = 0;
    matriz = vector<vector<float> >(dim, vector<float>(dim, INFINITY));
}

float& Grafo::operator()(unsigned origen, unsigned destino)
{
    accesos++;
    return matriz.at(origen).at(destino);
}

unsigned Grafo::size()
{
    return dim;
}

void Grafo::creaGrafoND(float pmin, float pmax)
{
    for (unsigned orig = 0; orig < dim; orig++)
    {
        (*this)(orig, orig) = 0;
        for (unsigned dest = orig + 1; dest < dim; dest++)
        {
            float peso = ((float) rand() / RAND_MAX) * (pmax - pmin) + pmin;
            peso = roundf(peso * 10) / 10;
            (*this)(orig, dest) = peso;
            (*this)(dest, orig) = peso;
        }
    }
}

unsigned Grafo::getAccesos()
{
    return accesos;
}
