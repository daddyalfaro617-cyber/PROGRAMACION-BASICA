#include <iostream>
#include <cmath>
using namespace std;
int main()
{

    float area, sperimetro, lado1, lado2, lado3;
    do
    {
        cout << "..........EJERCICIO 8 TRIANGULO CON LA FORMULA DE HERON.........\n"
             << endl;
        cout << "ingrese el lado 1: ";
        cin >> lado1;
        cout << "ingrese el lado 2: ";
        cin >> lado2;
        cout << "ingrese el lado 3: ";
        cin >> lado3;
        if (lado1 <= 0 || lado2 <= 0 || lado3 <= 0)
        {
            cout << "Los valores ingresados deben de ser mayores a cero" << endl;
            cout << "ingrese los valores de nuevo\n"
                 << endl;
        }
    } while (lado1 <= 0 || lado2 <= 0 || lado3 <= 0);
    sperimetro = (lado1 + lado2 + lado3) / 2;
    area = sqrt(sperimetro * (sperimetro - lado1) * (sperimetro - lado2) * (sperimetro - lado3));
    cout << "semiperimetro: " << sperimetro << endl;
    cout << "area: " << area;

    return 0;
}