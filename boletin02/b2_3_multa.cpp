// b2_3_multa.cpp 
// Marcos Vives Del Sol - GII 19/X/2013
// License: WTFPL

#include <iostream>
#include <math.h>
using namespace std;

int main(void)
{
    double speed, limit;
    int excess;

    // En estas variables se almacena la multa y los puntos
    int fine = 0, points = 0;

    // Este contador se emplea para modificar los valores de la multa y puntos
    // en base a la fila de la tabla de sanciones
    int tableRow = 0;

    cout << "Este programa calcula si tenemos multa o no y si la tenemos el "
    "importe y los puntos de la sancion a partir de la velocidad a la que "
    "circulamos y el limite de velocidad de la via." << endl << endl;

    cout << "Dime velocidad de circulacion: ";
    cin >> speed;
    cout << "Dime limite de la via: ";
    cin >> limit;
    excess = (int) floor(speed - limit);

    // El funcionamiento del bucle se basa en ir decrementando el exceso de
    // velocidad hasta que sea cero o negativo y salgamos del bucle, con lo
    // que dejamos de incrementar la multa y los puntos del carnet a restar, o
    // hasta que hayamos aplicado la maxima sancion posible (tableRow == 5)
    //
    // Cuadro con valores relativos:
    //  30  40  50  60  70  80  90 100 110 120 Mult Pt
    // -----------------------------------------------
    //  20  20  20  30  30  30  30  30  30  30 +100 +0
    //  10  10  10  20  20  20  20  20  20  20 +200 +2
    //  10  10  10  10  10  10  10  10  10  10 +100 +2
    //  10  10  10  10  10  10  10  10  10  10 +100 +2
    //  10  10  10  10  10  10  10  10  10  10 +100 +0

    tableRow = 0;
    while (excess > 0 && tableRow < 5)
    {
        // Si es la primera fila
        if (tableRow == 0)
        {
            if (limit < 60)
            {
                // Para límites menores de 60, el rango para el que se aplica
                // la primera multa es de 1-20
                excess -= 20;
            }
            else
            {
                // Para límites mayores o iguales a 60, el rango para el que se
                // aplica la primera multa es de 1-30
                excess -= 30;
            }
        }
        else if (tableRow == 1 && limit >= 60)
        {
            // Para límites iguales o mayores a 60, el rango para el que se
            // aplica la segunda multa es de 31-50
            excess -= 20;
        }
        else
        {
            // Para el resto de filas, los rangos son de 10
            excess -= 10;
        }

        if (tableRow == 1)
        {
            // En la segunda fila, a diferencia del resto, el incremento de la
            // multa es de 200
            fine += 200;
        }
        else
        {
            // Para el resto de filas, se incrementa en 100
            fine += 100;
        }

        if (tableRow >= 1 && tableRow <= 3)
        {
            // Solo se acumulan puntos en las filas 1 a 3
            points += 2;
        }

        tableRow++;
    }

    if (fine > 0)
    {
        cout << endl << "Hay sancion. El importe es de " << fine << " euros y " << points << " punto" << (points != 1 ? "s" : "") << endl;
    }
    else
    {
        cout << endl << "No hay multa" << endl;
    }

    return 0;
}
