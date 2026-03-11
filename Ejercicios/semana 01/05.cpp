//Calcula el promedio de 3 números.

#include <iostream>
using namespace std;
int main(){
    int a, b,c, promedio;
    cout << "ingrese el primer numero: ";
    cin >> a;   
    cout << "ingrese el segundo numero: ";
    cin >> b;
    cout<<"ingrese el tercer numero: ";
    cin>>c;
    promedio = (a+b+c)/3;
    cout<< "el promedio es: "<<promedio<<endl;



  return 0;  
}