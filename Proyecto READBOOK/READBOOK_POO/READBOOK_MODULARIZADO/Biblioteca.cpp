#include "Biblioteca.h"
#include "Utilidades.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

Biblioteca::Biblioteca() {}

// Getters
const vector<Libro>& Biblioteca::obtenerLibros() const { return libros; }
const vector<Usuario>& Biblioteca::obtenerUsuarios() const { return usuarios; }
const vector<Prestamo>& Biblioteca::obtenerPrestamos() const { return prestamos; }
const vector<Historial>& Biblioteca::obtenerHistorial() const { return historial; }

// Libros
int Biblioteca::buscarLibroPorIsbn(const string& isbn) const {
    for (size_t i = 0; i < libros.size(); ++i)
        if (libros[i].obtenerIsbn() == isbn)
            return i;
    return -1;
}

void Biblioteca::agregarLibro(const Libro& libro) {
    libros.push_back(libro);
}

bool Biblioteca::eliminarLibro(const string& isbn) {
    int idx = buscarLibroPorIsbn(isbn);
    if (idx == -1) return false;
    // Verificar si tiene prestamos activos
    for (const auto& prestamo : prestamos)
        if (prestamo.obtenerIsbn() == isbn)
            return false;
    libros.erase(libros.begin() + idx);
    return true;
}

bool Biblioteca::actualizarLibro(const string& isbn, const string& nuevoTitulo, const string& nuevoAutor, int nuevaCantidad) {
    int idx = buscarLibroPorIsbn(isbn);
    if (idx == -1) return false;
    if (!nuevoTitulo.empty()) libros[idx].establecerTitulo(nuevoTitulo);
    if (!nuevoAutor.empty()) libros[idx].establecerAutor(nuevoAutor);
    if (nuevaCantidad >= 0) libros[idx].establecerCantidad(nuevaCantidad);
    return true;
}

void Biblioteca::mostrarTodosLosLibros() const {
    if (libros.empty()) {
        cout << "No hay libros registrados.\n";
        return;
    }
    for (const auto& libro : libros)
        libro.mostrar();
}

void Biblioteca::buscarLibros(const string& consulta) const {
    bool encontrado = false;
    for (const auto& libro : libros) {
        if (libro.obtenerIsbn() == consulta || libro.obtenerTitulo().find(consulta) != string::npos) {
            libro.mostrar();
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron resultados.\n";
}

// Usuarios
int Biblioteca::buscarUsuarioPorId(const string& id) const {
    for (size_t i = 0; i < usuarios.size(); ++i)
        if (usuarios[i].obtenerId() == id)
            return i;
    return -1;
}

void Biblioteca::agregarUsuario(const Usuario& usuario) {
    usuarios.push_back(usuario);
}

bool Biblioteca::eliminarUsuario(const string& id) {
    int idx = buscarUsuarioPorId(id);
    if (idx == -1) return false;
    // Verificar prestamos activos
    for (const auto& prestamo : prestamos)
        if (prestamo.obtenerIdUsuario() == id)
            return false;
    usuarios.erase(usuarios.begin() + idx);
    return true;
}

void Biblioteca::mostrarTodosLosUsuarios() const {
    if (usuarios.empty()) {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    for (const auto& usuario : usuarios)
        usuario.mostrar();
}

int Biblioteca::autenticarUsuario(const string& id, const string& contrasenia) const {
    int idx = buscarUsuarioPorId(id);
    if (idx != -1 && usuarios[idx].verificarContrasenia(contrasenia))
        return idx;
    return -1;
}

// Prestamos
int Biblioteca::buscarPrestamo(const string& idUsuario, const string& isbn) const {
    for (size_t i = 0; i < prestamos.size(); ++i)
        if (prestamos[i].obtenerIdUsuario() == idUsuario && prestamos[i].obtenerIsbn() == isbn)
            return i;
    return -1;
}

int Biblioteca::contarPrestamosUsuario(const string& idUsuario) const {
    int count = 0;
    for (const auto& prestamo : prestamos)
        if (prestamo.obtenerIdUsuario() == idUsuario) count++;
    return count;
}

bool Biblioteca::crearPrestamo(const string& idUsuario, const string& isbn, const string& fechaActual) {
    int usuarioIdx = buscarUsuarioPorId(idUsuario);
    int libroIdx = buscarLibroPorIsbn(isbn);
    if (usuarioIdx == -1 || libroIdx == -1) return false;
    if (libros[libroIdx].obtenerCantidad() == 0) return false;
    if (buscarPrestamo(idUsuario, isbn) != -1) return false; // ya tiene ese libro
    if (contarPrestamosUsuario(idUsuario) >= 3) return false;

    // Realizar prestamo
    libros[libroIdx].disminuirStock(1);
    prestamos.push_back(Prestamo(idUsuario, isbn, 1, fechaActual));
    return true;
}

bool Biblioteca::devolverPrestamo(const string& idUsuario, const string& isbn, const string& fechaActual, int& multa) {
    int prestamoIdx = buscarPrestamo(idUsuario, isbn);
    if (prestamoIdx == -1) return false;

    // Calcular multa
    multa = calcularMulta(prestamos[prestamoIdx].obtenerFechaPrestamo(), fechaActual);

    // Registrar en historial
    Historial hist(idUsuario, isbn, prestamos[prestamoIdx].obtenerCantidad(),
                   prestamos[prestamoIdx].obtenerFechaPrestamo(), fechaActual);
    historial.push_back(hist);

    // Devolver stock
    int libroIdx = buscarLibroPorIsbn(isbn);
    if (libroIdx != -1) libros[libroIdx].aumentarStock(prestamos[prestamoIdx].obtenerCantidad());

    // Eliminar prestamo
    prestamos.erase(prestamos.begin() + prestamoIdx);
    return true;
}

// Historial
void Biblioteca::agregarHistorial(const Historial& registro) {
    historial.push_back(registro);
}

void Biblioteca::mostrarHistorialUsuario(const string& idUsuario) const {
    bool encontrado = false;
    for (const auto& h : historial) {
        if (h.obtenerIdUsuario() == idUsuario) {
            h.mostrar();
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No hay registros en tu historial.\n";
}

void Biblioteca::mostrarTodoElHistorial() const {
    if (historial.empty()) {
        cout << "No hay registros en el historial.\n";
        return;
    }
    for (const auto& h : historial)
        h.mostrar();
}

// Reportes
void Biblioteca::mostrarPrestamosActivos() const {
    if (prestamos.empty()) {
        cout << "No hay prestamos activos.\n";
        return;
    }
    cout << "Total de prestamos: " << prestamos.size() << endl;
    for (const auto& prestamo : prestamos) {
        int userIdx = buscarUsuarioPorId(prestamo.obtenerIdUsuario());
        string userName = (userIdx != -1) ? usuarios[userIdx].obtenerNombre() : "Desconocido";
        int bookIdx = buscarLibroPorIsbn(prestamo.obtenerIsbn());
        string bookTitle = (bookIdx != -1) ? libros[bookIdx].obtenerTitulo() : "Desconocido";
        cout << "Usuario: " << userName << " (" << prestamo.obtenerIdUsuario() << ") | "
             << "Libro: " << bookTitle << " (" << prestamo.obtenerIsbn() << ") | "
             << "Cantidad: " << prestamo.obtenerCantidad() << " | Fecha: " << prestamo.obtenerFechaPrestamo() << endl;
    }
}

// Persistencia
void Biblioteca::guardarEnArchivo() const {
    ofstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt"), h("historial.txt");
    if (!u.is_open() || !l.is_open() || !p.is_open() || !h.is_open()) {
        cout << "Error al abrir archivos para guardar.\n";
        return;
    }

    // Guardar usuarios
    u << usuarios.size() << endl;
    for (const auto& user : usuarios) {
        u << user.obtenerId() << endl;
        u << user.obtenerNombre() << endl;
        u << user.obtenerContrasenia() << endl;
        u << user.esAdmin() << endl;
    }

    // Guardar libros
    l << libros.size() << endl;
    for (const auto& book : libros) {
        l << book.obtenerIsbn() << endl;
        l << book.obtenerTitulo() << endl;
        l << book.obtenerAutor() << endl;
        l << book.obtenerCantidad() << endl;
    }

    // Guardar prestamos
    p << prestamos.size() << endl;
    for (const auto& prestamo : prestamos) {
        p << prestamo.obtenerIdUsuario() << endl;
        p << prestamo.obtenerIsbn() << endl;
        p << prestamo.obtenerCantidad() << endl;
        p << prestamo.obtenerFechaPrestamo() << endl;
    }

    // Guardar historial
    h << historial.size() << endl;
    for (const auto& hist : historial) {
        h << hist.obtenerIdUsuario() << endl;
        h << hist.obtenerIsbn() << endl;
        h << hist.obtenerCantidad() << endl;
        h << hist.obtenerFechaPrestamo() << endl;
        h << hist.obtenerFechaDevolucion() << endl;
    }
}

void Biblioteca::cargarDesdeArchivo() {
    ifstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt"), h("historial.txt");

    // Cargar usuarios
    if (!u.is_open()) {
        // Crear admin por defecto
        usuarios.push_back(Usuario("ADMIN", "admin", "admin123", true));
        guardarEnArchivo();
    } else {
        int n;
        u >> n;
        u.ignore();
        for (int i = 0; i < n; ++i) {
            string id, nombre, pass;
            bool admin;
            getline(u, id);
            getline(u, nombre);
            getline(u, pass);
            u >> admin;
            u.ignore();
            if (u.fail()) break;
            usuarios.push_back(Usuario(id, nombre, pass, admin));
        }
    }

    // Cargar libros
    if (l.is_open()) {
        int n;
        l >> n;
        l.ignore();
        for (int i = 0; i < n; ++i) {
            string isbn, titulo, autor;
            int cant;
            getline(l, isbn);
            getline(l, titulo);
            getline(l, autor);
            l >> cant;
            l.ignore();
            if (l.fail()) break;
            libros.push_back(Libro(isbn, titulo, autor, cant));
        }
    }

    // Cargar prestamos
    if (p.is_open()) {
        int n;
        p >> n;
        p.ignore();
        for (int i = 0; i < n; ++i) {
            string userId, isbn, fecha;
            int cant;
            getline(p, userId);
            getline(p, isbn);
            p >> cant;
            p.ignore();
            getline(p, fecha);
            if (p.fail()) break;
            prestamos.push_back(Prestamo(userId, isbn, cant, fecha));
        }
    }

    // Cargar historial
    if (h.is_open()) {
        int n;
        h >> n;
        h.ignore();
        for (int i = 0; i < n; ++i) {
            string userId, isbn, fechaP, fechaD;
            int cant;
            getline(h, userId);
            getline(h, isbn);
            h >> cant;
            h.ignore();
            getline(h, fechaP);
            getline(h, fechaD);
            if (h.fail()) break;
            historial.push_back(Historial(userId, isbn, cant, fechaP, fechaD));
        }
    }
}