#include <iostream>
#include <cmath>
using namespace std;
int main()
{

    int dmayor, dmenor, area, lado, perimetro;
    cout << ".................EJERCICIO 3 ROMBO............." << endl;
    cout << "Ingrese la diagonal mayor: ";
    cin >> dmayor;
    cout << "Ingrese la diagonal menor: ";
    cin >> dmenor;

    area = (dmayor * dmenor) / 2;
    lado = sqrt(pow(dmayor / 2, 2) + pow(dmenor / 2, 2));
    perimetro = lado * 4;
    cout << "lado: " << lado << endl;
    cout << "area: " << area << endl;
    cout << "perimetro: " << perimetro << endl;

    return 0;
}