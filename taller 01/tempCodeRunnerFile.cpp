#include <iostream>
using namespace std;
int main()
{

    int lado1, lado2, base, altura, perimetro;
    float area;
    do
    {
        cout << "..........EJERCICIO 5 TRIANGULO..........\n"
             << endl;
        cout << "ingrese el lado 1 : ";
        cin >> lado1;
        cout << "ingrese el lado 2: ";
        cin >> lado2;
        cout << "ingrese la base: ";
        cin >> base;
        cout << "ingrese la altura: ";
        cin >> altura;
        if (lado1 <= 0 || lado2 <= 0 || base <= 0 || altura <= 0)
        {
            cout << "Los valores ingresados deben de ser mayores a cero" << endl;
            cout << "ingrese los valores de nuevo\n"
                 << endl;
        }
    } while (lado1 <= 0 || lado2 <= 0 || base <= 0 || altura <= 0);

    perimetro = lado1 + lado2 + base;
    area = ((base * altura) / 2);

    cout << "perimetro: " << perimetro << endl;
    cout << "area: " << area << endl;

    return 0;
}