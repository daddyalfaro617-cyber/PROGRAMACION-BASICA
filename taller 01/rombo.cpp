#include <iostream>
#include <cmath>
using namespace std;
int main()
{

    int dmayor, dmenor, area, lado, perimetro;
    do
    {
        cout << ".................EJERCICIO 3 ROMBO.............\n"
             << endl;
        cout << "Ingrese la diagonal mayor: ";
        cin >> dmayor;
        cout << "Ingrese la diagonal menor: ";
        cin >> dmenor;
        if (dmayor <= 0 || dmenor <= 0)
        {
            cout << "Los valores ingresados deben de ser mayores a cero" << endl;
            cout << "ingrese los valores de nuevo\n"
                 << endl;
        }
    } while (dmayor <= 0 || dmenor <= 0);

    area = (dmayor * dmenor) / 2;
    lado = sqrt(pow(dmayor / 2, 2) + pow(dmenor / 2, 2));
    perimetro = lado * 4;
    cout << "lado: " << lado << endl;
    cout << "area: " << area << endl;
    cout << "perimetro: " << perimetro << endl;

    return 0;
}