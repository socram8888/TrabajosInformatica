#include <cstdlib>
#include <iostream>
#include "cajero.h"

using namespace std;

int main()
{
    Cajero c(0, 0, 0, "1234");
	
    //Para poder poner acentos, e?es, etc.
	setlocale (LC_ALL, "spanish");
	
	if(!c.IntroducirTarjeta("2000"))
	    //Debe de mostrar esto al no coincidir el n?mero secreto con 1234
    	cout << "Operaci?n c.IntroducirTarjeta(\"2000\") no realizada" << endl;
    	
    //Pongo el cajero a operativo
    if(c.IntroducirTarjeta("1234"))
    	//Debe de mostrar esto
    	cout << "Cajero operativo" << endl; 
    
    //Ingreso 8 billetes de 10 euros
    c.Ingresar (8, 10);
    //Ingreso 7 billetes de 20 euros
    c.Ingresar (7, 20);
    //Ingreso 7 billetes de 20 euros
    c.Ingresar (10, 50);
    
    //Si todo ha ido bien deber? mostrar 720 euros
    cout << "Saldo: " << c.ConsultarSaldo () << " euros" << endl;
    
    c.Extraer (160);
    //Si todo ha ido bien deber? mostrar:
   	//3 billetes de 50 euros retirados
    //0 billetes de 20 euros retirados
	//1 billetes de 10 euros retirados

    //Si todo ha ido bien deber? mostrar 560 euros
	cout << "Saldo: " << c.ConsultarSaldo() << " euros" << endl;
					
	if (!c.Extraer (1000) )
	    //Debe de mostrar esto al estar no tener suficiente saldo
    	cout << "Operaci?n c.Extraer(1000) no realizada" << endl;
    
    //Pongo el cajero a no operativo
    c.ExtraerTarjeta ();
    
    if (!c.Ingresar (1, 10) )
        //Debe de mostrar esto al estar el cajero no operativo
    	cout << "Operaci?n c.Ingresar(1,10) no realizada" << endl;
    
    if (!c.Extraer (160) )
        //Debe de mostrar esto al estar el cajero no operativo
    	cout << "Operaci?n c.Extraer(160) no realizada" << endl;
        c.GestionarCajero();
    system ("pause");
    
    return 0;
}


