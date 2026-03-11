#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <cstdlib>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

class Libro {
private:
    string isbn;
    string titulo;
    string autor;
    int cantidad;
public:
    Libro() : cantidad(0) {}//constructor por defecto 
    Libro(string i, string t, string a, int c) : isbn(i), titulo(t), autor(a), cantidad(c) {}

    string getIsbn() const { return isbn; }
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getCantidad() const { return cantidad; }
    void setCantidad(int c) { cantidad = c; }

    void mostrar() const {
        cout << "\n| Titulo: " << titulo << " | Autor: " << autor << " |\n";
        cout << "| ISBN: " << isbn << " | Cantidad: " << cantidad << " |\n";
    }
};

class Usuario {
protected:
    string id;
    string nombre;
    string contrasenia;
public:
    Usuario() {}
    Usuario(string i, string n, string c) : id(i), nombre(n), contrasenia(c) {}
    virtual ~Usuario() {}

    string getId() const { return id; }
    string getNombre() const { return nombre; }
    string getContrasenia() const { return contrasenia; }
    virtual bool esAdmin() const { return false; }
    virtual string getTipo() const { return "usuario"; }
    virtual string getExtra() const { return ""; } // Para carrera o rol
};

class Alumno : public Usuario {
private:
    string carrera;
public:
    Alumno(string i, string n, string c, string ca) : Usuario(i, n, c), carrera(ca) {}
    virtual bool esAdmin() const override { return false; }
    virtual string getTipo() const override { return "alumno"; }
    virtual string getExtra() const override { return carrera; }
};

class Administrador : public Usuario {
private:
    string rol;
public:
    Administrador(string i, string n, string c, string r) : Usuario(i, n, c), rol(r) {}
    virtual bool esAdmin() const override { return true; }
    virtual string getTipo() const override { return "admin"; }
    virtual string getExtra() const override { return rol; }
};

class Prestamo {
private:
    string idUsuario;
    string isbn;
    int cantidad;
public:
    Prestamo() : cantidad(0) {}
    Prestamo(string idU, string i, int c) : idUsuario(idU), isbn(i), cantidad(c) {}

    string getIdUsuario() const { return idUsuario; }
    string getIsbn() const { return isbn; }
    int getCantidad() const { return cantidad; }
    void setCantidad(int c) { cantidad = c; }
};

// ---------- Clase Biblioteca ----------
class Biblioteca {
private:
    vector<Libro> libros;
    vector<shared_ptr<Usuario>> usuarios;
    vector<Prestamo> prestamos;
    int usuarioActual; // índice en el vector, -1 si no hay sesión

    // Métodos auxiliares
    int buscarLibroPorIsbn(const string& isbn) const {
        for (size_t i = 0; i < libros.size(); i++)
            if (libros[i].getIsbn() == isbn) return i;
        return -1;
    }

    int buscarUsuarioPorId(const string& id) const {
        for (size_t i = 0; i < usuarios.size(); i++)
            if (usuarios[i]->getId() == id) return i;
        return -1;
    }

    int buscarPrestamo(const string& idUsuario, const string& isbn) const {
        for (size_t i = 0; i < prestamos.size(); i++)
            if (prestamos[i].getIdUsuario() == idUsuario && prestamos[i].getIsbn() == isbn)
                return i;
        return -1;
    }

    int contarPrestamosUsuario(const string& idUsuario) const {
        int count = 0;
        for (const auto& p : prestamos)
            if (p.getIdUsuario() == idUsuario) count += p.getCantidad();
        return count;
    }

    void limpiarPantalla() {
        system(CLEAR);
    }

    void pausa() {
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }

public:
    Biblioteca() : usuarioActual(-1) {
        cargarDatos();
    }

    ~Biblioteca() {
        guardarDatos();
    }

    // Persistencia
    void guardarDatos() {
        // Guardar libros
        ofstream archLibros("libros.txt");
        for (const auto& l : libros)
            archLibros << l.getIsbn() << "," << l.getTitulo() << "," << l.getAutor() << "," << l.getCantidad() << "\n";
        archLibros.close();

        // Guardar usuarios (con tipo)
        ofstream archUsuarios("usuarios.txt");
        for (const auto& u : usuarios) {
            archUsuarios << u->getId() << "," << u->getNombre() << "," << u->getContrasenia() << ","
                         << u->getTipo() << "," << u->getExtra() << "\n";
        }
        archUsuarios.close();

        // Guardar préstamos
        ofstream archPrestamos("prestamos.txt");
        for (const auto& p : prestamos)
            archPrestamos << p.getIdUsuario() << "," << p.getIsbn() << "," << p.getCantidad() << "\n";
        archPrestamos.close();
    }

    void cargarDatos() {
        // Cargar libros
        ifstream archLibros("libros.txt");
        if (archLibros) {
            string linea;
            while (getline(archLibros, linea)) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1+1);
                size_t p3 = linea.find(',', p2+1);
                string isbn = linea.substr(0, p1);
                string titulo = linea.substr(p1+1, p2-p1-1);
                string autor = linea.substr(p2+1, p3-p2-1);
                int cant = stoi(linea.substr(p3+1));
                libros.emplace_back(isbn, titulo, autor, cant);
            }
            archLibros.close();
        }

        // Cargar usuarios
        ifstream archUsuarios("usuarios.txt");
        if (archUsuarios) {
            string linea;
            while (getline(archUsuarios, linea)) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1+1);
                size_t p3 = linea.find(',', p2+1);
                size_t p4 = linea.find(',', p3+1);
                string id = linea.substr(0, p1);
                string nombre = linea.substr(p1+1, p2-p1-1);
                string pass = linea.substr(p2+1, p3-p2-1);
                string tipo = linea.substr(p3+1, p4-p3-1);
                string extra = linea.substr(p4+1);

                if (tipo == "alumno")
                    usuarios.push_back(make_shared<Alumno>(id, nombre, pass, extra));
                else if (tipo == "admin")
                    usuarios.push_back(make_shared<Administrador>(id, nombre, pass, extra));
            }
            archUsuarios.close();
        } else {
            // Crear admin por defecto si no hay usuarios
            usuarios.push_back(make_shared<Administrador>("U1", "admin", "admin123", "super"));
        }

        // Cargar préstamos
        ifstream archPrestamos("prestamos.txt");
        if (archPrestamos) {
            string linea;
            while (getline(archPrestamos, linea)) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1+1);
                string idU = linea.substr(0, p1);
                string isbn = linea.substr(p1+1, p2-p1-1);
                int cant = stoi(linea.substr(p2+1));
                prestamos.emplace_back(idU, isbn, cant);
            }
            archPrestamos.close();
        }
    }

    // Menús
    void menuPrincipal() {
        int opc;
        do {
            limpiarPantalla();
            cout << "\n====== MENU PRINCIPAL - READBOOK ======\n";
            cout << "1. Mostrar Catalogo\n";
            cout << "2. Buscar Libro\n";
            cout << "3. Registrarse\n";
            cout << "4. Iniciar Sesion\n";
            cout << "5. Salir\n";
            cout << "Ingrese una opcion: ";
            cin >> opc;
            cin.ignore();

            switch (opc) {
                case 1: mostrarCatalogo(); break;
                case 2: buscarLibro(); break;
                case 3: registrarUsuario(); break;
                case 4: iniciarSesion(); break;
            }
        } while (opc != 5 && usuarioActual == -1);
    }

    void menuAlumno() {
        int opc;
        do {
            limpiarPantalla();
            cout << "\n========= MENU ALUMNO - READBOOK =======\n";
            cout << "1. Ver Catalogo\n";
            cout << "2. Buscar Libro\n";
            cout << "3. Prestar Libro\n";
            cout << "4. Devolver Libro\n";
            cout << "5. Cerrar Sesion\n";
            cout << "Ingrese una opcion: ";
            cin >> opc;
            cin.ignore();

            switch (opc) {
                case 1: mostrarCatalogo(); break;
                case 2: buscarLibro(); break;
                case 3: prestarLibro(); break;
                case 4: devolverLibro(); break;
                case 5: cerrarSesion(); break;
            }
        } while (opc != 5);
    }

    void menuAdmin() {
        int opc;
        do {
            limpiarPantalla();
            cout << "\n========= MENU ADMINISTRADOR - READBOOK =======\n";
            cout << "1. Ver Catalogo\n";
            cout << "2. Buscar Libro\n";
            cout << "3. Agregar Libro\n";
            cout << "4. Cerrar Sesion\n";
            cout << "Ingrese una opcion: ";
            cin >> opc;
            cin.ignore();

            switch (opc) {
                case 1: mostrarCatalogo(); break;
                case 2: buscarLibro(); break;
                case 3: agregarLibro(); break;
                case 4: cerrarSesion(); break;
            }
        } while (opc != 4);
    }

    // Funcionalidades
    void mostrarCatalogo() {
        limpiarPantalla();
        cout << "\n=== CATALOGO DE LIBROS ===\n";
        if (libros.empty()) {
            cout << "No hay libros registrados.\n";
        } else {
            for (const auto& l : libros) {
                l.mostrar();
                cout << "------------------------\n";
            }
        }
        pausa();
    }

    void buscarLibro() {
        limpiarPantalla();
        cout << "\n=== BUSCAR LIBRO ===\n";
        cout << "Ingrese titulo o ISBN: ";
        string criterio;
        getline(cin, criterio);
        bool encontrado = false;
        for (const auto& l : libros) {
            if (l.getTitulo().find(criterio) != string::npos || l.getIsbn().find(criterio) != string::npos) {
                l.mostrar();
                cout << "------------------------\n";
                encontrado = true;
            }
        }
        if (!encontrado) cout << "No se encontraron libros.\n";
        pausa();
    }

    void registrarUsuario() {
        limpiarPantalla();
        cout << "\n=== REGISTRO DE USUARIO ===\n";
        cout << "Tipo (1=Alumno, 2=Administrador): ";
        int tipo;
        cin >> tipo;
        cin.ignore();

        string id, nombre, pass, extra;
        cout << "ID: "; getline(cin, id);
        // Verificar si ya existe
        if (buscarUsuarioPorId(id) != -1) {
            cout << "Ya existe un usuario con ese ID.\n";
            pausa();
            return;
        }
        cout << "Nombre: "; getline(cin, nombre);
        cout << "Contrasenia: "; getline(cin, pass);

        if (tipo == 1) {
            cout << "Carrera: "; getline(cin, extra);
            usuarios.push_back(make_shared<Alumno>(id, nombre, pass, extra));
            cout << "Alumno registrado con exito.\n";
        } else if (tipo == 2) {
            cout << "Rol: "; getline(cin, extra);
            usuarios.push_back(make_shared<Administrador>(id, nombre, pass, extra));
            cout << "Administrador registrado con exito.\n";
        } else {
            cout << "Tipo invalido.\n";
        }
        guardarDatos();
        pausa();
    }

    void iniciarSesion() {
        limpiarPantalla();
        cout << "\n=== INICIAR SESION ===\n";
        cout << "ID: ";
        string id;
        getline(cin, id);
        cout << "Contrasenia: ";
        string pass;
        getline(cin, pass);

        int idx = buscarUsuarioPorId(id);
        if (idx != -1 && usuarios[idx]->getContrasenia() == pass) {
            usuarioActual = idx;
            cout << "Bienvenido " << usuarios[idx]->getNombre() << "!\n";
            pausa();
            if (usuarios[idx]->esAdmin())
                menuAdmin();
            else
                menuAlumno();
        } else {
            cout << "ID o contrasenia incorrectos.\n";
            pausa();
        }
    }

    void cerrarSesion() {
        usuarioActual = -1;
        cout << "Sesion cerrada.\n";
        pausa();
    }

    void agregarLibro() {
        limpiarPantalla();
        cout << "\n=== AGREGAR LIBRO ===\n";
        string isbn, titulo, autor;
        int cantidad;
        cout << "ISBN: "; getline(cin, isbn);
        if (buscarLibroPorIsbn(isbn) != -1) {
            cout << "Ya existe un libro con ese ISBN.\n";
            pausa();
            return;
        }
        cout << "Titulo: "; getline(cin, titulo);
        cout << "Autor: "; getline(cin, autor);
        cout << "Cantidad: "; cin >> cantidad; cin.ignore();
        libros.emplace_back(isbn, titulo, autor, cantidad);//construye el objeto directamente
        guardarDatos();
        cout << "Libro agregado.\n";
        pausa();
    }

    void prestarLibro() {
        if (usuarioActual == -1) return;
        string idU = usuarios[usuarioActual]->getId();
        limpiarPantalla();
        cout << "\n=== PRESTAR LIBRO ===\n";
        cout << "Ingrese ISBN del libro: ";
        string isbn;
        getline(cin, isbn);
        int idxLibro = buscarLibroPorIsbn(isbn);
        if (idxLibro == -1) {
            cout << "Libro no encontrado.\n";
            pausa();
            return;
        }
        Libro& libro = libros[idxLibro];
        if (libro.getCantidad() < 1) {
            cout << "No hay ejemplares disponibles.\n";
            pausa();
            return;
        }
        // Verificar si ya tiene préstamo de ese libro
        if (buscarPrestamo(idU, isbn) != -1) {
            cout << "Ya tienes un prestamo de este libro.\n";
            pausa();
            return;
        }
        // Verificar límite de 3 libros
        if (contarPrestamosUsuario(idU) >= 3) {
            cout << "Has alcanzado el limite de 3 libros prestados.\n";
            pausa();
            return;
        }
        // Realizar préstamo
        libro.setCantidad(libro.getCantidad() - 1);
        prestamos.emplace_back(idU, isbn, 1);
        guardarDatos();
        cout << "Prestamo realizado con exito.\n";
        pausa();
    }

    void devolverLibro() {
        if (usuarioActual == -1) return;
        string idU = usuarios[usuarioActual]->getId();
        limpiarPantalla();
        cout << "\n=== DEVOLVER LIBRO ===\n";
        cout << "Ingrese ISBN del libro a devolver: ";
        string isbn;
        getline(cin, isbn);
        int idxPrestamo = buscarPrestamo(idU, isbn);
        if (idxPrestamo == -1) {
            cout << "No tienes un prestamo de ese libro.\n";
            pausa();
            return;
        }
        Prestamo& p = prestamos[idxPrestamo];
        int idxLibro = buscarLibroPorIsbn(isbn);
        if (idxLibro != -1) {
            libros[idxLibro].setCantidad(libros[idxLibro].getCantidad() + 1);
        }
        if (p.getCantidad() > 1) {
            p.setCantidad(p.getCantidad() - 1);
        } else {
            prestamos.erase(prestamos.begin() + idxPrestamo);
        }
        guardarDatos();
        cout << "Devolucion realizada con exito.\n";
        pausa();
    }

    void ejecutar() {
        while (true) {
            if (usuarioActual == -1) {
                menuPrincipal();
                if (usuarioActual == -1) break; // opción salir
            }
        }
        cout << "Saliendo del sistema...\n";
    }
};

// ---------- Main ----------
int main() {
    Biblioteca biblio;
    biblio.ejecutar();
    return 0;
}