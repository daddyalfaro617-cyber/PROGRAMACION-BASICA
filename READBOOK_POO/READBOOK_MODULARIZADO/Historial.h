#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>
using namespace std;

class Historial {
private:
    string idUsuario;
    string isbn;
    int cantidad;
    string fechaPrestamo;
    string fechaDevolucion;

public:
    Historial();
    Historial(const string& idUsuario, const string& isbn, int cantidad, const string& fechaPrestamo, const string& fechaDevolucion);

    // Getters
    string obtenerIdUsuario() const;
    string obtenerIsbn() const;
    int obtenerCantidad() const;
    string obtenerFechaPrestamo() const;
    string obtenerFechaDevolucion() const;

    // Setters
    void establecerFechaDevolucion(const string& fecha);

    // Metodos
    void mostrar() const;
};

#endif