#include <iostream>
#include <cmath>
using namespace std;
int main (){
    int base , altura, area, perimetro, diagonal;
    cout <<"............EJERCICIO 2 RECTANGULO..........."<<endl;
    cin >>base>>altura;
        area=base*altura;
        perimetro=(base * altura)*2;
        diagonal = sqrt ((base*base)+(altura*altura));
        cout<<"area: "<<area<<endl;
        cout<<"perimetro: "<<perimetro<<endl;           
        cout<<"diagonal: "<<diagonal<<endl;

    return 0;
}