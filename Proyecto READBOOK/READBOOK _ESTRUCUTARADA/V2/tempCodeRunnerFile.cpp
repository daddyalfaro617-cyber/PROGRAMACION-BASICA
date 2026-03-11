#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <cstdlib> 

using namespace std;

// ====================== ESTRUCTURAS ======================
struct Libro {
    string isbn, titulo, autor;
    int cantidad;
};

struct Usuario {
    string id, nombre, pass;
    bool admin;
};

struct Prestamo {
    string idUsuario, isbn;
    int cantidad;
};

// ====================== VARIABLES GLOBALES ======================
Libro *libros = nullptr;
int totalLibros = 0;
Usuario *usuarios = nullptr;
int totalUsuarios = 0;
Prestamo *prestamos = nullptr;
int totalPrestamos = 0;
int usuarioActual = -1; // índice del usuario logueado

// ====================== UTILIDADES ======================
void limpiarPantalla() {
    // Detecta el sistema operativo y ejecuta el comando correspondiente
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEntero(int min, int max) {
    int op;
    while (true) {
        if (cin >> op && op >= min && op <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return op;
        }
        cout << "Opcion invalida. Intente nuevamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Lee una cadena no vacía y con longitud máxima controlada
string leerString(const string& mensaje, int maxLong = 50) {
    string entrada;
    do {
        cout << mensaje;
        getline(cin, entrada);
        if (entrada.empty()) {
            cout << "El campo no puede estar vacio.\n";
        } else if (entrada.length() > static_cast<size_t>(maxLong)) {
            cout << "El campo no puede exceder " << maxLong << " caracteres.\n";
        }
    } while (entrada.empty() || entrada.length() > static_cast<size_t>(maxLong));
    return entrada;
}

// Valida formato básico de ISBN (solo dígitos y guiones, entre 10 y 13 dígitos)
bool validarISBN(const string& isbn) {
    string limpio;
    for (char c : isbn) {
        if (isdigit(c))
            limpio += c;
        else if (c != '-')
            return false; // carácter no válido
    }
    return limpio.length() >= 10 && limpio.length() <= 13;
}

void encabezado(const string& titulo) {
    limpiarPantalla(); // Limpia la pantalla antes de mostrar el encabezado
    cout << "\n====================================\n";
    cout <<"||          " << titulo <<"       ||" << endl;
    cout << "====================================\n";
}

// Plantilla para agregar un elemento a un arreglo dinámico
template <typename T>
void agregar(T *&arr, int &total, const T &dato) {
    T *nuevo = new T[total + 1];
    for (int i = 0; i < total; i++)
        nuevo[i] = arr[i];
    nuevo[total] = dato;
    delete[] arr;
    arr = nuevo;
    total++;
}

// ====================== ARCHIVOS ======================
void guardar() {
    ofstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt");
    if (!u.is_open() || !l.is_open() || !p.is_open()) {
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
    }
}

void cargar() {
    ifstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt");

    // Cargar usuarios
    if (!u.is_open()) {
        // Si no existe, crear admin por defecto
        Usuario admin = {"ADMIN", "admin", "admin123", true};
        agregar(usuarios, totalUsuarios, admin);
        guardar(); // guarda el admin inicial
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
            if (p.fail()) break;
            agregar(prestamos, totalPrestamos, pre);
        }
    }
}

// ====================== BÚSQUEDAS ======================
int buscarLibro(const string& isbn) {
    for (int i = 0; i < totalLibros; i++)
        if (libros[i].isbn == isbn)
            return i;
    return -1;
}

int buscarPrestamo(const string& isbn, int idUsuarioIdx) {
    if (idUsuarioIdx < 0 || idUsuarioIdx >= totalUsuarios) return -1;
    const string& idUsr = usuarios[idUsuarioIdx].id;
    for (int i = 0; i < totalPrestamos; i++)
        if (prestamos[i].idUsuario == idUsr && prestamos[i].isbn == isbn)
            return i;
    return -1;
}

// ====================== FUNCIONES PRINCIPALES ======================
void mostrarCatalogo() {
    encabezado("CATALOGO DE LIBROS");
    if (totalLibros == 0) {
        cout << "No hay libros registrados.\n";
        pausa();
        return;
    }

    for (int i = 0; i < totalLibros; i++)
        cout << libros[i].isbn << " | " << libros[i].titulo << " | " << libros[i].autor << " | Stock: " << libros[i].cantidad << endl;
    pausa();
}

void buscarLibroMenu() {
    encabezado("BUSCAR LIBRO");
    string dato = leerString("Ingrese titulo o ISBN: ", 100);

    bool encontrado = false;
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].isbn == dato ||
            libros[i].titulo.find(dato) != string::npos) {
            cout << "\n" << libros[i].isbn << " | " << libros[i].titulo << " | " << libros[i].autor << " | Stock: " << libros[i].cantidad << endl;
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No se encontraron resultados.\n";
    pausa();
}

void registrar() {
    encabezado("REGISTRO DE USUARIO");
    Usuario u;
    u.id = "U" + to_string(totalUsuarios + 1);
    u.nombre = leerString("Nombre: ");
    u.pass = leerString("Contrasena: ");
    u.admin = false;
    agregar(usuarios, totalUsuarios, u);
    guardar();
    cout << "Usuario registrado con ID: " << u.id << endl;
    pausa();
}

bool login() {
    encabezado("INICIAR SESION");
    int intentos = 3;
    while (intentos-- > 0) {
        string id, pass;
        cout << "ID: ";
        getline(cin, id);
        cout << "Contrasena: ";
        getline(cin, pass);

        for (int i = 0; i < totalUsuarios; i++) {
            if (usuarios[i].id == id && usuarios[i].pass == pass) {
                usuarioActual = i;
                return true;
            }
        }
        cout << "Credenciales incorrectas. Intentos restantes: " << intentos << endl;
    }
    cout << "Demasiados intentos fallidos.\n";
    pausa();
    return false;
}

void agregarLibro() {
    encabezado("AGREGAR LIBRO");
    Libro l;
    do {
        l.isbn = leerString("ISBN: ", 20);
        if (!validarISBN(l.isbn))
            cout << "ISBN invalido. Debe contener solo digitos y guiones, y tener entre 10 y 13 digitos.\n";
    } while (!validarISBN(l.isbn));

    if (buscarLibro(l.isbn) != -1) {
        cout << "El ISBN ya existe.\n";
        pausa();
        return;
    }

    l.titulo = leerString("Titulo: ");
    l.autor = leerString("Autor: ");
    cout << "Cantidad: ";
    l.cantidad = leerEntero(0, 100000);
    agregar(libros, totalLibros, l);
    guardar();
    cout << "Libro agregado correctamente.\n";
    pausa();
}

void prestar() {
    encabezado("PRESTAR LIBRO");
    string isbn = leerString("ISBN: ", 20);
    if (!validarISBN(isbn)) {
        cout << "ISBN invalido.\n";
        pausa();
        return;
    }

    int pos = buscarLibro(isbn);
    if (pos == -1) {
        cout << "Libro no encontrado.\n";
        pausa();
        return;
    }
    if (libros[pos].cantidad == 0) {
        cout << "No hay stock disponible.\n";
        pausa();
        return;
    }

    cout << "Cantidad (max " << libros[pos].cantidad << "): ";
    int c = leerEntero(1, libros[pos].cantidad);

    int pr = buscarPrestamo(isbn, usuarioActual);
    if (pr != -1) {
        prestamos[pr].cantidad += c;
    } else {
        Prestamo nuevo = {usuarios[usuarioActual].id, isbn, c};
        agregar(prestamos, totalPrestamos, nuevo);
    }

    libros[pos].cantidad -= c;
    guardar();
    cout << "Prestamo registrado.\n";
    pausa();
}

void devolver() {
    encabezado("DEVOLVER LIBRO");
    string isbn = leerString("ISBN: ", 20);
    if (!validarISBN(isbn)) {
        cout << "ISBN invalido.\n";
        pausa();
        return;
    }

    int pr = buscarPrestamo(isbn, usuarioActual);
    if (pr == -1) {
        cout << "No tienes este libro prestado.\n";
        pausa();
        return;
    }

    cout << "Cantidad a devolver (max " << prestamos[pr].cantidad << "): ";
    int c = leerEntero(1, prestamos[pr].cantidad);

    int pos = buscarLibro(isbn); // debe existir porque hay préstamo
    libros[pos].cantidad += c;
    prestamos[pr].cantidad -= c;

    if (prestamos[pr].cantidad == 0) {
        // Eliminar el préstamo
        Prestamo *temp = new Prestamo[totalPrestamos - 1];
        for (int i = 0, j = 0; i < totalPrestamos; i++) {
            if (i != pr)
                temp[j++] = prestamos[i];
        }
        delete[] prestamos;
        prestamos = temp;
        totalPrestamos--;
    }

    guardar();
    cout << "Devolucion realizada.\n";
    pausa();
}

// ====================== MENUS ======================
void menuUsuario() {
    int op;
    do {
        encabezado("MENU USUARIO");
        cout << "||    1. Ver catalogo              ||\n";
        cout << "||    2. Buscar libro              ||\n";
        cout << "||    3. Prestar libro             ||\n";
        cout << "||    4. Devolver libro            ||\n";
        cout << "||    5. Cerrar sesion             ||\n";
        cout << "=====================================\n";
        op = leerEntero(1, 5);

        switch (op) {
            case 1: mostrarCatalogo(); break;
            case 2: buscarLibroMenu(); break;
            case 3: prestar(); break;
            case 4: devolver(); break;
        }
    } while (op != 5);
    usuarioActual = -1;
}

void menuAdmin() {
    int op;
    do {
        encabezado("MENU ADMINISTRADOR");
        cout << "||    1. Agregar libro               ||\n";
        cout << "||    2. Ver catalogo                ||\n";
        cout << "||    3. Buscar libro                ||\n";
        cout << "||    4. Cerrar sesion               ||\n";
        cout << "=======================================\n";
        cout << "Seleccione una opcion: ";
        op = leerEntero(1, 4);

        switch (op) {
            case 1: agregarLibro(); break;
            case 2: mostrarCatalogo(); break;
            case 3: buscarLibroMenu(); break;
        }
    } while (op != 4);
    usuarioActual = -1;
}

// ====================== MAIN ======================
int main() {
    cargar();
    int op;

    do {
        encabezado("SISTEMA READBOOK");
        cout << "||     1. Ver catalogo             ||\n";
        cout << "||     2. Buscar libro             ||\n";
        cout << "||     3. Registrarse              ||\n";
        cout << "||     4. Iniciar sesion           ||\n";
        cout << "||     5. Salir                    ||\n";
        cout << "=====================================\n";
        cout << "Seleccione una opcion: ";
        op = leerEntero(1, 5);

        switch (op) {
            case 1: mostrarCatalogo(); break;
            case 2: buscarLibroMenu(); break;
            case 3: registrar(); break;
            case 4:
                if (login()) {
                    if (usuarios[usuarioActual].admin)
                        menuAdmin();
                    else
                        menuUsuario();
                }
                break;
        }
    } while (op != 5);

    // Liberar memoria
    delete[] libros;
    delete[] usuarios;
    delete[] prestamos;

    cout << "\nSaliendo del sistema...\n";
    return 0;
}