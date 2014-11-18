
#include "Cd.h"
#include <string>
using namespace std;

string Cd::dameAutor()
{
       return autor;
}

void Cd::cambiarAutor(string autor)
{
     this->autor = autor;
}

int Cd::dameAnyo()
{
    return anyo;
}

void Cd::cambiarAnyo(int anyo)
{
     this->anyo = anyo;
}
