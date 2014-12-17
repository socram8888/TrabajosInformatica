
/**
 * Interfaz del algoritmo Dijkstra
 * @author Marcos Vives Del Sol
 */

#ifndef HAVE_DIJKSTRA_H
#define HAVE_DIJKSTRA_H

#include <vector>
#include "grafo.h"
using namespace std;

/**
 * Ejecuta el algoritmo de distancia mínima de Dijkstra
 * @param grafo El grafo
 * @param inicio Nodo inicial
 * @param pvecino Peso del arco con el nodo anterior
 * @param vecino Nodo anterior
 */
void dijkstra(Grafo& grafo, unsigned inicio, vector<float>& pvecino, vector<unsigned>& vecino);

#endif
