/*******************************************************************/
/*                                                                 */
/*                    Rectangulo.CPP                               */
/*          Implementación de la clase Rectángulo.                 */
/*                                                                 */
/*******************************************************************/

#include <iostream>
#include "rectangulo.h"

using namespace std;

/***************** Rectangulo **************************************/
/*                                                                 */
/*  Contructor por defecto de la clase Rectángulo                  */
/*                                                                 */
/*  Descripcion:  Inicializa a cero las variables privadas del     */
/*  rectángulo. Su ponicion(x,y), y su base y altura                */
/*                                                                 */
/*  Parámetros: Ninguno                                            */
/*  Valor devuelto: Ninguno                                        */
/*******************************************************************/
Rectangulo::Rectangulo()
:x(0), y(0), base(0), altura(0)
{}

/***************** Rectangulo **************************************/
/*                                                                 */
/*  Contructor por defecto de la clase Rectángulo                  */
/*                                                                 */
/*  Descripcion:  Inicializa a cero las variables privadas del     */
/*  rectángulo. Su ponicion(x,y), y su base y altura                */
/*                                                                 */
/*  Parámetros: Ninguno                                            */
/*  Valor devuelto: Ninguno                                        */
/*******************************************************************/
Rectangulo::Rectangulo(int x, int y, int base, int altura)
{
    if (!cambiarAncho(base) || !cambiarAlto(altura) || !cambiarPosicion(x, y))
        cerr << "Valores no validos";
}

/***************** leerRectangulo **********************************/
/*                                                                 */
/*  Descripcion:  Lee los parámetros de un rectángulo y comprueba  */
/*  que los valores recogidos son mayores de 0. En caso contrario  */
/*  muestra por pantalla el correspondiente mensaje de error.      */
/*                                                                 */
/*  Parámetros: Ninguno                                            */
/*  Valor devuelto: Ninguno                                        */
/*******************************************************************/
istream& operator>>(istream& input, Rectangulo& r)
{
    char Signo;   // utilizado para guardar ',' durante la lectura.
    int px, py, b, a;

    input >> px >> Signo >> py >> Signo >> b >> Signo >> a;

    //comprobación de que todos los valores deben ser mayor de 0
    if (!r.cambiarAncho(b) || !r.cambiarAlto(a) || !r.cambiarPosicion(px, py))
        cerr << "Todos los parametros deben ser mayores de 0\n";
    return input;
}

/***************** mostrarRectangulo *******************************/
/*                                                                 */
/*  Descripcion:  Muestra por pantalla los parámetros del          */
/*                rectángulo (x, y, base y altura).                 */
/*                                                                 */
/*  Parámetros: Ninguno                                            */
/*  Valor devuelto: Ninguno                                        */
/*******************************************************************/
ostream& operator<<(ostream& out, Rectangulo& r)
{
    out << "\n posicion (x,y); " << r.x << ',' << r.y;
    out << "\n base: " << r.base;
    out << "\n altura: " << r.altura;

    return out;
}

/***************** calcularArea ************************************/
/*                                                                 */
/*  Descripcion:  Devuelve el área del rectángulo (base * altura)  */
/*                                                                 */
/*  Parámetros: Ninguno                                            */
/*                                                                 */
/*  Valor devuelto:                                                */
/*  int, resultado del calculo del área                            */
/*******************************************************************/
int Rectangulo::calcularArea()
{
    return (base * altura);
}
/***************** calcularArea ************************************/
/*                                                                 */
/*  Descripcion:  Devuelve el área del rectángulo (base * altura)  */
/*                                                                 */
/*  Parámetros: Ninguno                                            */
/*                                                                 */
/*  Valor devuelto:                                                */
/*  int, resultado del calculo del área                            */
/*******************************************************************/
int Rectangulo::calcularPerimetro()
{
    return (base + altura) * 2;
}
/***************** estaDentroPunto *********************************/
/*                                                                 */
/*  Descripcion:  Indica si un punto se encuentra en el interior   */
/*                del rectángulo.                                  */
/*                                                                 */
/*  Parámetros:                                                    */
/*  Nombre          Tipo        E/S  Descripcion                   */
/*  ------          ----------  ---  ------------                  */
/*  x1              int         E    posicion x del rectangulo     */
/*  y1              int         E    posicion y del rectangulo     */
/*                                                                 */
/*  Valor devuelto:                                                */
/*  bool, indica si el punto en interior                           */
/*******************************************************************/
bool Rectangulo::estaDentroPunto(int x1, int y1)
{
    bool esta; 

    if((x1 > x) && (x1 < x + base) && (y1 > y) && (y1 < y + altura))
        esta = true;
    else	
        esta = false;

    return esta;   
}

/***************** cambiarAncho ************************************/
/*                                                                 */
/*  Descripcion:  Establece el ancho del rectangulo                */
/*                                                                 */
/*  Parámetros:                                                    */
/*  Nombre          Tipo        E/S  Descripcion                   */
/*  ------          ----------  ---  ------------                  */
/*  anchoNuevo      int         E    ancho nuevo, positivo         */
/*                                                                 */
/*  Valor devuelto:                                                */
/*  void                                                           */
/*******************************************************************/
bool Rectangulo::cambiarAncho(int anchoNuevo)
{
    bool ok = anchoNuevo > 0;
    if (ok)
        base = anchoNuevo;
        
    return ok;
}

/***************** cambiarAlto *************************************/
/*                                                                 */
/*  Descripcion:  Establece la altura del rectangulo               */
/*                                                                 */
/*  Parámetros:                                                    */
/*  Nombre          Tipo        E/S  Descripcion                   */
/*  ------          ----------  ---  ------------                  */
/*  alturaNueva     int         E    ancho nuevo, positivo         */
/*                                                                 */
/*  Valor devuelto:                                                */
/*  void                                                           */
/*******************************************************************/
bool Rectangulo::cambiarAlto(int alturaNueva)
{
    bool ok = alturaNueva > 0;
    if (ok)
        altura = alturaNueva;
        
    return ok;
}
/***************** cambiarPosicion *********************************/
/*                                                                 */
/*  Descripcion:  Establece la posicion del rectangulo             */
/*                                                                 */
/*  Parámetros:                                                    */
/*  Nombre          Tipo        E/S  Descripcion                   */
/*  ------          ----------  ---  ------------                  */
/*  nuevaX          int         E    coordenada X nueva            */
/*  nuevaY          int         E    coordenada Y nueva            */
/*                                                                 */
/*  Valor devuelto:                                                */
/*  bool, las coordenadas son validas (mayores o iguales a cero)   */
/*******************************************************************/
bool Rectangulo::cambiarPosicion(int nuevaX, int nuevaY)
{
    bool ok = (nuevaX > 0 && nuevaY > 0);

    if (ok)
    {
        x = nuevaX;
        y = nuevaY;
    }

    return ok;
}

/***************** desplazarRectangulo *****************************/
/*                                                                 */
/*  Descripcion:  Desplaza el rectangulo                           */
/*                                                                 */
/*  Parámetros:                                                    */
/*  Nombre          Tipo        E/S  Descripcion                   */
/*  ------          ----------  ---  ------------                  */
/*  desp_x          int         E    desplazamiento en X           */
/*  desp_y          int         E    desplazamiento en Y           */
/*  Valor devuelto:                                                */
/*  bool, las cordenadas resultantes son positivas                 */
/*******************************************************************/
bool Rectangulo::desplazarRectangulo(int desp_x, int desp_y)
{
    return cambiarPosicion(x + desp_x, y + desp_y);   
}

/***************** estaDentroCirc **********************************/
/*                                                                 */
/*  Descripcion:  Comprueba si el circulo esta contenido en el     */
/*                rectangulo                                       */
/*                                                                 */
/*  Parámetros:                                                    */
/*  Nombre          Tipo        E/S  Descripcion                   */
/*  ------          ----------  ---  ------------                  */
/*  circ            Circulo     E    el circulo a comprobar        */
/*  Valor devuelto:                                                */
/*  bool                                                           */
/*******************************************************************/
bool Rectangulo::estaDentroCirc(Circulo circ)
{
	int r = circ.obtenerRadio();
	int cx = circ.obtenerCentroX();
	int cy = circ.obtenerCentroY();

	// Aparentemente esto no funciona bien, porque estaDentroPunto devuelve false si el punto esta sobre el borde del rectangulo
    // return estaDentroPunto(cx - r, cy - r) && estaDentroPunto(cx + r, cy + r);
	return x >= cx - r
		&& y >= cy - r
		&& x + base <= cx + r
		&& y + altura <= cy + r;
}
