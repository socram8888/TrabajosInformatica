/*******************************************************************/
/*                                                                 */
/*                    Catalogo.cpp                                 */
/*                                                                 */
/*          Implementacion de la clase Catalogo                    */
/*                                                                 */
/*******************************************************************/

#include <string>
#include <iostream>

#include "Catalogo.h"
#include "Articulo.h"

using namespace std;

/***************** Catalogo   **************************************/
/*                                                                 */
/*  Contructor por defecto de la clase Catalogo                    */
/*                                                                 */
/*  Descripcion:  Inicializa a cero el numero de articulos         */
/*  del catalogo                                                   */
/*                                                                 */
/*  Parametros: Ninguno                                            */
/*  Valor devuelto: Ninguno                                        */
/*******************************************************************/
Catalogo::Catalogo()
{
    numlibros = 0;
    numcds = 0;
    numpeliculas = 0;
}

/***************** operator<< **************************************/
/*                                                                 */
/*  Descripcion:  Sobrecarga del operador "<<" para mostrar los    */
/*  articulos del Catalogo por pantalla                            */
/*  Par·metros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  out          ostream    E/S  stream estandar de salida         */
/*  a            Catalogo   E    objeto Catalogo   a mostrar       */
/*                                                                 */
/*  Valor devuelto: Referencia a objeto tipo ostream               */
/*******************************************************************/
ostream& operator <<(ostream& out, Catalogo a)
{
    
    int i;
    out << "Catalogo de articulos de 'RoboCom'" << endl;
    out << "-----------------------------------" << endl << endl;
    out << "# Libros:" << endl;
    for (i=0;i<a.numlibros;i++)
    {
        out << a.numlibros[i];
        out << endl;
    }
    
    out << "# CDs:" << endl;
    for (i=0;i<a.numcds;i++)
    {
        out << a.numcds [i];
        out << endl;
    }
    
    out << "# Peliculas:" << endl;
    for (i=0;i<a.numpeliculas;i++)
    {
        out << a.numpeliculas [i];
        out << endl;
    }
    
    out << endl;
    
    return out;
}

/***************** Catalogo    *************************************/
/*                                                                 */
/*  Descripcion:  anyade un articulo al Catalogo                   */
/*                                                                 */
/*  Parametros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  a            Articulo   E    Articulo a anyadir al catalogo    */
/*                                                                 */
/*  Valor devuelto: valor logico indicando si la operacion se ha   */
/*                   realizado correctamente                       */
/*******************************************************************/
bool Catalogo::anyadirArticulo(Articulo a)
{
    bool ok = false;
    PosicionCatalogo pos;
    string t;
    
    t = a.dameTitulo();
    pos = buscarArticulo(t);
    if (pos.posicion < 0)
    {
        switch (a.dameTipo())
        {
            case 'p':
                if (numpeliculas < MAX_ART)
                {
                    peliculas[numpeliculas] = a;
                    numpeliculas++;
                    ok = true;
                }
                break;
            case 'l':
                if (numlibros < MAX_ART)
                {
                    libros[numlibros] = a;
                    numlibros++;
                    ok = true;
                }
                break;
            case 'c':
                if (numcds < MAX_ART)
                {
                    cds[numcds] = a;
                    numcds++;
                    ok = true;
                }
                break;
        }
    }

    return ok;
}

/***************** Catalogo    *************************************/
/*                                                                 */
/*  Descripcion:  borra  un articulo al Catalogo                   */
/*                                                                 */
/*  Parametros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  t            string     E    El titulo del articulo a borrar   */
/*                                                                 */
/*  Valor devuelto: valor logico indicando si la operacion se ha   */
/*                   realizado correctamente                       */
/*******************************************************************/
bool Catalogo::borrarArticulo(string t)
{
    int i = 0;
    bool ok = false;
    PosicionCatalogo pos;
    
    pos = buscarArticulo(t);
    if ( pos.tipo == 'p' && pos.posicion >= 0 )
    {
        for (i = pos.posicion + 1; i < numpeliculas; i++)
            peliculas[i - 1] = peliculas[i];
        numpeliculas--;
        ok = true;
    }
    
    if (pos.tipo == 'l' && pos.posicion >= 0)
    {
        for (i = pos.posicion + 1; i < numlibros; i++)
            libros[i - 1] = libros[i];
        numlibros--;
        ok = true;
    }
    
    if (pos.tipo == 'c' && pos.posicion >= 0)
    {
        for (i = pos.posicion + 1; i < numcds; i++)
            cds[i - 1] = cds[i];
        numcds--;
        ok = true;
    }

    return ok;
}

/***************** Catalogo    *************************************/
/*                                                                 */
/*  Descripcion:  busca un articulo en el Catalogo                 */
/*                                                                 */
/*  Parametros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  t            string     E    El titulo del articulo a buscar   */
/*                                                                 */
/*  Valor devuelto: entero indicando la posicion del vector donde  */
/*                  se encuentra almacenado el articulo, o -1      */
 /*                 si no se encuentra al catalogo                 */
/*******************************************************************/
PosicionCatalogo Catalogo::buscarArticulo(string t)
{
    int i;
    PosicionCatalogo pos;

    pos.tipo = ' ';
    pos.posicion = -1;

    i = 0;
    while (pos.posicion < 0 && i < numpeliculas)
    {
        if (peliculas[i].dameTitulo() == t)
        {
            encontrado = true;
            pos.posicion = i;
            pos.tipo = 'p';
        }
        i++;
    }
            
    i = 0;
    while (pos.posicion < 0 && i < numlibros)
    {
        if (libros[i].dameTitulo() == t)
        {
            encontrado = true;
            pos.posicion = i;
            pos.tipo = 'l';
        }
        i++;
    }

    i = 0;
    while (pos.posicion < 0 && i < numcds)
    {
        if (cds[i].dameTitulo() == t)
        {
            encontrado = true;
            pos.posicion = i;
            pos.tipo = 'c';
        }
        i++;
    }

    return pos;
}

void cargarArticulos(ifstream &f)
{
    string linea;

    while (f.good())
    {
        getline(f, linea);
        if (linea == "c")
            cargarCd(f);
        else if (linea == "p")
            cargarPelicula(f);
        else if (linea == "l")
            cargarLibro(f);
    }
}

void cargarCd(ifstream &f)
{
    string linea, titulo;
    Cd cd;

    getline(f, titulo);

    getline(f, linea);
    cd.cambiarAutor(linea);

    getline(f, linea);
    cd.cambiarAnyo(atoi(linea.c_str()));

    getline(f, linea);
    cd.fijarDatos(titulo, 'c', atof(linea.c_str()));

    anyadirArticulo(cd);
}
        
void cargarPelicula(ifstream &f);
{
    string linea, titulo;
    Pelicula pelicula;

    getline(f, titulo);

    getline(f, linea);
    pelicula.cambiarAutor(linea);

    getline(f, linea);
    pelicula.cambiarDuracion(atoi(linea.c_str()));
    
    getline(f, linea);
    pelicula.fijarDatos(titulo, 'p', atof(linea.c_str()));

    anyadirArticulo(pelicula);
}

        
void cargarLibro(ifstream &f);
{
    string linea, titulo;
    Libro libro;

    getline(f, titulo);

    getline(f, linea);
    libro.cambiarAutor(linea);

    getline(f, linea);
    libro.cambiarEditorial(linea);

    getline(f, linea);
    libro.fijarDatos(titulo, 'l', atof(linea.c_str()));

    anyadirArticulo(libro);

}