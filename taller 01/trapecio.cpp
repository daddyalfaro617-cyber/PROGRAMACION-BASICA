#include <iostream>
using namespace std;
int main()
{
    int bmayor, bmenor, altura;
    float area;
    do
    {
        cout << ".........EJERCICIO 4 TRAPECIO..........\n"
             << endl;
        cout << "Ingrese la base mayor: ";
        cin >> bmayor;
        cout << "Ingrese la base menor: ";
        cin >> bmenor;
        cout << "Ingrese la altura: ";
        cin >> altura;
        if (bmayor <= 0 || bmenor <= 0 || altura <= 0)
        {
            cout << "Los valores ingresados deben de ser mayores a cero" << endl;
            cout << "ingrese los valores de nuevo\n"
                 << endl;
        }
    } while (bmayor <= 0 || bmenor <= 0 || altura <= 0);

    area = ((bmayor + bmenor) * altura) / 2;
    cout << "area: " << area << endl;

    return 0;
}