/*
Reflexión: ¿Por qué es útil tener constructores sobrecargados?
Su utilidad es que te dan libertad, porque te permiten crear un mismo tipo de objeto de diferentes maneras,
según el contexto y la información disponible.
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
    Celular()
    {
        this->marca = "Desconocida";
        this->modelo = "Generico";
        this->bateria = 100;
    }

    Celular(string marca, string modelo)
    {
        this->marca = marca;
        this->modelo = modelo;
        this->bateria = 100;
    }

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

    void setMarca(string marca) { this->marca = marca; }
    void setModelo(string modelo) { this->modelo = modelo; }
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

    Celular cel1;
    Celular cel2("Xiaomi", "Redmi Note 13");
    Celular cel3("Samsung", "Galaxy S23", 85);

    cel1.mostrarInfo();
    cel2.mostrarInfo();
    cel3.mostrarInfo();

    return 0;
}