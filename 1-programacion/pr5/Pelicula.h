
#ifndef PELICULA_H
#define PRACTICA_H

#include <iostream>
#include "Articulo.h"
using namespace std;

class Pelicula : Articulo
{
      public:
             string dameDirector();
             void cambiarDirector(string);
             int dameDuracion();
             void cambiarDuracion(int);
      private:
              string director;
              int minutos;
};

#endif
