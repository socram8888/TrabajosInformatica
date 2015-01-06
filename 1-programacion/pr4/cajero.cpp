
#include <iostream>
#include "cajero.h"
#include "getch.h"

using namespace std;

string LeerPin()
{
    string pin = "";
    int chr;

    do {
        chr = getch();
        if (chr >= '0' && chr <= '9')
        {
            pin += (char) chr;
            cout << '*';
        }
        else if (chr == 8 && pin.length() > 0)
        {
            pin = pin.substr(0, pin.length() - 1);
            cout << "\x08 \x08";
        }
    }
    while (chr != 13);

    return pin;
}

void Pausa()
{
    cout << "*** Pulsa una tecla para continuar ***\n";
    getch();
}

Cajero::Cajero()
{
    operativo = false;
    billetes10 = 0;
    billetes20 = 0;
    billetes50 = 0;
    codigoSecreto = "1234";
}

Cajero::Cajero(int billetes10, int billetes20, int billetes50, string codigo)
{
    operativo = false;
    this->billetes10 = billetes10;
    this->billetes20 = billetes20;
    this->billetes50 = billetes50;
    codigoSecreto = codigo;
}

bool Cajero::Ingresar(int cantidad, int valor)
{   
    bool ok = true;
    
    if (!operativo)
        ok = false;
        
    if (ok && cantidad < 0)
        ok = false;
    
    if (ok)
    {
        switch (valor)
        {
            case 10:
                billetes10 += cantidad;
                break;
            case 20:
                billetes20 += cantidad;
                break;
            case 50:
                billetes50 += cantidad;
                break;
            default:
                ok = false;
        }
    }

    return ok;
}

bool Cajero::CalcularBilletes(int dinero, int& n10, int& n20, int& n50)
{
    if (dinero > 0)
    {
        n50 = min(dinero / 50, billetes50);
        dinero -= n50 * 50;
    
        n20 = min(dinero / 20, billetes20);
        dinero -= n20 * 20;
    
        n10 = min(dinero / 10, billetes10);
        dinero -= n10 * 10;
    }
    return dinero == 0;
}

bool Cajero::Extraer(int dinero)
{
    bool ok;
    int n10;
    int n20;
    int n50;

    ok = operativo;
    
    if (ok)
        ok = CalcularBilletes(dinero, n10, n20, n50);

    if (ok)
    {
        cout << "Se ha extraido "<< dinero << " euros:\n";
        cout << " - " << n10 << " billetes de 10\n";
        cout << " - " << n20 << " billetes de 20\n";
        cout << " - " << n50 << " billetes de 50\n";
        
        billetes10 -= n10;
        billetes20 -= n20;
        billetes50 -= n50;
    }
    else
        cerr << "No se ha podido sacar la cantidad solicitada\n";
    
    return ok;
}

int Cajero::ConsultarSaldo()
{
    return 10 * billetes10 +
        20 * billetes20 +
        50 * billetes50;
}

bool Cajero::IntroducirTarjeta(string codigo)
{
    operativo = codigoSecreto == codigo;
    return operativo;
}

void Cajero::ExtraerTarjeta()
{
    operativo = false;    
}

bool Cajero::CambiarPin()
{
    bool ok = operativo;
    string nuevoPin;

    if (ok)
    {
        cout << "Introduce el PIN nuevo: ";
        nuevoPin = LeerPin();
        cout << "\n";
        
        ok = nuevoPin.length() > 0;
    }

    if (ok)
        codigoSecreto = nuevoPin;

    return ok;
}

OpcionCajero Cajero::Menu()
{
    int chr;

    cout << "[" << OPCIONCAJERO_INGRESAR << "] Ingresar\n";
    cout << "[" << OPCIONCAJERO_EXTRAER << "] Extraer\n";
    cout << "[" << OPCIONCAJERO_CONSULTAR << "] Consultar\n";
    cout << "[" << OPCIONCAJERO_LOGIN << "] Introducir tarjeta\n";
    cout << "[" << OPCIONCAJERO_LOGOUT << "] Extraer tarjeta\n";
    cout << "[" << OPCIONCAJERO_CAMBIAR_PIN << "] Cambiar PIN\n";
    cout << "[" << OPCIONCAJERO_SALIR << "] Salir\n";

    do
    {
        chr = getch();
    }
    while (chr < '0' || chr > '0' + OPCIONCAJERO_ULTIMA);

    return (OpcionCajero) (chr - '0');
} 

bool Cajero::GestionarCajero()
{
    bool ok; 
    int cantidad;
    int valor;
    string codigo;
    OpcionCajero opcion;

    do {
        opcion = Menu();
        ok = true;

        switch (opcion)
        {
            case OPCIONCAJERO_INGRESAR:
                cout<< "Cantidad de billetes: ";
                cin >> cantidad;
                cout<< "Valor de billetes: ";
                cin >> valor;
    
                ok = Ingresar(cantidad, valor);
                break;
    
            case OPCIONCAJERO_EXTRAER:
                cout << "Ingrese cantidad: ";
                cin >> valor;
                
                ok = Extraer(valor);
                break;
    
            case OPCIONCAJERO_CONSULTAR:
                cout << "El cajero contiene " << ConsultarSaldo() << " euros\n";
                break;
    
            case OPCIONCAJERO_LOGIN:
                cout << "Ingrese PIN: ";
                codigo = LeerPin();
                ok = IntroducirTarjeta(codigo);
                break;
    
            case OPCIONCAJERO_LOGOUT:
                ExtraerTarjeta();
                break;

            case OPCIONCAJERO_CAMBIAR_PIN:
                ok = CambiarPin();
                break;
        }
        
        if (ok)
        {
            cout << "Operacion realizada correctamente\n";
        }
        else
        {
            cout << "No se ha podido realizar la operacion seleccionada\n";
            Pausa();
        }
    }
    while (opcion != OPCIONCAJERO_SALIR);

    return false;
}

bool Cajero::DevuelveEstado() {
    return operativo;
}

int Cajero::DevuelveBilletes10() {
    return billetes10;
}

int Cajero::DevuelveBilletes20() {
    return billetes20;
}

int Cajero::DevuelveBilletes50() {
    return billetes50;
}
