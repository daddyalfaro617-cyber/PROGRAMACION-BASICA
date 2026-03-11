#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "Libro.h"
#include "Usuario.h"
#include "Prestamo.h"
#include "Historial.h"
#include <vector>
#include <string>
using namespace std;

class Biblioteca {
private:
    vector<Libro> libros;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    vector<Historial> historial;

public:
    Biblioteca();

    // Getters (acceso controlado)
    const vector<Libro>& obtenerLibros() const;
    const vector<Usuario>& obtenerUsuarios() const;
    const vector<Prestamo>& obtenerPrestamos() const;
    const vector<Historial>& obtenerHistorial() const;

    // Operaciones con libros
    int buscarLibroPorIsbn(const string& isbn) const;
    void agregarLibro(const Libro& libro);
    bool eliminarLibro(const string& isbn);
    bool actualizarLibro(const string& isbn, const string& nuevoTitulo, const string& nuevoAutor, int nuevaCantidad);
    void mostrarTodosLosLibros() const;
    void buscarLibros(const string& consulta) const;

    // Operaciones con usuarios
    int buscarUsuarioPorId(const string& id) const;
    void agregarUsuario(const Usuario& usuario);
    bool eliminarUsuario(const string& id);
    void mostrarTodosLosUsuarios() const;
    int autenticarUsuario(const string& id, const string& contrasenia) const; // retorna indice o -1

    // Operaciones con prestamos
    int buscarPrestamo(const string& idUsuario, const string& isbn) const;
    int contarPrestamosUsuario(const string& idUsuario) const;
    bool crearPrestamo(const string& idUsuario, const string& isbn, const string& fechaActual);
    bool devolverPrestamo(const string& idUsuario, const string& isbn, const string& fechaActual, int& multa);

    // Historial
    void agregarHistorial(const Historial& registro);
    void mostrarHistorialUsuario(const string& idUsuario) const;
    void mostrarTodoElHistorial() const;

    // Reportes
    void mostrarPrestamosActivos() const;

    // Persistencia
    void guardarEnArchivo() const;
    void cargarDesdeArchivo();
};

#endif