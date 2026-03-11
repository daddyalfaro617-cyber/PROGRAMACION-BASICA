#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>

using namespace std;

// ---------------------------- Clase Libro ----------------------------
class Libro
{
private:
    string isbn;
    string titulo;
    string autor;
    int cantidad;

public:
    Libro() : cantidad(0) {}
    Libro(const string &isbn, const string &titulo, const string &autor, int cant)
        : isbn(isbn), titulo(titulo), autor(autor), cantidad(cant) {}

    string getIsbn() const { return isbn; }
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int cant) { cantidad = cant; }

    void mostrar() const
    {
        cout << isbn << " | " << titulo << " | " << autor << " | Stock: " << cantidad << endl;
    }
};

// ---------------------------- Clase Usuario ----------------------------
class Usuario
{
private:
    string id;
    string nombre;
    string pass;
    bool admin;

public:
    Usuario() : admin(false) {}
    Usuario(const string &id, const string &nombre, const string &pass, bool admin)
        : id(id), nombre(nombre), pass(pass), admin(admin) {}

    string getId() const { return id; }
    string getNombre() const { return nombre; }
    string getPass() const { return pass; }
    bool isAdmin() const { return admin; }

    bool checkPassword(const string &p) const { return pass == p; }

    void setId(const string &newId) { id = newId; }
};

// ---------------------------- Clase Prestamo ----------------------------
class Prestamo
{
private:
    string idUsuario;
    string isbn;
    int cantidad;

public:
    Prestamo() : cantidad(0) {}
    Prestamo(const string &idUsr, const string &isbn, int cant)
        : idUsuario(idUsr), isbn(isbn), cantidad(cant) {}

    string getIdUsuario() const { return idUsuario; }
    string getIsbn() const { return isbn; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int cant) { cantidad = cant; }
};

// ---------------------------- Clase Biblioteca ----------------------------
class Biblioteca
{
private:
    vector<Libro> libros;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    int usuarioActual; // índice del usuario logueado, -1 si ninguno

    // Métodos privados de búsqueda (devuelven índice o -1)
    int buscarLibroIndex(const string &isbn) const
    {
        for (size_t i = 0; i < libros.size(); i++)
            if (libros[i].getIsbn() == isbn)
                return i;
        return -1;
    }

    int buscarUsuarioIndex(const string &id) const
    {
        for (size_t i = 0; i < usuarios.size(); i++)
            if (usuarios[i].getId() == id)
                return i;
        return -1;
    }

    int buscarPrestamoIndex(const string &isbn, int userIndex) const
    {
        if (userIndex < 0 || userIndex >= (int)usuarios.size())
            return -1;
        const string &idUsr = usuarios[userIndex].getId();
        for (size_t i = 0; i < prestamos.size(); i++)
            if (prestamos[i].getIdUsuario() == idUsr && prestamos[i].getIsbn() == isbn)
                return i;
        return -1;
    }

public:
    Biblioteca() : usuarioActual(-1)
    {
        cargarDatos();
    }

    ~Biblioteca()
    {
        guardarDatos();
    }

    // Getters
    const vector<Libro> &getLibros() const { return libros; }
    const vector<Usuario> &getUsuarios() const { return usuarios; }
    const vector<Prestamo> &getPrestamos() const { return prestamos; }
    int getUsuarioActualIndex() const { return usuarioActual; }
    const Usuario &getUsuarioActual() const { return usuarios[usuarioActual]; } // asume sesión activa
    bool haySesion() const { return usuarioActual != -1; }

    // Persistencia
    void cargarDatos()
    {
        ifstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt");

        // Cargar usuarios
        if (!u.is_open())
        {
            // Crear admin por defecto si no existe archivo
            Usuario admin("ADMIN", "admin", "admin123", true);
            usuarios.push_back(admin);
            guardarDatos();
        }
        else
        {
            int n;
            u >> n;
            u.ignore();
            for (int i = 0; i < n; i++)
            {
                string id, nombre, pass;
                bool admin;
                getline(u, id);
                getline(u, nombre);
                getline(u, pass);
                u >> admin;
                u.ignore();
                if (u.fail())
                    break;
                usuarios.emplace_back(id, nombre, pass, admin);
            }
        }

        // Cargar libros
        if (l.is_open())
        {
            int n;
            l >> n;
            l.ignore();
            for (int i = 0; i < n; i++)
            {
                string isbn, titulo, autor;
                int cant;
                getline(l, isbn);
                getline(l, titulo);
                getline(l, autor);
                l >> cant;
                l.ignore();
                if (l.fail())
                    break;
                libros.emplace_back(isbn, titulo, autor, cant);
            }
        }

        // Cargar préstamos
        if (p.is_open())
        {
            int n;
            p >> n;
            p.ignore();
            for (int i = 0; i < n; i++)
            {
                string idUsr, isbn;
                int cant;
                getline(p, idUsr);
                getline(p, isbn);
                p >> cant;
                p.ignore();
                if (p.fail())
                    break;
                prestamos.emplace_back(idUsr, isbn, cant);
            }
        }
    }

    void guardarDatos() const
    {
        ofstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt");
        if (!u.is_open() || !l.is_open() || !p.is_open())
        {
            cout << "Error al abrir archivos para guardar.\n";
            return;
        }

        // Usuarios
        u << usuarios.size() << endl;
        for (const auto &usr : usuarios)
        {
            u << usr.getId() << endl;
            u << usr.getNombre() << endl;
            u << usr.getPass() << endl;
            u << usr.isAdmin() << endl;
        }

        // Libros
        l << libros.size() << endl;
        for (const auto &lib : libros)
        {
            l << lib.getIsbn() << endl;
            l << lib.getTitulo() << endl;
            l << lib.getAutor() << endl;
            l << lib.getCantidad() << endl;
        }

        // Préstamos
        p << prestamos.size() << endl;
        for (const auto &pre : prestamos)
        {
            p << pre.getIdUsuario() << endl;
            p << pre.getIsbn() << endl;
            p << pre.getCantidad() << endl;
        }
    }

    // Gestión de usuarios
    bool registrarUsuario(const Usuario &usuario)
    {
        if (buscarUsuarioIndex(usuario.getId()) != -1)
            return false;
        usuarios.push_back(usuario);
        guardarDatos();
        return true;
    }

    bool login(const string &id, const string &pass)
    {
        int idx = buscarUsuarioIndex(id);
        if (idx != -1 && usuarios[idx].checkPassword(pass))
        {
            usuarioActual = idx;
            return true;
        }
        return false;
    }

    void logout() { usuarioActual = -1; }

    // Gestión de libros
    bool agregarLibro(const Libro &libro)
    {
        if (buscarLibroIndex(libro.getIsbn()) != -1)
            return false;
        libros.push_back(libro);
        guardarDatos();
        return true;
    }

    const Libro *buscarLibroPorIsbn(const string &isbn) const
    {
        int idx = buscarLibroIndex(isbn);
        return (idx != -1) ? &libros[idx] : nullptr;
    }

    vector<Libro> buscarLibrosPorTitulo(const string &titulo) const
    {
        vector<Libro> resultados;
        for (const auto &libro : libros)
            if (libro.getTitulo().find(titulo) != string::npos)
                resultados.push_back(libro);
        return resultados;
    }

    vector<Libro> buscarLibros(const string &criterio) const
    {
        vector<Libro> resultados;
        for (const auto &libro : libros)
        {
            if (libro.getIsbn() == criterio || libro.getTitulo().find(criterio) != string::npos)
                resultados.push_back(libro);
        }
        return resultados;
    }

    // Gestión de préstamos
    bool prestarLibro(int userIndex, const string &isbn, int cantidad)
    {
        if (userIndex < 0 || userIndex >= (int)usuarios.size())
            return false;
        int libroIdx = buscarLibroIndex(isbn);
        if (libroIdx == -1)
            return false;
        Libro &libro = libros[libroIdx];
        if (libro.getCantidad() < cantidad)
            return false;

        int prestamoIdx = buscarPrestamoIndex(isbn, userIndex);
        if (prestamoIdx != -1)
        {
            prestamos[prestamoIdx].setCantidad(prestamos[prestamoIdx].getCantidad() + cantidad);
        }
        else
        {
            prestamos.emplace_back(usuarios[userIndex].getId(), isbn, cantidad);
        }
        libro.setCantidad(libro.getCantidad() - cantidad);
        guardarDatos();
        return true;
    }

    bool devolverLibro(int userIndex, const string &isbn, int cantidad)
    {
        if (userIndex < 0 || userIndex >= (int)usuarios.size())
            return false;
        int prestamoIdx = buscarPrestamoIndex(isbn, userIndex);
        if (prestamoIdx == -1)
            return false;
        Prestamo &prestamo = prestamos[prestamoIdx];
        if (prestamo.getCantidad() < cantidad)
            return false;

        int libroIdx = buscarLibroIndex(isbn);
        if (libroIdx == -1)
            return false; // no debería ocurrir
        Libro &libro = libros[libroIdx];

        libro.setCantidad(libro.getCantidad() + cantidad);
        prestamo.setCantidad(prestamo.getCantidad() - cantidad);

        if (prestamo.getCantidad() == 0)
        {
            prestamos.erase(prestamos.begin() + prestamoIdx);
        }
        guardarDatos();
        return true;
    }
};

// ---------------------- Utilidades de consola ------------------------
namespace ConsoleUtils
{
    void limpiarPantalla()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pausa()
    {
        cout << "\nPresione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int leerEntero(int min, int max)
    {
        int op;
        while (true)
        {
            if (cin >> op && op >= min && op <= max)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return op;
            }
            cout << "Opcion invalida. Intente nuevamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string leerString(const string &mensaje, int maxLong = 50)
    {
        string entrada;
        do
        {
            cout << mensaje;
            getline(cin, entrada);
            if (entrada.empty())
            {
                cout << "El campo no puede estar vacio.\n";
            }
            else if (entrada.length() > static_cast<size_t>(maxLong))
            {
                cout << "El campo no puede exceder " << maxLong << " caracteres.\n";
            }
        } while (entrada.empty() || entrada.length() > static_cast<size_t>(maxLong));
        return entrada;
    }

    bool validarISBN(const string &isbn)
    {
        string limpio;
        for (char c : isbn)
        {
            if (isdigit(c))
                limpio += c;
            else if (c != '-')
                return false;
        }
        return limpio.length() >= 10 && limpio.length() <= 13;
    }

    void encabezado(const string &titulo)
    {
        limpiarPantalla();
        cout << "\n====================================\n";
        cout << "||          " << titulo;
        int spaces = 20 - (int)titulo.length();
        if (spaces < 0)
            spaces = 0;
        for (int i = 0; i < spaces; i++)
            cout << " ";
        cout << "       ||\n";
        cout << "====================================\n";
    }
}

// ---------------------------- Interfaz de Usuario ----------------------------
class ConsoleUI
{
private:
    Biblioteca &biblio;

    void mostrarCatalogo()
    {
        ConsoleUtils::encabezado("CATALOGO DE LIBROS");
        if (biblio.getLibros().empty())
        {
            cout << "No hay libros registrados.\n";
            ConsoleUtils::pausa();
            return;
        }
        for (const auto &libro : biblio.getLibros())
            libro.mostrar();
        ConsoleUtils::pausa();
    }

    void buscarLibroMenu()
    {
        ConsoleUtils::encabezado("BUSCAR LIBRO");
        string dato = ConsoleUtils::leerString("Ingrese titulo o ISBN: ", 100);
        auto resultados = biblio.buscarLibros(dato);
        if (resultados.empty())
            cout << "No se encontraron resultados.\n";
        else
            for (const auto &libro : resultados)
                libro.mostrar();
        ConsoleUtils::pausa();
    }

    void registrar()
    {
        ConsoleUtils::encabezado("REGISTRO DE USUARIO");
        string id = "U" + to_string(biblio.getUsuarios().size() + 1);
        string nombre = ConsoleUtils::leerString("Nombre: ");
        string pass = ConsoleUtils::leerString("Contrasena: ");
        Usuario nuevo(id, nombre, pass, false);
        if (biblio.registrarUsuario(nuevo))
            cout << "Usuario registrado con ID: " << id << endl;
        else
            cout << "Error al registrar usuario.\n";
        ConsoleUtils::pausa();
    }

    bool login()
    {
        ConsoleUtils::encabezado("INICIAR SESION");
        int intentos = 3;
        while (intentos-- > 0)
        {
            string id = ConsoleUtils::leerString("ID: ");
            string pass = ConsoleUtils::leerString("Contrasena: ");
            if (biblio.login(id, pass))
                return true;
            cout << "Credenciales incorrectas. Intentos restantes: " << intentos << endl;
        }
        cout << "Demasiados intentos fallidos.\n";
        ConsoleUtils::pausa();
        return false;
    }

    void agregarLibro()
    {
        ConsoleUtils::encabezado("AGREGAR LIBRO");
        string isbn;
        do
        {
            isbn = ConsoleUtils::leerString("ISBN: ", 20);
            if (!ConsoleUtils::validarISBN(isbn))
                cout << "ISBN invalido. Debe contener solo digitos y guiones, y tener entre 10 y 13 digitos.\n";
        } while (!ConsoleUtils::validarISBN(isbn));

        if (biblio.buscarLibroPorIsbn(isbn) != nullptr)
        {
            cout << "El ISBN ya existe.\n";
            ConsoleUtils::pausa();
            return;
        }

        string titulo = ConsoleUtils::leerString("Titulo: ");
        string autor = ConsoleUtils::leerString("Autor: ");
        cout << "Cantidad: ";
        int cantidad = ConsoleUtils::leerEntero(0, 100000);
        Libro nuevo(isbn, titulo, autor, cantidad);
        if (biblio.agregarLibro(nuevo))
            cout << "Libro agregado correctamente.\n";
        else
            cout << "Error al agregar libro.\n";
        ConsoleUtils::pausa();
    }

    void prestar()
    {
        ConsoleUtils::encabezado("PRESTAR LIBRO");
        string isbn = ConsoleUtils::leerString("ISBN: ", 20);
        if (!ConsoleUtils::validarISBN(isbn))
        {
            cout << "ISBN invalido.\n";
            ConsoleUtils::pausa();
            return;
        }

        const Libro *libro = biblio.buscarLibroPorIsbn(isbn);
        if (libro == nullptr)
        {
            cout << "Libro no encontrado.\n";
            ConsoleUtils::pausa();
            return;
        }
        if (libro->getCantidad() == 0)
        {
            cout << "No hay stock disponible.\n";
            ConsoleUtils::pausa();
            return;
        }

        cout << "Cantidad (max " << libro->getCantidad() << "): ";
        int c = ConsoleUtils::leerEntero(1, libro->getCantidad());

        if (biblio.prestarLibro(biblio.getUsuarioActualIndex(), isbn, c))
            cout << "Prestamo registrado.\n";
        else
            cout << "Error al realizar prestamo.\n";
        ConsoleUtils::pausa();
    }

    void devolver()
    {
        ConsoleUtils::encabezado("DEVOLVER LIBRO");
        string isbn = ConsoleUtils::leerString("ISBN: ", 20);
        if (!ConsoleUtils::validarISBN(isbn))
        {
            cout << "ISBN invalido.\n";
            ConsoleUtils::pausa();
            return;
        }

        cout << "Cantidad a devolver: ";
        int c = ConsoleUtils::leerEntero(1, 100000);

        if (biblio.devolverLibro(biblio.getUsuarioActualIndex(), isbn, c))
            cout << "Devolucion realizada.\n";
        else
            cout << "No tienes este libro prestado o la cantidad es invalida.\n";
        ConsoleUtils::pausa();
    }

    void menuUsuario()
    {
        int op;
        do
        {
            ConsoleUtils::encabezado("MENU USUARIO");
            cout << "||    1. Ver catalogo              ||\n";
            cout << "||    2. Buscar libro              ||\n";
            cout << "||    3. Prestar libro             ||\n";
            cout << "||    4. Devolver libro            ||\n";
            cout << "||    5. Cerrar sesion             ||\n";
            cout << "=====================================\n";
            op = ConsoleUtils::leerEntero(1, 5);

            switch (op)
            {
            case 1:
                mostrarCatalogo();
                break;
            case 2:
                buscarLibroMenu();
                break;
            case 3:
                prestar();
                break;
            case 4:
                devolver();
                break;
            }
        } while (op != 5);
        biblio.logout();
    }

    void menuAdmin()
    {
        int op;
        do
        {
            ConsoleUtils::encabezado("MENU ADMINISTRADOR");
            cout << "||    1. Agregar libro               ||\n";
            cout << "||    2. Ver catalogo                ||\n";
            cout << "||    3. Buscar libro                ||\n";
            cout << "||    4. Cerrar sesion               ||\n";
            cout << "=======================================\n";
            cout << "Seleccione una opcion: ";
            op = ConsoleUtils::leerEntero(1, 4);

            switch (op)
            {
            case 1:
                agregarLibro();
                break;
            case 2:
                mostrarCatalogo();
                break;
            case 3:
                buscarLibroMenu();
                break;
            }
        } while (op != 4);
        biblio.logout();
    }

public:
    ConsoleUI(Biblioteca &b) : biblio(b) {}

    void run()
    {
        int op;
        do
        {
            ConsoleUtils::encabezado("SISTEMA READBOOK");
            cout << "||     1. Ver catalogo             ||\n";
            cout << "||     2. Buscar libro             ||\n";
            cout << "||     3. Registrarse              ||\n";
            cout << "||     4. Iniciar sesion           ||\n";
            cout << "||     5. Salir                    ||\n";
            cout << "=====================================\n";
            cout << "Seleccione una opcion: ";
            op = ConsoleUtils::leerEntero(1, 5);

            switch (op)
            {
            case 1:
                mostrarCatalogo();
                break;
            case 2:
                buscarLibroMenu();
                break;
            case 3:
                registrar();
                break;
            case 4:
                if (login())
                {
                    if (biblio.getUsuarioActual().isAdmin())
                        menuAdmin();
                    else
                        menuUsuario();
                }
                break;
            }
        } while (op != 5);
    }
};

// ---------------------------- Main ----------------------------
int main()
{
    Biblioteca biblio;
    ConsoleUI ui(biblio);
    ui.run();
    return 0;
}