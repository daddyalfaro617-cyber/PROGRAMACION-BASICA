/*ANÁLISIS DE PROBLEMA
  1.	Identifique qué atributos y métodos deben ser comunes a todos los vehículos.
Atributos:
•	int      ID o placa: alguna forma para poder identificar a los vehículos.
•	double     Velocidad: velocidad que mantienen los vehículos.
Métodos:
•	moverse()
•	mostrarInformación()

2. Determine qué métodos deben ser obligatoriamente implementados por cada tipo de vehículo.
•	Método virtual puro: void moverse() = 0;
•	Método virtual: void mostrarInfo();
*/

#include <iostream>
#include <vector>
#include <memory> 
using namespace std;

class Vehiculo {
protected:
    int id;
    double velocidad; 

public:
    Vehiculo(int id, double vel) : id(id), velocidad(vel) {}

    virtual void moverse() const = 0;

    virtual void mostrarInfo() const {
        cout << "ID: " << id << ", Velocidad: " << velocidad << " km/h" << endl;
    }

    virtual ~Vehiculo() {
        cout << "Destructor de Vehiculo (ID: " << id << ")" << endl;
    }

    friend class Reporte;
};

class Auto : public Vehiculo {
private:
    int numeroPuertas;

public:
    Auto(int id, double vel, int puertas) : Vehiculo(id, vel), numeroPuertas(puertas) {}

    void moverse() const override {
        cout << "Auto " << id << " circulando por a " << velocidad << " km/h." << endl;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Tipo: Auto, Puertas: " << numeroPuertas << endl;
    }
};

class Drone : public Vehiculo {
private:
    double autonomiaVuelo;

public:
    Drone(int id, double vel, double autonomia) : Vehiculo(id, vel), autonomiaVuelo(autonomia) {}

    void moverse() const override {
        cout << "Drone " << id << " volando a " << velocidad << " km/h." << endl;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Tipo: Drone, Autonomia: " << autonomiaVuelo << " minutos" << endl;
    }
};

class Camion : public Vehiculo {
private:
    double capacidadCarga; 
public:
    Camion(int id, double vel, double carga) : Vehiculo(id, vel), capacidadCarga(carga) {}

    void moverse() const override {
        cout << "Camion " << id << " transportando carga a " << velocidad << " km/h." << endl;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Tipo: Camion, Capacidad de carga: " << capacidadCarga << " toneladas" << endl;
    }
};

template <typename T>
double calcularEficiencia(T consumo, T distancia) {
    return static_cast<double>(distancia) / consumo;
}

class Reporte {
public:
    static void generarReporte(const vector<Vehiculo*>& flota) {
        cout << "\n=== REPORTE DE LA FLOTA ===" << endl;
        for (const auto& v : flota) {
            cout << "Vehiculo ID: " << v->id << " - Velocidad actual: " << v->velocidad << " km/h" << endl;
        }
        cout << "================================================\n" << endl;
    }
};

int main() {
    vector<Vehiculo*> flota;

    flota.push_back(new Auto(101, 120.5, 4));
    flota.push_back(new Drone(202, 80.0, 30));
    flota.push_back(new Camion(303, 90.0, 15.5));

    for (const auto& v : flota) {
        v->moverse();
        v->mostrarInfo();
        cout << "------------------------" << endl;
    }

    double eficienciaAuto = calcularEficiencia(10.5, 500.0);
    cout << "Eficiencia del auto (distancia/consumo): " << eficienciaAuto << endl;

    int eficienciaDrone = calcularEficiencia(20, 300); 
    cout << "Eficiencia del drone (distancia/consumo): " << eficienciaDrone << endl;

    Reporte::generarReporte(flota);

    for (auto& v : flota) {
        delete v;
    }
    return 0;
}

/* REFLEXIÓN ACTIVA

1. ¿Qué ocurre si eliminamos virtual del destructor?
    Si eliminamos 'virtual' del destructor de Vehiculo, 
    al eliminar un objeto derivado mediante un puntero a Vehiculo, 
    solo se llamaría al destructor de Vehiculo y no al de la clase derivada. 
    Esto provocaría fugas de memoria y comportamiento indefinido si la clase derivada 
    gestiona recursos propios.

2. ¿Qué sucede si quitamos override?
    Si quitamos 'override', el método sigue siendo una sobrescritura 
    si coincide con la firma de la clase base, pero el compilador no verificará 
    que efectivamente estás sobrescribiendo un método virtual. Si hay un error,
    se crearía una nueva función y no se  aplicaría polimorfismo. 
    override ayuda a detectar errores en tiempo de compilación.

3. ¿Qué diferencia existe entre usar punteros y objetos directos?
    Usar punteros permite el polimorfismo dinámico: 
    la función llamada se determina en tiempo de ejecución según el tipo real del objeto. 
    Con objetos directos, el tipo se conoce en tiempo de compilación y no se puede 
    tratar de manera polimórfica. Los punteros también facilitan la gestión de memoria dinámica 
    y la inserción en contenedores heterogéneos.
*/