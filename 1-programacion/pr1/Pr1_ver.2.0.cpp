/*******************************************************************/
/* Asignatura: Programacion. Grado Ing. Informática/Multimedia    */
/* Curso 2013-2014                                                */
/* Laboratorio. Practica 1                                        */
/* Busqueda en vectores                                            */
/*                                                                */
/* AUTOR: Ricardo Ferris                                          */
/* ALUMNOS: Julio Alejandro Ayala, Marcos Vives Del Sol            */
/*                                                                */
/* PROPOSITO: Medir coste empirico de algoritmos de busqueda      */
/*                                                                */
/*******************************************************************/
#include <iostream>
#include <cstdlib>  //Equivalente C, #include <stdlib.h>
#include <ctime>    //Equivalente C, #include <time.h>

using namespace std;

// Tamanyo maximo del vector
const int MAX = 100000;
// Numero de algoritmos con los que trabajar
const int N_ALGORITMOS = 4;

// Tipo para el vector
typedef int Vector[MAX];

// Tipo para el vector de contadores
typedef int Contadores[N_ALGORITMOS];

/*
* Prototipos de las funciones empleadas,
* implementadas despues de main()
*/
void CrearVector (Vector, int);
void MostrarResultados (Contadores, int tam);
bool BusquedaSecuencial (Vector, int, int, int &);
bool BusquedaSecuencialParada (Vector, int, int, int &);
bool BusquedaSecuencialCentinela (Vector, int, int, int &);
bool BusquedaBinaria (Vector, int, int, int &);
void RealizarBusquedas (int, Vector, int, int, Contadores);
int PedirNumero (int min, int max);
int GenerarNumeroAleatorio (int min, int max);

static const int ITERACIONES = 100;
static const int TAMANOS[] = { 10, 100, 5000, 50000, 0 };

/*
* Programa principal
*/
int main ()
{
    Vector v;        // Vector sobre el que se busca
    int tam;          // Numero de elementos del vector
    int x;            // Dato a buscar
    int alg;          // Algoritmo con el que se desea buscar
    Contadores total; // Contadores del total de operaciones, 1 x algoritmo
    int i;
    int j;
    srand (2014);
    // Pedimos la talla del vector con el que queremos trabajar

    j= 0;
    tam = TAMANOS [j];
    while ( tam > 0)
    {
        // Crear los elementos de un vector 'v' de 'tam' posiciones
        CrearVector (v, tam);


        // Poner contadores a cero
        for (i = 0; i < N_ALGORITMOS; i++)
        {
            total[i] = 0;
        }

        for ( i = 0; i < ITERACIONES; i++ )
        {
            x = GenerarNumeroAleatorio (0, tam);
            for ( alg=0; alg< 4; alg ++)
            {
                // Buscar  x el vector v mediante los 4 metodos
                // alg = 0: Busqueda Secuencial
                // alg = 1: Busqueda Secuencial con Parada
                // alg = 2: Busqueda Secuencial con Centinela
                // alg = 3: Busqueda Binaria
                RealizarBusquedas (alg, v, tam, x, total);
            }
        }
        //mostrar numero de operaciones de cada algoritmo
        MostrarResultados (total, tam);


        j ++;
        tam = TAMANOS [j];
    }
    system("pause");

    return 0;
}

/*************** CrearVector *********************************************
*
*  Prototipo:    void CrearVector (Vector v, int n)
*
*  Descripcion:  Inicializa los n primeros elementos del vector v
*                de forma ordenada con enteros pares
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  v              Vector      E/S  vector cuyos elementos se inicializan
*  n              int        E    numero de elementos de v a inicializar
*
*  Valor devuelto:
*  ninguno
************************************************************************/
void CrearVector (Vector v, int n)
{
    int i;

    for (i = 0; i < n; i++)
        v[i] = i * 2;

    return;
}

/*************** MostrarResultados *********************************************
*
*  Prototipo:    void MostrarResultados (Contadores contadores)
*
*  Descripcion:  Muestra el numero de operaciones realizadas por cada algoritmo
*                para buscar en el vector
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  contadores      Contadores  E    numero de operaciones realizadas x algoritmo
*
*  Valor devuelto:
*  ninguno
*****************************************************************************/
void MostrarResultados (Contadores contadores, int tam)
{

    cout << endl;
    cout << "Resultados" << endl;

    cout << " Longitud de vector = " << tam << endl;

    cout << "-------------------------------------------" << endl;
    cout << "Busqueda Secuencial:" <<endl;
    cout << "\tTotal pasos = " << (double) contadores[0] / ITERACIONES << endl;
    cout << "Busqueda Secuencial con Parada:" <<endl;
    cout << "\tTotal pasos = " << (double) contadores[1] / ITERACIONES  << endl;
    cout << "Busqueda Secuencial con Centinela:" <<endl;
    cout << "\tTotal pasos = " << (double) contadores[2] / ITERACIONES  << endl;
    cout << "Busqueda Binaria:" <<endl;
    cout << "\tTotal pasos = " << (double) contadores[3] / ITERACIONES  << endl;
    cout << "-------------------------------------------" << endl;

    return;
}

/*************** BusquedaSecuencial *************************************
*
*  Prototipo:    bool BusquedaSecuencial (Vector v, int n, int x, int& total)
*
*  Descripcion:  Implementa el metodo de busqueda secuencial (sin parada):
*                busca 'x' en los 'n' primeros elementos de 'v'
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  v              Vector      E    vector sobre el que se busca
*  n              int        E    numero de elementos de v
*  x              int        E    dato a buscar
*  pasos          int        E/S  numero total de pasos realizados
*
*  Valor devuelto:
*  bool, true si se localiza el dato 'x', false en caso contrario
************************************************************************/
bool BusquedaSecuencial (Vector v, int n, int x, int & pasos)
{
    int i;
    bool enc = false;

    i = 0;

    // Contabilizar las 2 asignaciones anteriores
    pasos += 2;

    while (i < n)
    {
        if (v[i] == x)
        {
            enc = true;
            // Contabilizar la asignacion
            pasos++;
        }
        // Contabilizar la comparacion del vector del if
        pasos++;

        i++;
        //contabilizar la comparacion del while y el incr. de i
        pasos += 2;
    }

    //contabilizar la comp. de salida del while
    pasos++;

    return enc;
}

/*************** BusquedaSecuencialParada *********************************
*
*  Prototipo:    bool BusquedaSecuencialParada (Vector v, int n, int x, int& total)
*
*  Descripcion:  Implementa el metodo de busqueda secuencial (con parada):
*                busca 'x' en los 'n' primeros elementos de 'v'
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  v              Vector      E    vector sobre el que se busca
*  n              int        E    numero de elementos de v
*  x              int        E    dato a buscar
*  pasos          int        E/S  numero total de operaciones realizadas
*
*  Valor devuelto:
*  bool, true si se localiza el dato 'x', false en caso contrario
************************************************************************/
bool BusquedaSecuencialParada (Vector v, int n, int x, int & pasos)
{
    int i;
    bool enc;

    i = 0;
    pasos ++;
    while ( (i < n) && (v[i] != x) )
    {
        // Comparacion del while
        pasos += 2;

        i++;
        // Incremento de i
        pasos++;
    }

    // Comparacion final del while
    pasos += 2;

    if (i == n)
        enc = false;
    else
        enc = true;

    // Comparacion del if y asignacion de enc
    pasos += 2;

    return enc;
}

/*************** BusquedaSecuencialCentinela *******************************
*
*  Prototipo:    bool BusquedaSecuencialCentinela (Vector v, int n, int x, int& total)
*
*  Descripcion:  Implementa el metodo de busqueda secuencial con centinela:
*                busca 'x' en los 'n' primeros elementos de 'v'
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  v              Vector      E    vector sobre el que se busca
*  n              int        E    numero de elementos de v
*  x              int        E    dato a buscar
*  pasos          int        E/S  numero total de operaciones realizadas
*
*  Valor devuelto:
*  bool, true si se localiza el dato 'x', false en caso contrario
************************************************************************/
bool BusquedaSecuencialCentinela (Vector v, int n, int x, int & pasos)
{
    int i;
    bool enc;

    v[n] = x;
    i = 0;
    pasos += 2;
    while (v[i] != x)
    {
        pasos ++;
        i++;
        pasos ++;
    }

    pasos ++;
    if (i == n)
        enc = false;
    else
        enc = true;
    pasos += 2;

    return enc;
}

/*************** BusquedaBinaria *************************************
*
*  Prototipo:    bool BusquedaBinaria (Vector v, int n, int x, int& total)
*
*  Descripcion:  Implementa el metodo de busqueda binaria:
*                busca 'x' en los 'n' primeros elementos de 'v'
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  v              Vector      E    vector sobre el que se busca
*  n              int        E    numero de elementos de v
*  x              int        E    dato a buscar
*  pasos          int        E/S  numero total de operaciones realizadas
*
*  Valor devuelto:
*  bool, true si se localiza el dato 'x', false en caso contrario
************************************************************************/
bool BusquedaBinaria (Vector v, int n, int x, int & pasos)
{
    int izq, der, cen;
    bool enc = false;
    izq = 0;
    der = n - 1;
    cen = (izq + der) / 2;

    // Inicializacion de variables
    pasos += 4;

    while ( (izq <= der) && (v[cen] != x) )
    {
        // Comparacion del while
        pasos += 2;

        if (x < v[cen])
            der = cen - 1;
        else
            izq = cen + 1;
        // Comparacion del if y asignacion de variable
        pasos += 2;

        cen = (izq + der) / 2;
        // Calculo de la posicion central
        pasos++;
    }

    // Comparacion fallida del while
    pasos += 2;

    if (izq > der)
        enc = false;
    else
        enc = true;

    // Comparacion y asignacion
    pasos += 2;

    return enc;
}

/*************** RealizarBusquedas ************************************
*
*  Prototipo:    void RealizarBusqueda (Vector v, int n, int x, Contadores contadores)
*
*  Descripcion:  Permite seleccionar el algoritmo de busqueda emplear para:
*                busca 'x' en los 'n' primeros elementos de 'v'
*                alg=0: Busqueda Secuencial
*                alg=1: Busqueda Secuencial con Parada
*                alg=2: Busqueda Secuencial con Centinela
*                alg=3: Busqueda Binaria
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  alg            int        E    identificador de algoritmo a emplear
*  v              Vector      E    vector sobre el que se busca
*  n              int        E    numero de elementos de v
*  x              int        E    dato a buscar
*  total          int[]      E/S  numero total de operaciones realizadas
*
*  Valor devuelto:
*  Ninguno
************************************************************************/
void RealizarBusquedas (int alg, Vector v, int n, int x, Contadores contadores)
{
    bool ok = false;

    //cout << "\n** Buscando... ";
    switch (alg)
    {
        case 0:
            //cout << "Busqueda secuencial. ";
            ok = BusquedaSecuencial (v, n, x, contadores[0]);
            break;
        case 1:
            //cout << "Busqueda secuencial con parada. ";
            ok = BusquedaSecuencialParada (v, n, x, contadores[1]);
            break;
        case 2:
            //cout << "Busqueda secuencial con centinela. ";
            ok = BusquedaSecuencialCentinela (v, n, x, contadores[2]);
            break;
        case 3:
            //cout << "Busqueda binaria. ";
            ok = BusquedaBinaria (v, n, x, contadores[3]);
            break;
    }
    /*
    cout << " Elemento " << x;
    if (ok)
        cout << " encontrado **" << endl;
    else
        cout << " NO encontrado **" << endl;
    */
    return;
}

/*************** PedirNumero ******************************************
*
*  Prototipo:    int PedirNumero (int min, int max)
*
*  Descripcion:  Lee un entero de teclado hasta que este en el
*                rango [min..max] y lo devuelve
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  min            int        E    valor minimo del rango
*  max            int        E    valor maximom del rango
*
*  Valor devuelto:
*  int    valor leido correcto
************************************************************************/
int PedirNumero (int min, int max)
{
    int x;

    do
    {
        // Leer el tamanyo del vector
        cout << "Dame entero entre " << min << " y " << max - 1 << " (ambos incluidos): ";
        cin >> x;
    }
    while (x < min || max <= x);

    return x;
}

/*************** GenerarNumeroAleatorio ********************************
*
*  Prototipo:    int GenerarNumeroAleatorio (int min, int max)
*
*  Descripcion:  Genera un entero aleatorio en el rango [min..max - 1]
*                y lo devuelve
*
*  Parametros:
*  Nombre          Tipo        E/S  Descripcion
*  ------          ----------  ---  ------------
*  min            int        E    valor minimo del rango
*  max            int        E    valor maximom del rango
*
*  Valor devuelto:
*  int    valor generado
************************************************************************/
int GenerarNumeroAleatorio (int min, int max)
{
    return rand () % (max - min) + min;
}

/***********************************************************************
*                          TABLA A RELLENAR                          *
***********************************************************************
*                                    NUMERO DE ELEMENTOS            *
*                          ----------------------------------------- *
*                          *  10    *  100  *  5000  *  50000  * *
*  ALGORIMO                *  PASOS  *  PASOS  *  PASOS  *  PASOS  * *
*  ================================================================= *
*  BUSQUEDA SECUENCIAL    | 33.49  | 303.54  | 15003.5 | 150003  | *
*  ------------------------|---------------------------------------| *
*  BUSQUEDA SEC. PARADA    | 23.27  | 183.77  | 9151.92 | 89208.4 | *
*  ------------------------|---------------------------------------| *
*  BUSQUEDA SEC. CENTINELA | 17.18  | 124.18  | 6102.68 | 59473.9 | *
*  ------------------------|---------------------------------------| *
*  BUSQUEDA BINARIA        | 20.95  | 36.25  | 65      | 80.9    | *
*  ================================================================= *
*                                                                    *
***********************************************************************/

/* COSTES ALGORITMOS
*
* SECUENCIAL: N^2
* SEC. PARADA: N^2
* SEC. CENTINELA: N^2
* BINARIA: N*LOG2(N)
*
*/