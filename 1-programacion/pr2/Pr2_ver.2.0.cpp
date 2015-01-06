
/***************************************************************************/
/* Asignatura: Programacion                                                */
/* Curso 2013-2014                                                         */
/* Practica 2                                                              */
/* Ordenacion de vectores                                                  */
/*                                                                         */
/* AUTOR: Jesus Albert , Jorge Esteve                                      */
/* FECHA: 25 de febrero de 2014                                            */
/*                                                                         */
/* PROPOSITO: Medir coste empirico de algoritmos de ordenacion             */
/*            se ordenan vectores de objetos                               */
/*                                                                         */
/*  Historial del Desarrollo:                                              */
/*  Fecha       Autor                 Id  Ver  Descripcion del Cambio      */
/*  ----------  --------------------- --  ---  --------------------------- */
/*  03/03/2014  Jorge Esteve          0  1.0                               */
/*              Jesus Albert                                               */
/*                                                                         */
/*  14/03/2014  Julio Alejandro Ayala 1  2.0                               */
/*              Marcos Vives Del Sol                                       */
/*              Grupo 10                                                   */
/*                                                                         */
/***************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <ctime> 

/*  
 *  Se trabaja sobre un vector con informacion sobre criticas musicales 
 *  de Discos aparecidas en una revista especializada en musica clasica.
 *  La clase "Disco" especifica la estructura de informacion 
 */

#include "disco.h"

using namespace std;

/*
 * Tamanyo maximo del vector a ordenar
 */
const int MAX = 5000;
const int LONGITUD[] = { 10, 500, 1000, 4000, 0 };
const int RND_ITERS = 100;
/*
 * Tipo para definir vectores de discos
 */
typedef Disco VectorDiscos[MAX];

/*
 * Prototipos de las funciones del programa
 */
int CrearVectorDiscos (VectorDiscos, ifstream&);
void Copiar (VectorDiscos, VectorDiscos, int);
bool VerificarOrden (VectorDiscos, int);
void MostrarResultados (int, string, int, int, int); 
void Inicializar (VectorDiscos, VectorDiscos, VectorDiscos);
void Ordenar (VectorDiscos, int, int&, int&, int&);
void Desordenar (VectorDiscos, VectorDiscos, int);
void Invertir (VectorDiscos, VectorDiscos, int);

//Las funciones a COMPLETAR
int OrdenarInsercion (VectorDiscos, int); 
int OrdenarSeleccion (VectorDiscos, int); 
int OrdenarQuicksort (VectorDiscos, int); 

/*
 * Programa principal,  COMPLETAR
 */
int main ()
{
    VectorDiscos v_orig,   //vector con los datos originales
                 v_ord,    //vector con los datos ordenados
                 v_inv,    //vector con los datos inversamente ordenados
                 v_aleat;  //vector con los datos aleatoriamente ordenados
    int tam = 0;           //numero de elementos a ordenar del vector
    int i, iteracion = 0;
    int operaIns = 0,      //contadores de operaciones realizadas por cada metodo 
        operaSel = 0,
        operaQui = 0;
    int operaInsAux = 0,      //contadores de operaciones realizadas por cada metodo 
        operaSelAux = 0,
        operaQuiAux = 0;
    string criterio;     //etiqueta que indica la situacion inicial del vector
    
    //Inicializar los 3 vectores de referencia: original, ordenado e inversamente ordenado
    Inicializar (v_orig, v_ord, v_inv);
    tam = LONGITUD[0];

    while (tam > 0)
    {
        //1: Calcular resultados para un vector ordenad
        criterio = "Vector inicialmente ordenado";
        Ordenar (v_ord, tam, operaIns, operaSel, operaQui);
        MostrarResultados (tam, criterio, operaIns, operaSel, operaQui);
        
        //2: Calcular resultados para un vector inv. ordenado
        criterio = "Vector inicialmente inversamente ordenado";
        Ordenar (v_inv, tam, operaIns, operaSel, operaQui);
        MostrarResultados (tam, criterio, operaIns, operaSel, operaQui);
        
        //3: Calcular resultados para un vector aleatorio
        criterio = "Vector aleatoriamente ordenado";
        operaIns = 0;
        operaSel = 0;
        operaQui = 0;
        for (i = 0; i < RND_ITERS; i++)
        {
            Desordenar (v_orig, v_aleat, tam);
            Ordenar (v_aleat, tam, operaInsAux, operaSelAux, operaQuiAux);
            operaIns += operaInsAux;
            operaSel += operaSelAux;
            operaQui += operaQuiAux;
        }
        operaIns /= RND_ITERS;
        operaSel /= RND_ITERS;
        operaQui /= RND_ITERS;
        MostrarResultados (tam, criterio, operaIns, operaSel, operaQui);
        
        iteracion++;
        tam = LONGITUD[iteracion];
    }
    return 0;
} 

/*************** Inicializar ********************************************
 *
 *  Prototipo:    void Inicializar (VectorDiscos orig, VectorDiscos ord, VectorDiscos inv)
 *
 *  Descripcion:  Inicializa los 3 vectores de referencia: original, ordenado e 
 *                inversamente ordenado
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  orig            VectorDiscos   E/S  vector con los datos originales
 *  ord             VectorDiscos   E/S  vector con los datos ordenados
 *  inv             VectorDiscos   E/S  vector con los datos inversamente ordenados
 *
 *  Valor devuelto:
 *  ninguno
 ************************************************************************/
void Inicializar (VectorDiscos orig, VectorDiscos ord, VectorDiscos inv)
{
    int num_datos = 0;   //numero de datos almacenados en el archivo
    ifstream f;          //archivo con los datos que se cargan en el vector
	
    //leer los datos del vector desde el archivo "discos.txt"
    f.open ("discos.txt");
    if ( !f )
        cout << "Error al abrir el archivo de datos" << endl;
    else
    {
        num_datos = CrearVectorDiscos (orig, f);
        Copiar (orig, ord, num_datos); 
        OrdenarQuicksort (ord, num_datos);
        Invertir (ord, inv, num_datos); 
	}
    f.close ();	
}

/*************** CrearVectorDiscos **************************************
 *
 *  Prototipo:    int CrearVectorDiscos (VectorDiscos v, ifstream& f)
 *
 *  Descripcion:  Almacena en el vector v los datos almacenados en el
 *                archivo f
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E/S  vector cuyos elementos se inicializan
 *  f               ifstream       E/S  archivo que contiene los datos
 *
 *  Valor devuelto:
 *  int, Numero de elementos leidos y almacenados
 ************************************************************************/
int CrearVectorDiscos (VectorDiscos v, ifstream& f)
{
    int i = 0;

    while (v[i].leerDisco(f) && i < MAX)
        i++;

    return i;
}

/*************** Ordenar ************************************************
 *
 *  Prototipo:    void Ordenar (VectorDiscos v, int n, int& opI, int& opS, int& opQ)
 *
 *  Descripcion:  Ordena el vector v por los 3 metodos de ordenacion. 
 *                Mantiene una copia de v para evitar que una ordenacion
 *                afecte a las siguientes.
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E    vector con los datos a ordenar
 *  n               int            E    numero de elementos de v que se ordenan
 *  opI             int            E/S  operaciones realizadas por Insercion
 *  opS             int            E/S  operaciones realizadas por Seleccion
 *  opQ             int            E/S  operaciones realizadas por Quicksort
 *
 *  Valor devuelto:
 *  ninguno
 ************************************************************************/
void Ordenar (VectorDiscos v, int n, int& opI, int& opS, int& opQ)
{
    VectorDiscos v_copia; //vector que se ordena
	
    //crear la copia de v
    Copiar (v, v_copia, n);
    cout << "Ordenando Insercion ... ";
    opI = OrdenarInsercion (v, n);
    cout << "fin" << endl;
    //nueva copia de v
    Copiar (v_copia, v, n);
    cout << "Ordenando Seleccion ... ";
    opS = OrdenarSeleccion (v, n);
    cout << "fin" << endl;
    //nueva copia de v
    Copiar (v_copia, v, n); 
    cout << "Ordenando Quicksort ... ";
    opQ = OrdenarQuicksort (v, n);
    cout << "fin" << endl;

    return;
}

/*************** VerificarOrden *********************************************
 *
 *  Prototipo:    bool VerificarOrden (VectorDiscos v, int n)
 *
 *  Descripcion:  Verifica que los n primeros elementos del vector v
 *                estan ordenados (true) o no (false).
 *                El objetivo es comprobar el correcto funcionamiento
 *                del proceso de ordenacion. Utilizar para TEST
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E    vector cuyo ordenacion se verifica
 *  n               int            E    numero de elementos de v
 *
 *  Valor devuelto:
 *  bool
 *****************************************************************************/
bool VerificarOrden (VectorDiscos v, int n)
{
    int i;
    bool ordenados = true;

    i = 0;
    while ( (i < n - 1) && ordenados )
    {
        if ( v[i].getClave() > v[i + 1].getClave() )
            ordenados = false;
        i++;
    }

    return ordenados;
}

/*************** MostrarResultados *******************************************
 *
 *  Prototipo:    void MostrarResultados (int n, int a, int c)
 *
 *  Descripcion:  Muestra el numero de operaciones realizadas para ordenar
 *                el vector por los 3 metodos.
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *  n               int         E    talla
 *  texto           string      E    texto con el tipo de ordenacion inicial del vector
 *  opI             int         E    operaciones realizadas por Insercion
 *  opS             int         E    operaciones realizadas por Seleccion
 *  opQ             int         E    operaciones realizadas por Quicksort
 *
 *  Valor devuelto:
 *  ninguno
 *****************************************************************************/
void MostrarResultados (int n, string texto, int opI, int opS, int opQ)
{
    cout << endl;
    cout << "*** " << texto << " ***" << endl;
    cout << "Resultados ==> ";
    cout << "n = " << n << endl;
    cout << "   - Insercion: " << opI << " pasos" << endl;
    cout << "   - Seleccion: " << opS << " pasos" << endl;
    cout << "   - Quicksort: " << opQ << " pasos" << endl;
    cout << "-------------------------------------------" << endl;
	system ("PAUSE");    
    cout << endl;

    return;
} 

/*************** Copiar *****************************************************
 *
 *  Prototipo:    void Copiar (VectorDiscos origen, VectorDiscos destino, int n)
 *
 *  Descripcion:  Copiar los datos del vector origen en el vector destino
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  origen          VectorDiscos   E    vector origen de la copia
 *  destino         VectorDiscos   E/S  vector destino de la copia
 *  n               int            E    numero de elementos a copiar
 *
 *  Valor devuelto:
 *  ninguno
 *****************************************************************************/
void Copiar (VectorDiscos origen, VectorDiscos destino, int n)
{
    int i;

    for (i = 0; i < n; i++)
        destino[i] = origen[i];
		
    return;
}

/*************** Desordenar **************************************************
 *
 *  Prototipo:    void Desordenar (VectorDiscos origen, VectorDiscos destino, int n)
 *
 *  Descripcion:  Copiar de manera desordenada (aleatoria) los datos del vector 
 *                origen en el vector destino
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  origen          VectorDiscos   E    vector origen de la copia
 *  destino         VectorDiscos   E/S  vector destino de la copia
 *  n               int            E    numero de elementos a copiar
 *
 *  Valor devuelto:
 *  ninguno
 *****************************************************************************/
void Desordenar (VectorDiscos origen, VectorDiscos destino, int n)
{
    int pos, fin, i;
    Disco aux;

    srand ( time(NULL) );
 
    Copiar(origen, destino, n);
    fin = n - 1;
    for (i = 0; i < n; i++)
    {
        pos = rand () % (fin + 1);
        aux = destino[fin];
        destino[fin] = destino[pos];
        destino[pos] = aux;
        fin--;
    }

    return;
}

/*************** Invertir **************************************************
 *
 *  Prototipo:    void Invertir (VectorDiscos origen, VectorDiscos destino, int n)
 *
 *  Descripcion:  Copiar en orden inverso los datos del vector origen 
 *                en el vector destino
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  origen          VectorDiscos   E    vector origen de la copia
 *  destino         VectorDiscos   E/S  vector destino de la copia
 *  n               int            E    numero de elementos a copiar
 *
 *  Valor devuelto:
 *  ninguno
 *****************************************************************************/
void Invertir (VectorDiscos origen, VectorDiscos destino, int n)
{
    int i;

    for (i = 0; i < n / 2; i++)
        destino[i] = origen[n - i - 1];

    return;
}

/*************** OrdenarInsercion *********************************************
 *
 *  Prototipo:    int OrdenarInsercion (VectorDiscos v, int n)
 *
 *  Descripcion:  Ordena por el metodo Insercion los n primeros
 *                elementos del vector v. Contabiliza el numero de operaciones
 *                (asignaciones y comparaciones) de elementos del vector realizadas.
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E/S  vector cuyos elementos se ordenan
 *  n               int            E    numero de elementos de v que se ordenan
 *
 *  Valor devuelto:
 *  int, Numero de operaciones realizadas sobre elementos del vector v
 *****************************************************************************/
int OrdenarInsercion (VectorDiscos v, int n)
{
    int ops = 0;
    int i, j;

    for (i = n - 2; i >= 0; i--)
    {
        v[n] = v[i];
        ops++;
    
        j = i + 1;
        while (v[j].getClave() < v[n].getClave())
        {
            ops++; // Comparacion bucle

            v[j - 1] = v[j];
            ops++;

            j++;
        }
        ops++; // Comparacion fallida bucle

        v[j - 1] = v[n];
        ops++;
    }

    return ops;
}

/*************** OrdenarSeleccion *********************************************
 *
 *  Prototipo:    int OrdenarSeleccion (VectorDiscos v, int n)
 *
 *  Descripcion:  Ordena por el metodo Seleccion los n primeros
 *                elementos del vector v. Contabiliza el numero de operaciones
 *                (asignaciones y comparaciones) de elementos del vector realizadas.
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E/S  vector cuyos elementos se ordenan
 *  n               int            E    numero de elementos de v que se ordenan
 *
 *  Valor devuelto:
 *  int, Numero de operaciones realizadas sobre elementos del vector v
 *****************************************************************************/
int OrdenarSeleccion (VectorDiscos v, int n)
{
    int i, j, pos_min, ops=0;
    Disco aux;
    
    for(i= 0; i < n - 1; i++)
    {
        pos_min = i;
        for ( j=i + 1; j < n; j++)
        {
            ops++;
            if (v[j].getClave() < v[pos_min].getClave())
                pos_min = j;
        }
        if (pos_min != i)
        {
            aux = v[i];
            v[i]= v[pos_min];
            v[pos_min] = aux;
            ops += 3;
        }
           
    }
    return ops;
}

/*************** Particion *********************************************
 *
 *  Prototipo:    int Particion (VectorDiscos v, int izq, int der)
 *
 *  Descripcion:  Ordena por el metodo Quicksort los elementos entre izq y der
 *                Contabiliza el numero de operaciones
 *                (asignaciones y comparaciones) de elementos del vector realizadas.
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E/S  vector cuyos elementos se ordenan
 *  izq             int            E    posicion izquierda
 *  der             int            E    posicion derecha
 *
 *  Valor devuelto:
 *  int, Numero de operaciones realizadas sobre elementos del vector v
 *****************************************************************************/
int Particion(VectorDiscos v, int izq, int der)
{
    int i, j;
    int ops = 0;
    Disco piv, aux;

    piv = v[(izq + der) / 2];
    ops++;
    i = izq;
    j = der;

    while (i <= j)
    {
        while (v[i].getClave() < piv.getClave())
        {
            i++;
            ops++;
        }
        ops++;

        while (v[j].getClave() > piv.getClave())
        {
            j--;
            ops++;
        }
        ops++;

        if (i < j)
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            ops += 3;

            i++;
            j--;
        }
        else if (i == j)
        {
            i++;
            j--;
        }
    }
    
    if (izq < j)
        ops += Particion(v, izq, j);
    if (i < der)
        ops += Particion(v, i, der);

    return ops;
}

/*************** OrdenarQuickSort *********************************************
 *
 *  Prototipo:    int OrdenarQuicksort (VectorDiscos v, int n)
 *
 *  Descripcion:  Ordena por el metodo Quicksort los n primeros
 *                elementos del vector v. Contabiliza el numero de operaciones
 *                (asignaciones y comparaciones) de elementos del vector realizadas.
 *
 *  Parametros:
 *  Nombre          Tipo           E/S  Descripcion
 *  ------          ----------     ---  ------------
 *  v               VectorDiscos   E/S  vector cuyos elementos se ordenan
 *  n               int            E    numero de elementos de v que se ordenan
 *
 *  Valor devuelto:
 *  int, Numero de operaciones realizadas sobre elementos del vector v
 *****************************************************************************/
int OrdenarQuicksort (VectorDiscos v, int n)
{
    return Particion(v, 0, n - 1);
}


