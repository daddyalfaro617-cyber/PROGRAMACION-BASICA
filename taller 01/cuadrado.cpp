#include <iostream>
#include <cmath>
using namespace std;
int main()
{

    float lado, area, perimetro, diagonal, raiz;
    do
    {
        cout << "............EJERCICIO 1 CUADRADO.............\n"
             << endl;
        cout << "ingrese el valor del lado del cuadrado: ";
        cin >> lado;
        if (lado <= 0)
        {
            cout << "El valor debe de ser mayor a cero" << endl;
            cout << "ingrese de nuevo el valor del lado\n"
                 << endl;
        }
    } while (lado <= 0);

    area = pow(lado, 2);
    perimetro = lado * 4;
    raiz = sqrt(2);
    diagonal = lado * raiz;
    cout << "area: " << area << endl;
    cout << "perimetro: " << perimetro << endl;
    cout << "diagonal: " << diagonal << endl;
    return 0;
}