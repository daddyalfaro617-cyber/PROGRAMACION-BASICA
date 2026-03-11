#include <iostream>
#include <string>
using namespace std;

// Estructuras para usuarios y libros
struct Usuario {
    int id;
    string nombre;
    string correo;
    string rol; // "Administrador", "Bibliotecario", "Lector"
};

struct Libro {
    int id;
    string titulo;
    string autor;
    bool disponible;
};

// Funciones de gestión de usuarios
void registrarUsuario() {
    cout << ">>> Registrar nuevo usuario\n";
    // Aquí se pedirían datos y se guardarían en un arreglo
}

void iniciarSesion() {
    cout << ">>> Iniciar sesión\n";
    // Validar credenciales y asignar rol
}

void mostrarPerfilUsuario() {
    cout << ">>> Mostrar perfil del usuario\n";
    // Mostrar historial de préstamos, rol, etc.
}

// Funciones de gestión de catálogo
void agregarLibro() {
    cout << ">>> Agregar libro al catálogo\n";
    // Solo accesible para bibliotecario/administrador
}

void buscarLibro() {
    cout << ">>> Buscar libro en el catálogo\n";
    // Buscar por título, autor o ID
}

void mostrarCatalogo() {
    cout << ">>> Mostrar catálogo completo\n";
    // Listar todos los libros
}

// Funciones de préstamos y devoluciones
void prestarLibro() {
    cout << ">>> Prestar libro\n";
    // Validar disponibilidad y registrar préstamo
}

void devolverLibro() {
    cout << ">>> Devolver libro\n";
    // Marcar libro como disponible
}

void renovarPrestamo() {
    cout << ">>> Renovar préstamo\n";
    // Extender fecha si es posible
}

// Funciones de acceso digital
void leerLibroDigital() {
    cout << ">>> Leer libro digital\n";
    // Simular apertura de archivo
}

void descargarLibroDigital() {
    cout << ">>> Descargar libro digital\n";
    // Validar permisos/licencias
}

// Funciones adicionales
void reservarLibroFisico() {
    cout << ">>> Reservar libro físico\n";
    // Bloquear libro para un usuario
}

void mostrarRecomendaciones() {
    cout << ">>> Mostrar recomendaciones\n";
    // Basado en historial del usuario
}

void generarReportes() {
    cout << ">>> Generar reportes de uso\n";
    // Solo accesible para administrador
}

// Menú principal
void mostrarMenu(string rol) {
    cout << "\n===== MENU PRINCIPAL =====\n";
    cout << "1. Buscar libro\n";
    cout << "2. Mostrar catálogo\n";
    cout << "3. Prestar libro\n";
    cout << "4. Devolver libro\n";
    cout << "5. Leer libro digital\n";
    cout << "6. Descargar libro digital\n";
    cout << "7. Reservar libro físico\n";
    cout << "8. Mostrar recomendaciones\n";

    if (rol == "Bibliotecario" || rol == "Administrador") {
        cout << "9. Agregar libro\n";
    }
    if (rol == "Administrador") {
        cout << "10. Generar reportes\n";
    }
    cout << "0. Salir\n";
}

int main() {
    string rol = "Lector"; // Simulación: cambiar según el usuario
    int opcion;

    do {
        mostrarMenu(rol);
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: buscarLibro(); break;
            case 2: mostrarCatalogo(); break;
            case 3: prestarLibro(); break;
            case 4: devolverLibro(); break;
            case 5: leerLibroDigital(); break;
            case 6: descargarLibroDigital(); break;
            case 7: reservarLibroFisico(); break;
            case 8: mostrarRecomendaciones(); break;
            case 9: if (rol == "Bibliotecario" || rol == "Administrador") agregarLibro(); break;
            case 10: if (rol == "Administrador") generarReportes(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida\n"; break;
        }
    } while(opcion != 0);

    return 0;
}