
#ifndef HAVE_ATLETA_H
#define HAVE_ATLETA_H

#include "Sexo.h"
#include "numutils.h"
#include <string>
#include <iostream>
using namespace std;

class Atleta {
    public:
        Atleta();
        void inicializar(string nombre, int dorsal, Sexo sexo, int edad, int tiempo);
        void asignaNombre(string nombre);
        void asignaDorsal(uint dorsal);
        void asignaSexo(Sexo sexo);
        void asignaEdad(uint edad);
        void asignaTiempo(uint tiempo);

        string devuelveNombre();
        uint devuelveDorsal();
        Sexo devuelveSexo();
        uint devuelveEdad();
        uint devuelveTiempo();
        const string& devuelveCategoria(); 

		friend ostream& operator<<(ostream& salida, Atleta &aleta);
        
    private:
        string _nombre;
        int _dorsal;
        Sexo _sexo;
        int _edad;
        int _tiempo;
};

bool gui_read_atleta(uint depth, Atleta &atleta);

#endif
