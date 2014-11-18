
#ifndef CD_H
#define CD_H

#include <iostream>
#include "Articulo.h"
using namespace std;

class Cd : Articulo
{
      public:
             void cambiarAutor(string);
             void cambiarAnyo(int);
             string dameAutor();
             int dameAnyo();
      private:
              string autor;
              int anyo;
};

#endif
