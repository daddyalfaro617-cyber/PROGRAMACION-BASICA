/*
Reflexión: ¿Qué problema evita el encapsulamiento?
El encapsulamiento protege los atributos de una clase al hacerlos privados y permitir el acceso solo mediante métodos públicos (getters y setters).
*/
#include <iostream>
using namespace std;

class Celular
{

public:
    string marca;
    string modelo;
    int bateria;

    void mostrarInfo()
    {
        cout << "la marca es: " << marca << endl;
        cout << "el modelo es: " << modelo << endl;
        cout << "la capacidad de la bateria es de: " << bateria << " Ah"<<endl;
    }
};
int main()
{

    Celular cel1;
    cel1.marca = "Xiaomy";
    cel1.modelo = "15 pro 5G";
    cel1.bateria = 5500;

    cel1.mostrarInfo();

    Celular cel2;
    cel2.marca = "Samsung";
    cel2.modelo = "A15";
    cel2.bateria = 5000;

    cel2.mostrarInfo();

    return 0;
}