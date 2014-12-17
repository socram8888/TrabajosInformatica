
#ifndef HAVE_GRAFO_H
#define HAVE_GRAFO_H

#include <vector>
using namespace std;

class Grafo
{
    public:
        /**
         * Crea un grafo nuevo
         * @param dim Número máximo de nodos
         */
        Grafo(unsigned);

        /**
         * Accede a un arco
         * @param origen Nodo de origen
         * @param destino Nodo de destino
         * @return Valor por referencia del peso del arco, o infinito si no existe
         */
        float & operator()(unsigned f, unsigned c);

        /**
         * @return Número de nodos del grafo
         */
        unsigned size();

        /**
         * Crea un grafo no dirigido completamente conexo con pesos aleatorios
         * @param pmin Peso mínimo de cada arco
         * @param pmax Peso máximo de cada arco
         */
        void creaGrafoND(float pmin, float pmax);

        /**
         * @return Número de accesos al grafo
         */
        unsigned getAccesos();

    private:
        vector<vector<float> > matriz;
        unsigned dim;
        unsigned accesos;
};

#endif
