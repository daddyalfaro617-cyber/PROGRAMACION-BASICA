#include <iostream>
#include <cmath>
using namespace std;
int main()
{

    float lado, area, perimetro, diagonal, raiz;

    cout << "............EJERCICIO 1 CUADRADO............. " << endl;
    cin >> lado;
    area = lado * lado;
    perimetro = lado * 4;
    raiz = sqrt(2);
    diagonal = lado * raiz;
    cout << "area:" << area << endl;
    cout << "perimetro: " << perimetro << endl;
    cout << "diagonal: " << diagonal << endl;
    return 0;
}