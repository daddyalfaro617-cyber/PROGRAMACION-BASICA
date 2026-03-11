/*Contexto: Una persona registra sus gastos diarios durante una semana.
Problema:
1. Calcular el gasto total.
2. Calcular el promedio de gastos.
3. Indicar cuántos días el gasto fue mayor al promedio.
Entrada ejemplo: 120 80 100 60 140 90 110
Salida esperada:
Total: 700
Promedio: 100
Días con gasto mayor al promedio: 3*/

#include <iostream>
using namespace std;
int main()
{

    float gasto[7];
    float promedio, gastototal;
    int diamayor=0;

    for (int i = 0; i <= 6; i++)
    {
        cout << "\nIngrese el gasto del dia #" << i+1<< ": ";
        cin >> gasto[i]; 
        gastototal += gasto[i];
        promedio = gastototal / 7;
    }
    
    for (int i=0; i<=6; i++){
        if(gasto[i] > promedio){
            diamayor++;
        }
    }
    cout << "\nGasto total: " << gastototal << endl;
    cout << "Promedio de gastos diarios: " << promedio << endl;
    cout << "Dias con gasto mayor al promedio: " << diamayor << endl;
    return 0;
} 