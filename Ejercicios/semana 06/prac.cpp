#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehiculo // clase Base
{
private: // Atributos
    string marca;
    string modelo;
    int anio;
    double costoBase;

public:                                                                                                              // Métodos
    Vehiculo(string mar, string mode, int a, double costb) : 
    marca(mar), modelo(mode), anio(a), costoBase(costb) {}; // Inicializador de Constructor
    void mostrarInfo()
    {
        cout << "=====DATOS DEL VEHICULO:=====\n"
             << endl;
        cout << "Marca: " << marca << " Modelo: " << modelo << " Año: " << anio << endl;
        cout << "Costo Base: " << costoBase << endl;
    }
    double getcostoBase() const { return costoBase; } // Método para obtener el costo base del vehículo
    virtual double calcularCostoFinal() const = 0;    // Método virtual puro para calcular el costo final del vehículo
};

class Auto : public Vehiculo
{
private:
    int numPuertas;

public:
    Auto(string mar, string mode, int a, double costb, int numP) : Vehiculo(mar, mode, a, costb), numPuertas(numP) {};
    
    double calcularCostoFinal() const override
    {
        return getcostoBase() + (numPuertas * 1000.0);
    }
};

class Camion : public Vehiculo
{
private:
    double capacidadCarga;

public:
    Camion(string mar, string mode, int a, double costb, double carga) : Vehiculo(mar, mode, a, costb), capacidadCarga(carga) {};

    double calcularCostoFinal() const override
    {
        return getcostoBase() + (capacidadCarga * 50.0);
    }
};

class Motocicleta : public Vehiculo
{
private:
    double cilindrada;

public:
    Motocicleta(string mar, string mode, int a, double costb, double cl) : Vehiculo(mar, mode, a, costb), cilindrada(cl) {};

    double calcularCostoFinal() const override
    {
        return getcostoBase() + (cilindrada * 20.0);
    }
};

class GestordeVentas

{
}; // clase para gestionar las ventas de los vehículos

int main()
{

    return 0;
}