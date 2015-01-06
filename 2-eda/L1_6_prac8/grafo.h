
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
        vector<bool>::reference operator()(unsigned f, unsigned c);

        /**
         * @return Número de nodos del grafo
         */
        unsigned size() const;

        /**
         * Crea un grafo aleatorio, con una probabilidad del 50% de que haya un
         * arco o no entre dos nodos.
         */
        void creaGrafoND50();

        /**
         * @return Número de accesos al grafo
         */
        unsigned getAccesos() const;

        void incAccesos(unsigned);
    private:
        vector<vector<bool> > matriz;
        unsigned dim;
        unsigned accesos;
};

#endif
