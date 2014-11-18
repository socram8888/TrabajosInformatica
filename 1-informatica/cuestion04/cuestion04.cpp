
// cuestionario4.cpp
// Marcos Vives Del Sol - GII 2013/14
// Licencia: WTFPL

#include <iostream>
using namespace std;

struct Range
{
    double min;
    double max;
};

void range_dump(Range &range, ostream &output)
{
    output << "[" << range.min << ", " << range.max << "]";
}

/**********************************************************/ 

struct QuadraticEquation
{
    // y = ax^2 + bx + c
    double a;
    double b;
    double c;
};

double quadratic_compute(QuadraticEquation &equation, double x)
{
    return equation.a * x * x + equation.b * x + equation.c;
}

// Esta funcion, si es posible, calcula el vertice y devuelve true. Sino,
// devuelve false
bool quadratic_vertex(QuadraticEquation &equation, double &vertex)
{
    bool computed = false;
    if (equation.a != 0.0)
    {
        // f(x) = ax^2 + bx + c ---> f'(x) = 2ax + b
        // f'(x)=0 ---> 2ax+b=0 -> x=-b/2a
        vertex = -equation.b / equation.a / 2.0;
        computed = true;
    }
    return computed;
}

void quadratic_minmax(QuadraticEquation &equation, Range &domainRange, Range &imageRange)
{
    bool computeMin = true;
    bool computeMax = true;
    double vertex;
    double imageRangeMin;
    double imageRangeMax;

    // Si la funcion tiene un vertice y esta en el rango especificado, ese
    // punto debe ser si o si un maximo o un minimo de la funcion
    if (quadratic_vertex(equation, vertex) &&
            vertex >= domainRange.min &&
            vertex <= domainRange.max)
    {
        // Si el coeficiente A es positivo, eso quiere decir que la funcion
        // es concava, por lo tanto el vertice es un minimo
        if (equation.a > 0.0)
        {
            imageRange.min = quadratic_compute(equation, vertex);
            computeMin = false;
        }
        // Sino, el coeficiente es negativo, y la funcion es convexa, con lo
        // que el vertice es el maximo
        else
        {
            imageRange.max = quadratic_compute(equation, vertex);
            computeMax = false;
        }
    }

    imageRangeMin = quadratic_compute(equation, domainRange.min);
    imageRangeMax = quadratic_compute(equation, domainRange.max);

    if (computeMin)
        imageRange.min = min(imageRangeMin, imageRangeMax);

    if (computeMax)
        imageRange.max = max(imageRangeMin, imageRangeMax);
}

// Esta funcion convierte objetos QuadraticEquation en un texto legible como
// lo escribiria un matematico, es decir, omitiendo el "1" al multiplicar
// y omitiendo los coeficientes cuyo valor es cero
void quadratic_dump(QuadraticEquation &equation, ostream &output)
{
    bool firstOperand = true;
    output << "y=";
    if (equation.a != 0.0)
    {
        if (equation.a != 1.0)
            output << equation.a;
        output << "x^2";
        firstOperand = false;
    }
    if (equation.b != 0.0)
    {
        if (!firstOperand && equation.b > 0.0)
            output << "+";
        if (equation.b != 1.0)
            output << equation.b;
        output << "x";
        firstOperand = false;
    }
    if (firstOperand)
        output << equation.c;
    else
    {
        if (equation.c != 0.0)
        {
            if (equation.c > 0.0)
                output << "+";
            output << equation.c;
        }
    }
}

/**********************************************************/ 

void read_params(QuadraticEquation &equation, Range &domainRange)
{
    cout << "Introduce los coeficientes de y=Ax^2+Bx+C" << endl;
    cout << " - A: ";
    cin >> equation.a;
    cout << " - B: ";
    cin >> equation.b;
    cout << " - C: ";
    cin >> equation.c;

    cout << endl << "Introduce el rango " << endl;
    cout << " - Minimo: ";
    cin >> domainRange.min;
    cout << " - Maximo: ";
    cin >> domainRange.max;

    cout << endl << "La funcion es: ";
    quadratic_dump(equation, cout);
    cout << " Rango: ";
    range_dump(domainRange, cout);
    cout << endl << endl;
}

void do_normalization(QuadraticEquation &equation, Range &domainRange, Range &imageRange)
{
    double x, y, normalizedY;

    while (true)
    {
        cout << "Valor de X: ";
        cin >> x;
        y = quadratic_compute(equation, x);
        normalizedY = (y - imageRange.min) / (imageRange.max - imageRange.min);
        cout << "Y: " << y << " - Y normalizada: " << normalizedY << endl;
    }
}

int main()
{
    QuadraticEquation equation;
    Range domainRange;
    Range imageRange;

    read_params(equation, domainRange);
    quadratic_minmax(equation, domainRange, imageRange);
    do_normalization(equation, domainRange, imageRange);

    return 0;
}
