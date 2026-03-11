#include "Historial.h"
#include <iostream>

Historial::Historial() : idUsuario(""), isbn(""), cantidad(0), fechaPrestamo(""), fechaDevolucion("") {}

Historial::Historial(const string& idUsuario, const string& isbn, int cantidad, const string& fechaPrestamo, const string& fechaDevolucion)
    : idUsuario(idUsuario), isbn(isbn), cantidad(cantidad), fechaPrestamo(fechaPrestamo), fechaDevolucion(fechaDevolucion) {}

string Historial::obtenerIdUsuario() const { return idUsuario; }
string Historial::obtenerIsbn() const { return isbn; }
int Historial::obtenerCantidad() const { return cantidad; }
string Historial::obtenerFechaPrestamo() const { return fechaPrestamo; }
string Historial::obtenerFechaDevolucion() const { return fechaDevolucion; }

void Historial::establecerFechaDevolucion(const string& fecha) { fechaDevolucion = fecha; }

void Historial::mostrar() const {
    cout << "Usuario: " << idUsuario << " | ISBN: " << isbn
         << " | Cantidad: " << cantidad
         << " | Prestamo: " << fechaPrestamo
         << " | Devolucion: " << fechaDevolucion << endl;
}