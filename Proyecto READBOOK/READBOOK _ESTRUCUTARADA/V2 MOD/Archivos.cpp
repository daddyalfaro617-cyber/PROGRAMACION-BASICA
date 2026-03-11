#include "archivos.h"
#include "globales.h"
#include "utilidades.h"
#include <fstream>
using namespace std;

void guardar() {
    ofstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt"), h("historial.txt");
    if (!u.is_open() || !l.is_open() || !p.is_open() || !h.is_open()) {
        cout << "Error al abrir archivos para guardar.\n";
        return;
    }

    // Guardar usuarios
    u << totalUsuarios << endl;
    for (int i = 0; i < totalUsuarios; i++) {
        u << usuarios[i].id << endl;
        u << usuarios[i].nombre << endl;
        u << usuarios[i].pass << endl;
        u << usuarios[i].admin << endl;
    }

    // Guardar libros
    l << totalLibros << endl;
    for (int i = 0; i < totalLibros; i++) {
        l << libros[i].isbn << endl;
        l << libros[i].titulo << endl;
        l << libros[i].autor << endl;
        l << libros[i].cantidad << endl;
    }

    // Guardar préstamos
    p << totalPrestamos << endl;
    for (int i = 0; i < totalPrestamos; i++) {
        p << prestamos[i].idUsuario << endl;
        p << prestamos[i].isbn << endl;
        p << prestamos[i].cantidad << endl;
        p << prestamos[i].fechaPrestamo << endl;
    }

    // Guardar historial
    h << totalHistorial << endl;
    for (int i = 0; i < totalHistorial; i++) {
        h << historial[i].idUsuario << endl;
        h << historial[i].isbn << endl;
        h << historial[i].cantidad << endl;
        h << historial[i].fechaPrestamo << endl;
        h << historial[i].fechaDevolucion << endl;
    }
}

void cargar() {
    ifstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt"), h("historial.txt");

    // Cargar usuarios 
    if (!u.is_open()) {
        Usuario admin = {"ADMIN", "admin", "admin123", true};
        agregar(usuarios, totalUsuarios, admin);
        guardar();
    } else {
        int n;
        u >> n;
        u.ignore();
        for (int i = 0; i < n; i++) {
            Usuario usr;
            getline(u, usr.id);
            getline(u, usr.nombre);
            getline(u, usr.pass);
            u >> usr.admin;
            u.ignore();
            if (u.fail()) break;
            agregar(usuarios, totalUsuarios, usr);
        }
    }

    // Cargar libros 
    if (l.is_open()) {
        int n;
        l >> n;
        l.ignore();
        for (int i = 0; i < n; i++) {
            Libro lib;
            getline(l, lib.isbn);
            getline(l, lib.titulo);
            getline(l, lib.autor);
            l >> lib.cantidad;
            l.ignore();
            if (l.fail()) break;
            agregar(libros, totalLibros, lib);
        }
    }

    // Cargar préstamos 
    if (p.is_open()) {
        int n;
        p >> n;
        p.ignore();
        for (int i = 0; i < n; i++) {
            Prestamo pre;
            getline(p, pre.idUsuario);
            getline(p, pre.isbn);
            p >> pre.cantidad;
            p.ignore();
            getline(p, pre.fechaPrestamo);
            if (p.fail()) break;
            agregar(prestamos, totalPrestamos, pre);
        }
    }

    // Cargar historial
    if (h.is_open()) {
        int n;
        h >> n;
        h.ignore();
        for (int i = 0; i < n; i++) {
            Historial hist;
            getline(h, hist.idUsuario);
            getline(h, hist.isbn);
            h >> hist.cantidad;
            h.ignore();
            getline(h, hist.fechaPrestamo);
            getline(h, hist.fechaDevolucion);
            if (h.fail()) break;
            agregar(historial, totalHistorial, hist);
        }
    }
}