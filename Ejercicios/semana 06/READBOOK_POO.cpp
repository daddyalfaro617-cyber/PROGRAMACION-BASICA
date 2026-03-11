#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

using namespace std;

class Libro
{
private:
    string isbn;
    string titulo;
    string autor;
    int cantidad;

public:
    Libro(string isbn, string titulo, string autor, int cantidad)
        : isbn(isbn), titulo(titulo), autor(autor), cantidad(cantidad) {}
};

class Usuario
{
private:
    string id;
    string nombre;
    string contrasenia;

public:
    Usuario(string id, string nombre, string contrasenia) 
    : id(id), nombre(nombre), contrasenia(contrasenia) {}
};

class Alumno : public Usuario
{
private:
    string carrera;

public:
    Alumno(string id, string nombre, string contrasenia, string carrera) 
    : Usuario(id, nombre, contrasenia), carrera(carrera) {}
};

class Administrador : public Usuario
{
private:
    string rol;

public:
};

class Prestamo
{
private:
    string idUsuario;
    string isbn;
    int cantidad;
};

class Biblioteca
{
private:
    vector<shared_ptr<Usuario>> usuarios;
    vector<Libro> libros;
    vector<Prestamo> prestamos;
    int usuarioActual;

public:
    void limpiarPantalla()
    {

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    void menuPrincipal()
    {
        cout << "\n====== MENU PRINCIPAL-READBOOK ======\n"
             << endl;
        cout << "1. Mostrar Catalogo\n";
        cout << "2. Buscar Libro\n";
        cout << "3. Registrarse\n";
        cout << "4. Iniciar Sesion\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
    }
    void menuAlumno()
    {
        cout << "\n========= MENU ALUMNO-READBOOK =======\n"
             << endl;
        cout << "1. Ver Catalogo" << endl;
        cout << "2. Buscar Libro" << endl;
        cout << "3. Prestar Libro" << endl;
        cout << "4. Devolver Libro" << endl;
        cout << "5.Salir" << endl;
        cout << "Ingrese una opcion: ";
    }
    void menuAdmin()
    {
        cout << "\n========= MENU ADMINISTRADOR-READBOOK =======\n"
             << endl;
        cout << "1. Ver Catalogo" << endl;
        cout << "2. Buscar Libro" << endl;
        cout << "3. Agregar Libro" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Ingrese una opcion: ";
    }

    void mostrarCatalogo()
    {
        string isbn, titulo, autor;
        int cantidad;

        cout << "\n| Titulo: " << titulo << " |  | Autor: " << autor << " | " << endl;
        cout << "| ISBN: " << isbn << " |  | Cantidad: " << cantidad << " | \n"
             << endl;
    }

    void buscarLIbro();

    void agregarLibro()
    {
        string autor, isbn, titulo;
        int cantidad;

        cout << "Ingrese el Titulo: ";
        cin >> titulo;
        cout << "Ingrese el Autor: ";
        cin >> autor;
        cout << "Ingrese el ISBN: ";
        cin >> isbn;
        cout << "Ingrese la Cantidad: ";
        cin >> cantidad;
    }

    void registrarUsuario();

    void registrarAlumno()
    {

        string nombre, id, contrasenia, carrera;

        cout << "Ingrese su Nombre: " << endl;
        cin >> nombre;
        cout << "Ingrese su ID de Alumno: " << endl;
        cin >> id;
        cout << "Ingrese su Carrera: " << endl;
        cin >> carrera;
        cout << "Ingrese su Contrasenia " << endl;
        cin >> contrasenia;
    }

    void registrarAdministrador()
    {
        string nombre, id, contrasenia, rol;

        cout << "Ingrese su Nombre: " << endl;
        cin >> nombre;
        cout << "Ingrese su ID de Admin: " << endl;
        cin >> id;
        cout << "Ingrese su Rol: " << endl;
        cin >> rol;
        cout << "Ingrese su Contrasenia " << endl;
        cin >> contrasenia;
    }

    void prestarLibro();

    void devolverLibro();

    void cargarUsuario();

    void guardarUsuario();

    void cargarPrestamo();

    void guardarPrestamo();
};


int main()
{

    return 0;
}