/*
Reflexión: ¿Qué atributos y métodos comparten Estudiante y Profesor gracias a Persona?
Tanto Estudiante como Profesor heredan de la clase padre o base Persona, lo que significa que comparten los atributos y métodos definidos allí.
Siendo asi que heredan:
 -nombre (string)
 -edad (int)
*/
#include <iostream>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;

public:
    
    Persona(string nombre, int edad) {
        this->nombre = nombre;
        setEdad(edad); 
    }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }

    void setNombre(string nombre) { this->nombre = nombre; }
    void setEdad(int edad) {
        if (edad >= 0) {
            this->edad = edad;
        } else {
            cout << "Edad invalida. Se asigna 0." << endl;
            this->edad = 0;
        }
    }

    void mostrar() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
    }
};

class Estudiante : public Persona {
private:
    string carrera;

public:
    Estudiante(string nombre, int edad, string carrera)
        : Persona(nombre, edad) {
        this->carrera = carrera;
    }

    void setCarrera(string carrera) { this->carrera = carrera; }
    string getCarrera() const { return carrera; }

    void estudiar() const {
        cout << getNombre() << " esta estudiando la carrera de " << carrera << "." << endl;
    }

    void mostrar() const {
        Persona::mostrar();
        cout << "Carrera: " << carrera << endl;
    }
};

class Profesor : public Persona {
private:
    string materia;

public:
    Profesor(string nombre, int edad, string materia)
        : Persona(nombre, edad) {
        this->materia = materia;
    }

    void setMateria(string materia) { this->materia = materia; }
    string getMateria() const { return materia; }

    void ensenar() const {
        cout << getNombre() << " esta enseniando la materia de " << materia << "." << endl;
    }

    void mostrar() const {
        Persona::mostrar();
        cout << "Materia: " << materia << endl;
    }
};

int main() {
    Estudiante est1("Carlos", 20, "Ingenieria de Sistemas");
    Profesor prof1("Ana", 45, "Matematicas");

    cout << "Datos del Estudiante" << endl;
    est1.mostrar();
    est1.estudiar();

    cout << "\nDatos del Profesor" << endl;
    prof1.mostrar();
    prof1.ensenar();

    return 0;
}