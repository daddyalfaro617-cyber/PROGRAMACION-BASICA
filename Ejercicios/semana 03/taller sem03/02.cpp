/*Contexto:
Se registran temperaturas diarias.

Problema:
1. Encontrar la temperatura máxima y el día correspondiente.
2. Encontrar la temperatura mínima y el día correspondiente.
3. Contar cuántos días superaron los 30°C.

Entrada ejemplo:
28 31 29 35 33 30 27

Salida esperada:
Máxima: 35 (día 4)
Mínima: 27 (día 7)
Días mayores a 30: 3
*/

#include <iostream>
using namespace std;

int main()
{
    int temperatura[7];
    int temcont = 0;
    int tempmin, tempmax;
    int diaMin = 1, diaMax = 1;

    for (int i = 0; i < 7; i++)
    {
        cout << "Ingrese la temperatura del dia #" << i + 1 << ": ";
        cin >> temperatura[i];
    }

    tempmax = temperatura[0];
    tempmin = temperatura[0];

    for (int i = 0; i < 7; i++)
    {
        if (temperatura[i] > tempmax)
        {
            tempmax = temperatura[i];
            diaMax = i + 1;
        }
        if (temperatura[i] < tempmin)
        {
            tempmin = temperatura[i];
            diaMin = i + 1;
        }
        if (temperatura[i] > 30)
        {
            temcont++;
        }
    }

    cout << "\nTemperatura maxima: " << tempmax<<" grados"<< " (dia " << diaMax << ")" << endl;
    cout << "Temperatura minima: " << tempmin<<" grados"<< " (dia " << diaMin << ")" << endl;
    cout << "Dias mayores a 30 grados: " << temcont << endl;

    return 0;
}