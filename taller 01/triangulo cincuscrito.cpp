#include <iostream>
using namespace std;
int main()
{

    int lado1, lado2, lado3, radio;
    float area, sperimetro;
    do
    {
        cout << "..........EJERCICIO 7 TRIANGULO CIRCUNSCRITO.........\n"<< endl;
        cout << "ingrese el lado 1: ";
        cin >> lado1;
        cout << "ingrese el lado 2: ";
        cin >> lado2;
        cout << "ingrese el lado 3: ";
        cin >> lado3;
        cout << "ingrese el radio: ";
        cin >> radio;
        if (lado1 <= 0 || lado2 <= 0 || lado3 <= 0 || radio <= 0)
        {
            cout << "Los valores ingresados deben de ser mayores a cero" << endl;
            cout << "ingrese los valores de nuevo\n"<< endl;
        }
    } while (lado1 <= 0 || lado2 <= 0 || lado3 <= 0 || radio <= 0);

    sperimetro = (lado1 + lado2 + lado3) / 2;
    area = radio * sperimetro;
    cout << "semiperimetro: " << sperimetro << endl;
    cout << "area: " << area;
    return 0;
}