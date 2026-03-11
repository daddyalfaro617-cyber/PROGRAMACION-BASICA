#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehiculo {
protected:
    string marca;
    string modelo;
    int anio;
    double costoBase;

public:
    Vehiculo(string mar, string mode, int a, double costb)
        : marca(mar), modelo(mode), anio(a), costoBase(costb) {}

    virtual void mostrarInfo() {
        cout << "Marca: " << marca << " Modelo: " << modelo << " Año: " << anio << endl;
        cout << "Costo Base: " << costoBase << endl;
    }

    virtual double calcularCostoFinal() = 0; // método abstracto
};

// Clase derivada Auto
class Auto : public Vehiculo {
private:
    int numPuertas;

public:
    Auto(string mar, string mode, int a, double costb, int puertas)
        : Vehiculo(mar, mode, a, costb), numPuertas(puertas) {}

    double calcularCostoFinal() override {
        return costoBase + (numPuertas * 100);
    }
};

// Clase derivada Camion
class Camion : public Vehiculo {
private:
    double capacidadCarga;

public:
    Camion(string mar, string mode, int a, double costb, double carga)
        : Vehiculo(mar, mode, a, costb), capacidadCarga(carga) {}

    double calcularCostoFinal() override {
        return costoBase + (capacidadCarga * 50);
    }
};

// Clase derivada Motocicleta
class Motocicleta : public Vehiculo {
private:
    double cilindrada;

public:
    Motocicleta(string mar, string mode, int a, double costb, double cil)
        : Vehiculo(mar, mode, a, costb), cilindrada(cil) {}

    double calcularCostoFinal() override {
        return costoBase + (cilindrada * 20);
    }
};

// Clase GestorVehiculos
class GestorVehiculos {
private:
    vector<Vehiculo*> lista;

public:
    void agregarVehiculo(Vehiculo* v) {
        lista.push_back(v);
    }

    void mostrarTodos() {
        for (auto v : lista) {
            v->mostrarInfo();
            cout << "Costo Final: " << v->calcularCostoFinal() << "\n\n";
        }
    }

    double calcularCostoTotal() {
        double total = 0;
        for (auto v : lista) {
            total += v->calcularCostoFinal();
        }
        return total;
    }
};

int main() {
    GestorVehiculos gestor;

    Auto a1("Toyota", "Corolla", 2020, 10000, 4);
    Camion c1("Volvo", "FH", 2018, 20000, 15);
    Motocicleta m1("Honda", "CBR", 2022, 8000, 600);

    gestor.agregarVehiculo(&a1);
    gestor.agregarVehiculo(&c1);
    gestor.agregarVehiculo(&m1);

    gestor.mostrarTodos();
    cout << "Costo Total de Operación: " << gestor.calcularCostoTotal() << endl;

    return 0;
}