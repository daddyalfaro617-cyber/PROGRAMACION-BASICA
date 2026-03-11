#ifndef LIBRO_H
#define LIBRO_H

#include <string>
using namespace std;

class Libro {
private:
    string isbn;
    string titulo;
    string autor;
    int cantidad;

public:
    Libro();
    Libro(const string& isbn, const string& titulo, const string& autor, int cantidad);

    // Getters
    string obtenerIsbn() const;
    string obtenerTitulo() const;
    string obtenerAutor() const;
    int obtenerCantidad() const;

    // Setters
    void establecerTitulo(const string& titulo);
    void establecerAutor(const string& autor);
    void establecerCantidad(int cantidad);

    // Metodos
    void mostrar() const;
    bool disminuirStock(int cantidad = 1);
    bool aumentarStock(int cantidad = 1);
};

#endif