#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
using namespace std;

// Búsquedas
int buscarLibro(const string& isbn);
int buscarPrestamo(const string& isbn, int idUsuarioIdx);
int buscarUsuarioPorId(const string& id);

// Funciones principales
void mostrarCatalogo();
void buscarLibroMenu();
void registrar();
bool login();
void agregarLibro();
void prestar();
void devolver();

// Funciones de perfil y usuario
void mostrarPerfil();
void cambiarPassword();
void listarUsuarios();
void eliminarUsuario();
void mostrarHistorialUsuario();
void mostrarHistorialCompleto();

// Funciones de libros (admin)
void editarLibro();
void eliminarLibro();

// Reportes
void reportePrestamos();



// Menús
void menuUsuario();
void menuAdmin();

#endif