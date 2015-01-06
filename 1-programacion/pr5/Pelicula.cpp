#include "Pelicula.h"

#include <string>
using namespace std;

string Pelicula::dameDirector()
{
       return director;
}

void Pelicula::cambiarDirector(string director)
{
     this->director = director;
}

int Pelicula::dameDuracion()
{
    return minutos;
}

void Pelicula::cambiarDuracion(int minutos)
{
     this->minutos = minutos;
}
