/*
Reflexión: ¿Qué pasaría si no usas this-> cuando el nombre del parámetro y el atributo son iguales?
sin this-> el atributo nunca se actualiza, y tu objeto no reflejará los cambios esperados.
*/

#include <iostream>
using namespace std;

class Celular
{
private:
    string marca;
    string modelo;
    int bateria;

public:

    Celular(string marca, string modelo, int bateria)
    {
        this->marca = marca;
        this->modelo = modelo;
        this->bateria = 0; 
        setBateria(bateria);
    }

    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    int getBateria() const { return bateria; }

    void setMarca(string marca)
    {
        this->marca = marca;
    }

    void setModelo(string modelo)
    {
        this->modelo = modelo;
    }

    void setBateria(int bateria)
    {
        if (bateria >= 0 && bateria <= 100)
        {
            this->bateria = bateria;
        }
        else
        {
            cout << "Valor de bateria invalido. Debe estar entre 0 y 100." << endl;
            this->bateria = 0; 
        }
    }

    void mostrarInfo() const
    {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Bateria: " << bateria << "%" << endl;
        cout << "-------------------------" << endl;
    }
};

int main()
{
    Celular cel1("Samsung", "Galaxy S23", 85);
    Celular cel2("Apple", "iPhone 14", 180); 

    cel1.mostrarInfo();
    cel2.mostrarInfo();

    return 0;
}