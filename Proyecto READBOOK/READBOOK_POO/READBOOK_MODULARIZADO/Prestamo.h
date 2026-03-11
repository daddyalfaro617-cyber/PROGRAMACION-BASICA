#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
using namespace std;

class Prestamo {
private:
    string idUsuario;
    string isbn;
    int cantidad;
    string fechaPrestamo;

public:
    Prestamo();
    Prestamo(const string& idUsuario, const string& isbn, int cantidad, const string& fechaPrestamo);

    // Getters
    string obtenerIdUsuario() const;
    string obtenerIsbn() const;
    int obtenerCantidad() const;
    string obtenerFechaPrestamo() const;

    // Setters
    void establecerFechaPrestamo(const string& fecha);

    // Metodos
    void mostrar() const;
};

#endif