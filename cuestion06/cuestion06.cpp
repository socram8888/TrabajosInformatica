
// Informatica - Cuestion 6 (30/XI/2013) - cuestion06.cpp
// Marcos Vives Del Sol (socram8888@gmail.com)
// Licencia: WTFPL

#include <iostream>
#include <string>
using namespace std;

typedef unsigned int uint;
typedef unsigned long ulong;

/*****************************************************************************
*                                MISC UTILS                                *
*****************************************************************************/

/**** void append_word(string &, string) *************************************
* Descripcion: Anade una palabra o conjunto de palabras al final de una frase
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* phrase string E/S frase a la que anadir la palabra
* phrase word    E  palabra que pegar al final de la frase
*
* Valor devuelto:
* void
*****************************************************************************/
void append_word(string &phrase, const string word)
{
    if (word.length() != 0)
    {
        if (phrase.length() != 0)
            phrase += " ";
        phrase += word;
    }
}

/**** void prepend_word(string &, string) ************************************
* Descripcion: Anade una palabra o conjunto de palabras al principio de una
*              frase
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* phrase string E/S frase a la que anadir la palabra
* phrase word    E  palabra que pegar al principio de la frase
*
* Valor devuelto:
* void
*****************************************************************************/
void prepend_word(string &phrase, const string word)
{
    if (word.length() != 0)
    {
        if (phrase.length() != 0)
            phrase.insert(0, " ");
        phrase.insert(0, word);
    }
}

/**** long invert(long) ******************************************************
* Descripcion: Invierte las cifras decimales de un numero (ej.: 1234 -> 4321)
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* in    long    E  el numero
*
* Valor devuelto:
* long El numero invertido
*****************************************************************************/
long invert(long in)
{
    long out = 0;
    while (in != 0)
    {
        out = out * 10 + in % 10;
        in /= 10;
    }
    return out;
}

/*****************************************************************************
*                          INTEGER TO STRING PARSER                        *
*****************************************************************************/

const string SECTION_NAMES_SINGULAR[] = { "", "millon",  "billon",  "trillon"  };
const string SECTION_NAMES_PLURAL[]  = { "", "millones", "billones", "trillones" };

const string UNIT_NAMES[] =      { "un",  "dos",        "tres",        "cuatro",        "cinco",      "seis",        "siete",      "ocho",        "nueve" };
const string UNIT_NAMES_FIRST[] = { "uno",  "dos",        "tres",        "cuatro",        "cinco",      "seis",        "siete",      "ocho",        "nueve" };
const string DEC_NAMES[]  =      {                      "treinta",    "cuarenta",      "cincuenta",  "sesenta",    "setenta",    "ochenta",    "noventa" };
const string CENT_NAMES[] =      { "cien", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos" };

const string DEC_NAMES_TENS[] =          { "diez",  "once",      "doce",      "trece",      "catorce",      "quince",      "dieciseis",  "diecisiete",  "dieciocho",  "diecinueve"  };
const string DEC_NAMES_TWENTIES[] =      { "veinte", "veintiun",  "veintidos", "veintitres", "veinticuatro", "veinticinco", "veintiseis", "veintisiete", "veintiocho", "veintinueve" };
const string DEC_NAMES_TWENTIES_FIRST[] = { "veinte", "veintiuno", "veintidos", "veintitres", "veinticuatro", "veinticinco", "veintiseis", "veintisiete", "veintiocho", "veintinueve" };

/**** string thousands_to_string(uint, bool) *********************************
* Descripcion: Convierte un numero positivo menor de mil en un texto legible
*              en espanol
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* num    uint    E  El numero que convertir
* first  bool    E  Indica si es el primer millar. Necesario para emplear
*                  "uno" en lugar de "un".
*
* Valor devuelto:
* string La frase
*****************************************************************************/
string thousands_to_string(uint num, bool first)
{
    string str = "";

    uint unit = num / 1  % 10;
    uint dec  = num / 10  % 10;
    uint cent = num / 100 % 10;

    if (cent != 0)
        str = CENT_NAMES[cent - 1];

    if (dec == 1)
    {
        append_word(str, DEC_NAMES_TENS[unit]);
        unit = 0;
    }
    else if (dec == 2)
    {
        if (first)
            append_word(str, DEC_NAMES_TWENTIES_FIRST[unit]);
        else
            append_word(str, DEC_NAMES_TWENTIES[unit]);
        unit = 0;
    }
    else if (dec != 0)
        append_word(str, DEC_NAMES[dec - 3]);

    if (unit != 0)
    {
        if (dec != 0)
            append_word(str, "y");
        if (first)
            append_word(str, UNIT_NAMES_FIRST[unit - 1]);
        else
            append_word(str, UNIT_NAMES[unit - 1]);
    }

    return str;
}

/**** string million_to_string(uint, bool) ***********************************
* Descripcion: Convierte un numero positivo menor de un millon en un texto
*              legible en espanol
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* num    uint    E  El numero que convertir
* first  bool    E  Indica si es el primer millon. Necesario para emplear
*                  "uno" en lugar de "un" en el primer millar.
*
* Valor devuelto:
* string La frase
*****************************************************************************/
string million_to_string(uint num, bool first)
{
    string str = "";

    num %= 1000000;
    if (num != 0)
    {
        if (num / 1000 != 0)
        {
            if (num / 1000 != 1)
                append_word(str, thousands_to_string(num / 1000, false));
            append_word(str, "mil");
        }

        append_word(str, thousands_to_string(num, first));
    }

    return str;
}

/**** string number_to_string(long) ******************************************
* Descripcion: Convierte un numero en un texto legible en espanol
*              Ejemplo: "1002011" -> "un millon dos mil once"
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* num    long    E  El numero que convertir
*
* Valor devuelto:
* string La frase
*****************************************************************************/
string number_to_string(long num)
{
    string str = "";

    uint millionId = 0;
    uint millionNum;
    string millionStr;

    if (num == 0)
        str = "cero";
    else
    {
        if (num < 0)
        {
            str = "menos";
            num = -num;
        }
        while (num != 0)
        {
            millionNum = num % 1000000;
            num /= 1000000;

            millionStr = million_to_string(millionNum, millionId == 0);
            if (millionNum == 1)
                append_word(millionStr, SECTION_NAMES_SINGULAR[millionId]);
            else
                append_word(millionStr, SECTION_NAMES_PLURAL[millionId]);
            prepend_word(str, millionStr);

            millionId++;
        }
    }

    return str;
}

/*****************************************************************************
*                            POLYBIUS SQUARE                              *
*****************************************************************************/

const uint INVALID = (uint) -1;
const uint POLYBIUS_SIDE = 5;
const uint POLYBIUS_SIZE = POLYBIUS_SIDE * POLYBIUS_SIDE;
typedef uint PolybiusSquare[POLYBIUS_SIZE];

/**** uint polybius_char_index(char) *****************************************
* Descripcion: Convierte un numero caracter latino en un indice del conjunto
*              "ABCDEFGHIJKLMNOPQRSTUVXYZ". Notese la ausencia de la "W".
*              Ejemplo: para char = "C", esta funcion devuelve 2.
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* chr    char    E  El caracter latino ASCII
*
* Valor devuelto:
* uint El indice, o INVALID si no se admite en un cuadrado de Polybius.
*****************************************************************************/
uint polybius_char_index(char chr)
{
    uint index = INVALID;

    if (chr >= 'A' && chr <= 'V')
        index = chr - 'A';
    else if (chr >= 'X' && chr <= 'Z')
        index = chr - 'A' - 1;
    else if (chr >= 'a' && chr <= 'v')
        index = chr - 'a';
    else if (chr >= 'x' && chr <= 'z')
        index = chr - 'a' - 1;

    return index;
}

/**** uint polybius_index_char(char) *****************************************
* Descripcion: Revierte la operacion realizada por polybius_char_index
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* idx    uint    E  El indice del caracter
*
* Valor devuelto:
* char El caracter latino en mayusculas, o el caracter nulo (\x00) si el
*      indice no tiene un caracter asociado.
*****************************************************************************/
char polybius_index_char(int idx)
{
    char chr = 0;

    if (idx >= ('A' - 'A') && idx <= ('V' - 'A'))
        chr = idx + 'A';
    else if (idx >= ('X' - 'A' - 1) && idx <= ('Z' - 'A' - 1))
        chr = idx + 'A' + 1;

    return chr;
}

/**** uint polybius_invert(uint) *********************************************
* Descripcion: Cambia la columna por la fila y viceversa. El indice
*              corresponde a X * POLYBIUS_SIDE + Y, y esta funcion lo cambia
*              a Y * POLYBIUS_SIDE + X.
*
* Parametros:
* Nombre Tipo  E/S Descripcion
* ------ ------ --- ---------------
* idx    uint    E  El indice del cuadrado
*
* Valor devuelto:
* uint
*****************************************************************************/
uint polybius_invert(uint idx)
{
    if (idx < POLYBIUS_SIZE)
        idx = idx / POLYBIUS_SIDE + (idx % POLYBIUS_SIDE) * POLYBIUS_SIDE;
    return idx;
}

/**** void polybius_fill(PolybiusSquare, string) *****************************
* Descripcion: Rellena el cuadrado de Polybius con la contrasena dada y
*              anade los caracteres faltantes
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* square PolybiusSquare  S  El cuadrado de Polybius a rellenar
* key    string          E  La clave con la que rellenar el cuadrado
*
* Valor devuelto:
* void
*****************************************************************************/
void polybius_fill(PolybiusSquare square, const string key)
{
    uint pos;
    uint polybiusPos = 0;
    uint chrIdx;

    bool stored[POLYBIUS_SIZE];
    for (pos = 0; pos < POLYBIUS_SIZE; pos++)
        stored[pos] = false;

    for (pos = 0; pos < key.length(); pos++)
    {
        chrIdx = polybius_char_index(key[pos]);
        if (chrIdx != INVALID && !stored[chrIdx])
        {
            square[polybius_invert(polybiusPos++)] = chrIdx;
            stored[chrIdx] = true;
        }
    }

    for (chrIdx = 0; chrIdx < POLYBIUS_SIZE; chrIdx++)
    {
        if (!stored[chrIdx])
            square[polybius_invert(polybiusPos++)] = chrIdx;
    }
}

/**** void polybius_reciprocal(PolybiusSquare, PolybiusSquare) ***************
* Descripcion: Calcula el cuadrado reciproco del dado. Se emplea para
*              deshacer la transformacion y descifrar.
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* orig  PolybiusSquare  E  El cuadrado original
* recip  PolybiusSquare  S  El cuadrado reciproco
*
* Valor devuelto:
* void
*****************************************************************************/
void polybius_reciprocal(PolybiusSquare orig, PolybiusSquare recip)
{
    uint pos;
    for (pos = 0; pos < POLYBIUS_SIZE; pos++)
        recip[orig[pos]] = pos;
}

/**** string polybius_cipher(PolybiusSquare, string) *************************
* Descripcion: Cifra o descifra segun el cuadrado dado
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* square PolybiusSquare  E  El cuadrado
* in    string          E  El texto a transformar
*
* Valor devuelto:
* string El texto transformado
*****************************************************************************/
string polybius_cipher(PolybiusSquare square, const string in)
{
    string out = "";
    uint pos;
    uint idx;

    for (pos = 0; pos < in.length(); pos++)
    {
        idx = polybius_char_index(in[pos]);
        if (idx != INVALID)
            out += polybius_index_char(square[idx]);
    }

    return out;
}

/*****************************************************************************
*                            BAZERIES' CIPHER                              *
*****************************************************************************/

/**** string bazeries_clean(string) ******************************************
* Descripcion: Elimina los caracteres de una string que no pueden ser
*              cifrados por Bazeries.
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* in    string          E  El texto a limpiar
*
* Valor devuelto:
* string El texto limpio
*****************************************************************************/
string bazeries_clean(const string in)
{
    string out = "";
    uint pos;

    for (pos = 0; pos < in.length(); pos++)
    {
        if (polybius_char_index(in[pos]) != INVALID)
            out += in[pos];
    }

    return out;
}

/**** char bazeries_charat(string, uint) *************************************
* Descripcion: Saca un caracter de una string, o devuelve BAZERIES_FILLER si
*              la string no contiene el indice dado.
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* str    string          E  La string de la que sacar el caracter
* pos    uint            E  La posicion deseada
*
* Valor devuelto:
* char El caracter, si está, o BAZERIES_FILLER
*****************************************************************************/
const char BAZERIES_FILLER = 'X';
char bazeries_charat(const string str, uint pos)
{
    char chr;

    if (pos < str.length())
        chr = str[pos];
    else
        chr = BAZERIES_FILLER;

    return chr;
}

/**** string bazeries_rotate(string, ulong) **********************************
* Descripcion: Rota una string segun la clave dada, y anade el relleno
*              que pueda ser necesario
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* in    string          E  La string original
* key    ulong          E  La clave
*
* Valor devuelto:
* string La string transformada con el relleno adecuado
*****************************************************************************/
string bazeries_rotate(const string in, ulong key)
{
    string out = "";
    unsigned long tmpKey;
    unsigned long pos = 0;
    uint chunkSize;
    uint chunkPos;

    key = invert(key);
    tmpKey = key;

    while (pos < in.length())
    {
        chunkSize = tmpKey % 10;

        chunkPos = chunkSize;
        while (chunkPos > 0)
            out += bazeries_charat(in, pos + --chunkPos);

        pos += chunkSize;

        tmpKey /= 10;
        if (tmpKey == 0)
            tmpKey = key;
    }

    return out;
}

/**** string bazeries_transcode(string, ulong, bool) *************************
* Descripcion: Cifra o descifra una string por el metodo de Bazeries
*
* Parametros:
* Nombre Tipo          E/S Descripcion
* ------ -------------- --- ---------------
* in    string          E  La string original
* key    ulong          E  La clave
* decode bool            E  True si se quiere descifrar
*
* Valor devuelto:
* string La string transformada
*****************************************************************************/
string bazeries_transcode(const string in, ulong keyNum, bool decode)
{
    PolybiusSquare encodeSquare;
    PolybiusSquare decodeSquare;
    string keyTxt;
    string out;

    out = bazeries_clean(in);
    out = bazeries_rotate(out, keyNum);

    keyTxt = number_to_string(keyNum);
    polybius_fill(encodeSquare, keyTxt);
    if (decode)
    {
        polybius_reciprocal(encodeSquare, decodeSquare);
        out = polybius_cipher(decodeSquare, out);
    }
    else
        out = polybius_cipher(encodeSquare, out);

    return out;
}

/*****************************************************************************
*                             USER INTERFACE                                 *
*****************************************************************************/

void run_transcode(bool decode)
{
    unsigned long key;
    string text = "";

    cout << "Introduce la clave: ";
    cin >> key;

    if (!cin.good() || key == 0)
        cout << "Clave no valida" << endl;
    else
    {
        cin.ignore(1, '\n');
        cout << "Entrada:" << endl;
        getline(cin, text);

        cout << "Salida:" << endl;
        cout << bazeries_transcode(text, key, decode) << endl;
    }
}

int main()
{
    int option;

    cout << "Este programa permite la codificacion y descodificacion de texto"
    "mediante el algoritmo de Bazeries." << endl << endl;

    cout << "  [1]: Cifrar" << endl;
    cout << "  [2]: Descifrar" << endl;
    cout << "Que quieres hacer?: ";
    cin >> option;
    cout << endl;

    switch (option)
    {
        case 1:
            run_transcode(false);
            break;
        case 2:
            run_transcode(true);
            break;
        default:
            cout << "Opcion no valida" << endl;
    }

    return 0;
}
