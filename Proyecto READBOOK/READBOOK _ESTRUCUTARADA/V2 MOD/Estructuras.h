#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>
using namespace std;

struct Libro {
    string isbn;
    string titulo;
    string autor;
    int cantidad;
};

struct Usuario {
    string id;
    string nombre;
    string pass;
    bool admin;
};

struct Prestamo {
    string idUsuario, isbn;
    int cantidad;
    string fechaPrestamo; 
};

struct Historial {
    string idUsuario, isbn;
    int cantidad;
    string fechaPrestamo;
    string fechaDevolucion;
};

#endif