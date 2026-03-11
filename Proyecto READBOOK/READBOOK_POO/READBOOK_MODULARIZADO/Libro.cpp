#include "Libro.h"
#include <iostream>

Libro::Libro() : isbn(""), titulo(""), autor(""), cantidad(0) {}

Libro::Libro(const string& isbn, const string& titulo, const string& autor, int cantidad)
    : isbn(isbn), titulo(titulo), autor(autor), cantidad(cantidad) {}

string Libro::obtenerIsbn() const { return isbn; }
string Libro::obtenerTitulo() const { return titulo; }
string Libro::obtenerAutor() const { return autor; }
int Libro::obtenerCantidad() const { return cantidad; }

void Libro::establecerTitulo(const string& titulo) { this->titulo = titulo; }
void Libro::establecerAutor(const string& autor) { this->autor = autor; }
void Libro::establecerCantidad(int cantidad) { this->cantidad = cantidad; }

void Libro::mostrar() const {
    cout << isbn << " | " << titulo << " | " << autor << " | Stock: " << cantidad << endl;
}

bool Libro::disminuirStock(int cantidad) {
    if (this->cantidad >= cantidad) {
        this->cantidad -= cantidad;
        return true;
    }
    return false;
}

bool Libro::aumentarStock(int cantidad) {
    this->cantidad += cantidad;
    return true;
}