/*
Reflexión: ¿Por qué la herencia reduce repetición de código?
Porque nos permite no tener que volver a escribir de nuevo los atributos y métodos tales como:  (marca, velocidadMax, mostrarInfo())
y asi solo se definen una sola vez en la clase base Vehiculol,
y ahora solo le reasignamos los metodos y atributos a las clases hijas que en este caso serian: (moto y carro).
*/
#include <iostream>
using namespace std;

class Vehiculo
{
private:
    string marca;
    int velocidadMax;

public:
    Vehiculo(string marca, int velocidadMax)
    {
        this->marca = marca;
        this->velocidadMax = velocidadMax;
    }

    string getMarca() const { return marca; }
    int getVelocidadMax() const { return velocidadMax; }

    void setMarca(string marca) { this->marca = marca; }
    void setVelocidadMax(int velocidadMax) { this->velocidadMax = velocidadMax; }

    virtual void mostrarInfo() const
    {
        cout << "Marca: " << marca << endl;
        cout << "Velocidad Maxima: " << velocidadMax << " km/h" << endl;
    }
};

class Carro : public Vehiculo
{
private:
    int puertas;

public:
    Carro(string marca, int velocidadMax, int puertas)
        : Vehiculo(marca, velocidadMax)
    {
        this->puertas = puertas;
    }

    void setPuertas(int puertas) { this->puertas = puertas; }
    int getPuertas() const { return puertas; }

    void mostrarInfo() const override
    {
        Vehiculo::mostrarInfo();
        cout << "Puertas: " << puertas << endl;
    }
};

class Moto : public Vehiculo
{
private:
    int cilindraje;

public:
    Moto(string marca, int velocidadMax, int cilindraje)
        : Vehiculo(marca, velocidadMax)
    {
        this->cilindraje = cilindraje;
    }

    void setCilindraje(int cilindraje) { this->cilindraje = cilindraje; }
    int getCilindraje() const { return cilindraje; }

    void mostrarInfo() const override
    {
        Vehiculo::mostrarInfo();
        cout << "Cilindraje: " << cilindraje << " cc" << endl;
    }
};

int main()
{
    Carro carro1("Toyota", 180, 4);
    Moto moto1("Yamaha", 220, 600);

    cout << "Datos del Carro" << endl;
    carro1.mostrarInfo();

    cout << "\nDatos de la Moto" << endl;
    moto1.mostrarInfo();

    return 0;
}