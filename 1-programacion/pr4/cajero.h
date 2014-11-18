
#ifndef HAVE_CAJERO_H
#define HAVE_CAJERO_H

#include <string>
using namespace std;

enum OpcionCajero {
    OPCIONCAJERO_SALIR,
    OPCIONCAJERO_INGRESAR,
    OPCIONCAJERO_EXTRAER,
    OPCIONCAJERO_CONSULTAR,
    OPCIONCAJERO_LOGIN,
    OPCIONCAJERO_LOGOUT,
    OPCIONCAJERO_CAMBIAR_PIN,
};
static const OpcionCajero OPCIONCAJERO_ULTIMA = OPCIONCAJERO_CAMBIAR_PIN;

class Cajero
{
    public:
        Cajero();
        Cajero(int, int, int, string);
        bool Ingresar(int, int);
        bool CalcularBilletes(int, int&, int&, int&);
        bool Extraer(int);
        int ConsultarSaldo();
        bool IntroducirTarjeta(string);
        void ExtraerTarjeta();
        OpcionCajero Menu();
        bool GestionarCajero();
        bool DevuelveEstado();
        int DevuelveBilletes10();
        int DevuelveBilletes20();
        int DevuelveBilletes50();
        bool CambiarPin();

    private:
        bool operativo;
        int billetes10;
        int billetes20;
        int billetes50;
        string codigoSecreto;
};

#endif
