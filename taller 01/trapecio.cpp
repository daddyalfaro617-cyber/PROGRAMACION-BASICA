#include <iostream>
using namespace std;
int main (){
    int bmayor, bmenor, altura;
    float area;
    cout<<".........EJERCICIO 4 TRAPECIO.........."<<endl;
    cout << "Ingrese la base mayor: ";
    cin >> bmayor;
    cout << "Ingrese la base menor: ";
    cin >> bmenor;
    cout << "Ingrese la altura: ";
    cin >> altura;

    area = ((bmayor + bmenor)*altura)/2;
    cout<<"area: "<<area<<endl;




    return 0;
}