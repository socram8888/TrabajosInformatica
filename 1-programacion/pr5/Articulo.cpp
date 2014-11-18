/*******************************************************************/
/*                                                                 */
/*                    Articulo.cpp                                 */
/*                                                                 */
/*          Implementacion de la clase Articulo                    */
/*                                                                 */
/*******************************************************************/
#include "Articulo.h"

#include <string>
#include <iostream>

using namespace std;

/***************** Articulo   **************************************/
/*                                                                 */
/*  Contructor por defecto de la clase Articulo                    */
/*                                                                 */
/*  Descripcion:  Inicializa a articulos tipo pelicula sin ningun  */
/*  tipo con precio 0.0                                            */
/*                                                                 */
/*  Parametros: Ninguno                                            */
/*  Valor devuelto: Ninguno                                        */
/*******************************************************************/
Articulo::Articulo()
:tipo('p'),titulo("ninguno"),precio(0.0)
{}

/***************** Articulo    *************************************/
/*                                                                 */
/*  Descripcion:  fija los atributos de un articulo                */
/*                                                                 */
/*  Parametros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  tit           string     E   El titulo del articulo            */
/*  tip           char       E   (p,l,c) (pelicula, libro o cd)    */
/*  pre           float      E   El precio del articulo            */
/*                                                                 */
/*  Valor devuelto: ninguno                                        */
/*******************************************************************/
void Articulo::fijarDatos(string tit,char tip,float pre)
{
	titulo = tit;
	tipo = tip;
	precio = pre;
}

/***************** operator<< **************************************/
/*                                                                 */
/*  Descripcion:  Sobrecarga del operador "<<" para mostrar l      */
/*  un articulo por pantalla                                       */
/*  Par·metros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  out          ostream    E/S  stream estandar de salida         */
/*  a            Articulo   E    objeto Articulo   a mostrar       */
/*                                                                 */
/*  Valor devuelto: Referencia a objeto tipo ostream               */
/*******************************************************************/
ostream& operator <<(ostream& out, Articulo a)
{
    out << a.titulo << " (" << a.tipo << ") " << " = " << a.precio << "euros";
    return out;
}

/***************** Articulo    *************************************/
/*                                                                 */
/*  Descripcion:  devuelve el titulo del articulo                  */
/*                                                                 */
/*  Parametros: ninguno                                            */
/*                                                                 */
/*  Valor devuelto: string con el titulo del articulo              */
/*******************************************************************/
string Articulo::dameTitulo()
{
    return titulo;
}

/***************** Articulo    *************************************/
/*                                                                 */
/*  Descripcion:  devuelve el tipo de articulo ('p','l','c')       */
/*                                                                 */
/*  Parametros: ninguno                                            */
/*                                                                 */
/*  Valor devuelto: char con el tipo del articulo                  */
/*******************************************************************/
char Articulo::dameTipo()
{
    return tipo;
}

/***************** Articulo    *************************************/
/*                                                                 */
/*  Descripcion:  devuelve el precio del articulo                  */
/*                                                                 */
/*  Parametros: ninguno                                            */
/*                                                                 */
/*  Valor devuelto: float con el precio del articulo               */
/*******************************************************************/
float Articulo::damePrecio()
{
    return precio;
}

/***************** Articulo    *************************************/
/*                                                                 */
/*  Descripcion:  fija el precio de un articulo                    */
/*                                                                 */
/*  Parametros:                                                    */
/*  Nombre       Tipo       E/S  Descripcion                       */
/*  ------       ---------  ---  ------------                      */
/*  pre           float      E   El precio del articulo            */
/*                                                                 */
/*  Valor devuelto: ninguno                                        */
/*******************************************************************/

void Articulo::cambiarPrecio(float pre)
{
    precio = pre;
}

