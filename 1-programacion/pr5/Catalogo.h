//
//  Catalogo.h
//  VentaOnline
//
//  Created by Xaro Benavent Garcia on 26/03/14.
//  Copyright (c) 2014 Xaro Benavent Garcia. All rights reserved.
//

#ifndef VentaOnline_Catalogo_h
#define VentaOnline_Catalogo_h

#include <string>
#include <fstream>

#include "Articulo.h"

using namespace std;

struct PosicionCatalogo {
    char tipo;
    int posicion;
};

class Catalogo
{
    public:
        Catalogo();
        friend ostream& operator <<(ostream& out, Catalogo a);
        bool anyadirArticulo(Articulo);
        bool borrarArticulo(string);
        void cargarArticulos(ifstream &f);
        void cargarCd(ifstream &f);
        void cargarLibro(ifstream &f);
        void cargarPelicula(ifstream &f);

        int numeroArticulos(char tipo);
        Articulo* dameArticulo(PosicionCatalogo posicion);
    private:
        static const int MAX_ART = 500; //Maximo numero de articulos

        Pelicula peliculas[MAX_ART];
        int numpeliculas;
        
        Cd cds[MAX_ART];
        int numcds;
        
        Libro libros[MAX_ART];
        int numlibros;
        
        PosicionCatalogo buscarArticulo(string titulo); //Funcion auxiliar para localizar un articulo
};

#endif