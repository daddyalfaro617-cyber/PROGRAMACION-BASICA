//Compara dos números e imprime el resultado.
#include <iostream>
using namespace std;
int main(){

int a,b,mayor, menor;
cout<<"Ingrese el primer numero: ";
cin>>a;
cout<<"Ingrese el segundo numero: ";
cin>>b;
if (a>b){
  mayor=a;
  menor=b;
  cout<<"El numero mayor es: "<<mayor<<endl;
  cout<<"El numero menor es: "<<menor<<endl;
}
else if(b>a){
  mayor=b;
  menor=a;
  cout<<"El numero mayor es: "<<mayor<<endl;
  cout<<"El numero menor es: "<<menor<<endl;
}

else if (a==b){
  cout<<"Los numeros son iguales"<<endl;
}

  return 0;  
}