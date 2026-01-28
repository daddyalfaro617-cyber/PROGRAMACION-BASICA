#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int base, altura, area, perimetro, diagonal;
    do
    {
        cout << "............EJERCICIO 2 RECTANGULO..........." << endl;
        cout << "ingrese el valor de la base del rectangulo: ";
        cin >> base;
        cout << "ingrese el valor dela altura del rectangulo: ";
        cin >> altura;
        if (base <= 0 || altura <= 0)
        {
            cout << "los valores ingresados deben de ser mayores a cero" << endl;
            cout << "ingrese los volores de nuevo\n"
                 << endl;
        }
    } while (base <= 0 || altura <= 0);

    area = base * altura;
    perimetro = (base * altura) * 2;
    diagonal = sqrt((base * base) + (altura * altura));
    cout << "area: " << area << endl;
    cout << "perimetro: " << perimetro << endl;
    cout << "diagonal: " << diagonal << endl;

    return 0;
}