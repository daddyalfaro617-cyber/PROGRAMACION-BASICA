/*
 Reflexión: ¿Qué significa decir que un objeto es una “instancia” de una clase?
Una clase es como un molde o plantilla que define atributos y comportamientos y una instancia es un objeto concreto creado a partir de esa clase.
Cada instancia tiene sus propios valores de atributos, aunque comparte la misma estructura y métodos definidos en la clase.
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
    Celular(string m, string mod, int b)
    {
        marca = m;
        modelo = mod;
        bateria = 0;
        setBateria(b);
    }

    string getMarca() const
    {
        return marca;
    }

    string getModelo() const
    {
        return modelo;
    }

    int getBateria() const
    {
        return bateria;
    }

    void setMarca(const string &m)
    {
        marca = m;
    }

    void setModelo(const string &mod)
    {
        modelo = mod;
    }

    void setBateria(int b)
    {
        if (b >= 0 && b <= 100)
        {
            bateria = b;
        }
        else
        {
            cout << "Valor de bateria invalido. Debe estar entre 0 y 100." << endl;
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
    Celular cel2("Apple", "iPhone 14", -8);

    cel1.mostrarInfo();
    cel2.mostrarInfo();

    return 0;
}
