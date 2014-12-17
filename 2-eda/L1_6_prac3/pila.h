
/**
 * Definición de la pila
 * @author Marcos Vives Del Sol
 */

#ifndef HAVE_PILA_H
#define HAVE_PILA_H

class Pila
{
    public:
        /**
         * Construye una nueva pila con un tamaño máximo.
         * @param size Tamaño máximo
         */
        Pila(unsigned int size);

        /**
         * Constructor de copia: clona el contenido y estado de la pila dada.
         * @param pila Pila original.
         */
        Pila(const Pila &pila);

        /**
         * Destructor
         */
        ~Pila();

        /**
         * Copia el contenido de otra pila a este objeto.
         * @param pila Pila original.
         */
        const Pila& operator=(const Pila &pila);

        /**
         * Introduce un entero en la pila.
         * @param dato El entero
         * @throws ErrorPilaLlena La pila ha llegado al límite de la capacidad.
         */
        void apilar(int dato);

        /**
         * Extrae el entero de la cima de la pila.
         * @return El entero de la cima
         * @throws ErrorPilaVacia La pila no contiene nada
         */
        int desapilar();

        /**
         * Devuelve el entero de la cima de la pila.
         * @return El entero de la cima
         * @throws ErrorPilaVacia La pila no contiene nada
         */
        int cima();

        /**
         * @return La pila está vacía
         */
        bool vacia();

        /**
         * Devuelve el número de accesos realizados a los métodos apilar,
         * desapilar y cima
         * @return Número de accesos
         */
        unsigned int getAccesos();

        /**
         * Reinicia a cero el contador de accesos.
         */
        void resetAccesos();

        /**
         * Muestra la pila por cout.
         */
        void mostrar();

    private:
        int * buffer;
        unsigned int size;
        unsigned int count;
        unsigned int accesses;
};

#endif
