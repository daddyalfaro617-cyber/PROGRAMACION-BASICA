#include "Prestamo.h"
#include <iostream>

Prestamo::Prestamo() : idUsuario(""), isbn(""), cantidad(0), fechaPrestamo("") {}

Prestamo::Prestamo(const string& idUsuario, const string& isbn, int cantidad, const string& fechaPrestamo)
    : idUsuario(idUsuario), isbn(isbn), cantidad(cantidad), fechaPrestamo(fechaPrestamo) {}

string Prestamo::obtenerIdUsuario() const { return idUsuario; }
string Prestamo::obtenerIsbn() const { return isbn; }
int Prestamo::obtenerCantidad() const { return cantidad; }
string Prestamo::obtenerFechaPrestamo() const { return fechaPrestamo; }

void Prestamo::establecerFechaPrestamo(const string& fecha) { fechaPrestamo = fecha; }

void Prestamo::mostrar() const {
    cout << "Usuario: " << idUsuario << " | ISBN: " << isbn << " | Cantidad: " << cantidad << " | Fecha: " << fechaPrestamo << endl;
}