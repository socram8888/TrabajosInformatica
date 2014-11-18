#include "Libro.h"

#include <string>
using namespace std;

void Libro::cambiarAutor(string autor)
{
     this->autor = autor;     
}
void Libro::cambiarEditorial(string editorial)
{
     this->editorial = editorial;
}
string Libro::dameAutor()
{
       return autor;
}
string Libro::dameEditorial()
{
       return editorial;       
}
