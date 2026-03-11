/*
Reflexión: ¿Qué ventaja da el polimorfismo?
Puedes escribir funciones que trabajen con objetos de una clase padre y automáticamente funcionarán con cualquier objeto de una clase hija (Herencia).
Añadir nuevas funcionalidades (nuevas clases) es fácil y no requiere modificar el código existente.
El código es más limpio, con menos condicionales, y más fácil de entender y depurar.
Puedes crear una interfaz o clase abstracta común y reutilizar el código que la utiliza para múltiples implementaciones concretas.
*/
#include <iostream>
using namespace std;

class Persona
{
private:
    string nombre;
    int edad;

public:
    Persona(string nombre, int edad)
    {
        this->nombre = nombre;
        setEdad(edad);
    }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setEdad(int edad)
    {
        if (edad >= 0)
            this->edad = edad;
        else
        {
            cout << "Edad inválida. Se asigna 0." << endl;
            this->edad = 0;
        }
    }

    void mostrar() const
    {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
    }

    virtual void rol() const
    {
        cout << "Soy una persona" << endl;
    }
};

class Estudiante : public Persona
{
private:
    string carrera;

public:
    Estudiante(string nombre, int edad, string carrera)
        : Persona(nombre, edad)
    {
        this->carrera = carrera;
    }

    void mostrar() const
    {
        Persona::mostrar();
        cout << "Carrera: " << carrera << endl;
    }

    void estudiar() const
    {
        cout << getNombre() << " está estudiando " << carrera << "." << endl;
    }

    void rol() const override
    {
        cout << "Soy estudiante" << endl;
    }
};

class Profesor : public Persona
{
private:
    string materia;

public:
    Profesor(string nombre, int edad, string materia)
        : Persona(nombre, edad)
    {
        this->materia = materia;
    }

    void mostrar() const
    {
        Persona::mostrar();
        cout << "Materia: " << materia << endl;
    }

    void ensenar() const
    {
        cout << getNombre() << " está enseñando " << materia << "." << endl;
    }

    void rol() const override
    {
        cout << "Soy profesor" << endl;
    }
};

int main()
{
    Persona *personas[2];

    personas[0] = new Estudiante("Carlos", 20, "Ingeniería de Sistemas");
    personas[1] = new Profesor("Ana", 45, "Matemáticas");

    for (int i = 0; i < 2; i++)
    {
        personas[i]->rol();
    }

    for (int i = 0; i < 2; i++)
    {
        delete personas[i];
    }

    return 0;
}