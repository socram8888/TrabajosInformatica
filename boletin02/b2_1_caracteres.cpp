// b2_1_caracteres.cpp
// Marcos Vives Del Sol - GII 19/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    char in;
    string text = "otra cosa";
    cout << "Este programa nos muestra un caracter en mayusculas si esta en minusculas o un numero en letras si es un caracter de un numero. En otro caso nos muestra el mensaje 'Es otra cosa'." << endl << endl;
    cout << "Dame caracter: ";
    cin >> in;

    cout << "Has introducido ";
    switch (in) {
        case '0':
            cout << "un cero";
            break;
        case '1':
            cout << "un uno";
            break;
        case '2':
            cout << "un dos";
            break;
        case '3':
            cout << "un tres";
            break;
        case '4':
            cout << "un cuatro";
            break;
        case '5':
            cout << "un cinco";
            break;
        case '6':
            cout << "un seis";
            break;
        case '7':
            cout << "un siete";
            break;
        case '8':
            cout << "un ocho";
            break;
        case '9':
            cout << "un nueve";
            break;
        default:
            if (in >= 'a' && in <= 'z')
            {
                cout << (char) (in - 'a' + 'A') << endl;
            }
            else
            {
                cout << "otra cosa" << endl;
            }
    }

    return 0;
}
