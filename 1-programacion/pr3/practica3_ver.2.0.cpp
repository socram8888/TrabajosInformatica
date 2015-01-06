/*******************************************************************/
/* Asignatura: Programacion                                        */
/* Curso 2013-2014                                                 */
/* Practica 3                                                      */
/* Programación Orientada a Objetos                                */
/*                                                                 */
/* AUTOR: Jose Garcia                                              */
/* FECHA: 18 de Marzo de 2014                                 	   */
/*                                                                 */
/* PROPOSITO: Practicar la utilización de clases                   */
/*                                                                 */
/*******************************************************************/

#include <cstdlib>
#include <iostream>
#include "rectangulo.h"
#include "circulo.h"

using namespace std;

int main()
{
    Rectangulo r;
    int opcion;
    char Signo; // utilizado para guardar ',' durante la lectura del punto
    int puntoX = 0, puntoY = 0;   // variables para almacenar una posicion
    int x, y;
	Circulo c;

    
    // cout << r.base;  -->> Da error por que es "private"
    
    
    /*

    if (r.estaDentroPunto(x,y))
        cout << "El punto esta dentro del rectangulo." << endl;
    else
        cout << "El punto esta fuera de las dimensiones del rectangulo." << endl;
    
    system("PAUSE");
    return 0;
    */
    do
    {
        cout << "[1] Leer un rectangulo\n";
        cout << "[2] Leer un punto\n";
        cout << "[3] Mover Rectangulo\n";
        cout << "[4] Modificar base rectangulo\n";
        cout << "[5] Modifica altura rectangulo\n";
        cout << "[6] Ver si el rectangulo incluye al punto\n";
        cout << "[7] Mostrar perimetro y area rectangulo\n";
        cout << "[8] Mostrar parametros rectangulo\n";
		cout << "[9] Leer un circulo\n";
		cout << "[10] Mostrar parametros circulo\n";
		cout << "[11] Cambiar radio\n";
		cout << "[12] Desplazar circulo\n";
		cout << "[13] Comprobar si el rectangulo contiene al circulo\n";
        cout << "[0] Salir\n";
    
        cout << "\nOpcion: ";
        cin >> opcion;
        
        switch (opcion)
        {
            case 1:
                cout << "Introduce los valores del rectangulo (x,y,base,altura): " ;
                cin >> r;
                break;
            case 2:
                cout << "Introduce un punto (x,y): ";
                cin >> puntoX >> Signo >> puntoY;
                break;
            case 3:
                cout << "Introduce un punto (x,y): ";
                cin >> x >> Signo >> y;
                if (!r.desplazarRectangulo(x, y))
                    cerr << "Desplazamiento no valido";
                break;
            case 4:
                cout << "Introduce la base: ";
                cin >> x;
                if (!r.cambiarAncho(x))
                    cerr << "Ancho no valido";
                break;
            case 5:
                cout << "Introduce la altura: ";
                cin >> x;
                if (!r.cambiarAlto(x))
                    cerr << "Altura no valida";
                break;
            case 6:
                if (r.estaDentroPunto(puntoX, puntoY))
                    cout << "El punto esta dentro del rectangulo." << endl;
                else
                    cout << "El punto esta fuera de las dimensiones del rectangulo." << endl;
                break;
            case 7:
                cout << "El area del rectangulo es: " << r.calcularArea() << endl;
                cout << "El perimetro del rectangulo es: " << r.calcularPerimetro() << endl;
                break;
            case 8:
                cout << "Parametros del rectangulo:\n";
                cout << r << "\n";
                break;
			case 9:
				cout << "Introduce un circulo (x,y,r):\n";
				cin >> c;
				break;
			case 10:
                cout << "Parametros del circulo:\n";
				cout << c;
				break;
			case 11:
				cout << "Introduce el radio nuevo: ";
				cin >> x;
				if (!c.cambiarRadio(x))
					cerr << "Radio no valido\n";
				break;
			case 12:
                cout << "Introduce un punto (x,y): ";
                cin >> x >> Signo >> y;
                if (!c.desplazarCirculo(x, y))
                    cerr << "Desplazamiento no valido";
                break;
			case 13:
				cout << "El circulo ";
				if (!r.estaDentroCirc(c))
					cout << "NO ";
				cout << "esta dentro del rectangulo dado\n";
        }
        cout << "\n";
    } while (opcion != 0);
    
    return 0;
}

