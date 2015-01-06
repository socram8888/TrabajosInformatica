/*******************************************************************/
/*                                                                 */
/*                    Articulo.h                                   */
/*                                                                 */
/*          Declaracion de la clase Articulo                       */
/*                                                                 */
/*******************************************************************/
#ifndef VentaOnline_Articulo_h
#define VentaOnline_Articulo_h

#include <string>

using namespace std;

class Articulo
{
public:
    Articulo();
    friend ostream& operator <<(ostream& out, Articulo a);
    void fijarDatos(string,char,float);
    string dameTitulo();
    char dameTipo();
    float damePrecio();
    void cambiarPrecio(float);
    
private:
    char tipo; //'p'=Pelicula, 'l'=Libro, 'c'=CD
    string titulo;
	float precio; 
};

#endif
