#include <iostream> 
using namespace std;
int main () {
  
    int lado1, lado2, base, altura, perimetro;
    float area;
    cout<<"..........EJERCICIO 5 TRIANGULO.........."<<endl;
    cout<<"ingrese el lado 1 : ";
    cin>>lado1;
    cout<<"ingrese el lado 2: ";
    cin>>lado2;
    cout<<"ingrese la base: ";
    cin>>base;
    cout<<"ingrese la altura: ";
    cin>>altura;

    perimetro=lado1+lado2+base;
    area=((base*altura)/2);

    cout<<"perimetro: "<<perimetro<<endl;
    cout<<"area: "<<area<<endl;

    return 0;
}