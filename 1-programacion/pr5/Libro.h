
#ifndef LIBRO_H
#define LIBRO_H

#include <iostream>
#include "Articulo.h"
using namespace std;

class Libro : Articulo
{
      public:
             void cambiarAutor(string);
             void cambiarEditorial(string);
             string dameAutor();
             string dameEditorial();
      private:
              string autor;
              string editorial;
};

#endif
