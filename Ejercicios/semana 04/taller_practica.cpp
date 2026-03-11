/*
==================== BITÁCORA IA ====================
Herramienta IA usada: Chat GPT
Objetivo del uso: (ej. entender punteros, revisar bug, mejorar diseño)

Preguntas que hice a la IA (resumen):
1) Como puedo implementar un sistema de gestión de biblioteca en C++ usando punteros y arreglos dinámicos?
2) Como podria implementar cada funcion, que debo de utilizar, en base a ello que realice un analisis de cada restriccion y requerimiento.
3) Como implementaria la IA este paso a paso, y que plan usaria para la creacion del codigo?

Qué sugerencias acepté y por qué:

Acepte seguir el procedimiento paso a paso que me estructuro IA.
Acepte las modificaciones a mi primera version de codigo inicial, ya que aun faltaba incluir mas funciones y mejorar su estructura, y la IA me dio una guia clara de como hacerlo.

Qué sugerencias rechacé y por qué:

Rechace sugerencia de usar clases, ya que el objetivo del taller es practicar con punteros y arreglos dinamicos.

Test manual diseñado por mí:
Entrada (pasos/comandos):
1) Agregar libro con ID 1, titulo "El Caballero Carmelo", autor "Abraham Valdelomar", año 1985.
2) Agregar usuario con ID 1, nombre "Maria Jose", carrera "Zootecnia".
3) Prestar libro con ID 1 al usuario con ID 1.
Salida esperada:
1) Libro agregado correctamente.
2) Usuario agregado correctamente.
3) Libro prestado correctamente.
Nota de autoría:
Declaro que entiendo el código entregado y puedo explicarlo.
====================================================
*/

#include <iostream>
#include <string>
using namespace std;

struct Libro
{
    int id;
    string titulo;
    string autor;
    int anio;
    bool disponible;
};

struct Usuario
{
    int id;
    string nombre;
    string carrera;
};

struct Prestamo
{
    int idUsuario;
    int idLibro;
};

Libro *libros = nullptr;
int cantidadLibros = 0;
int capacidadLibros = 0;

Usuario *usuarios = nullptr;
int cantidadUsuarios = 0;
int capacidadUsuarios = 0;

Prestamo *prestamos = nullptr;
int cantidadPrestamos = 0;
int capacidadPrestamos = 0;

void redimensionarLibros()
{
    capacidadLibros *= 2;
    Libro *nuevo = new Libro[capacidadLibros];

    for (int i = 0; i < cantidadLibros; i++)
        nuevo[i] = libros[i];

    delete[] libros;
    libros = nuevo;
}

void redimensionarUsuarios()
{
    capacidadUsuarios *= 2;
    Usuario *nuevo = new Usuario[capacidadUsuarios];

    for (int i = 0; i < cantidadUsuarios; i++)
        nuevo[i] = usuarios[i];

    delete[] usuarios;
    usuarios = nuevo;
}

void redimensionarPrestamos()
{
    capacidadPrestamos *= 2;
    Prestamo *nuevo = new Prestamo[capacidadPrestamos];

    for (int i = 0; i < cantidadPrestamos; i++)
        nuevo[i] = prestamos[i];

    delete[] prestamos;
    prestamos = nuevo;
}

Libro *buscarLibroPorId(int id)
{
    for (int i = 0; i < cantidadLibros; i++)
    {
        if (libros[i].id == id)
            return &libros[i];
    }
    return nullptr;
}

Usuario *buscarUsuarioPorId(int id)
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i].id == id)
            return &usuarios[i];
    }
    return nullptr;
}

void agregarLibro()
{
    int id;
    cout << "ID del libro: ";
    cin >> id;

    if (buscarLibroPorId(id) != nullptr)
    {
        cout << "Error: ID ya existe.\n";
        return;
    }

    if (cantidadLibros == capacidadLibros)
        redimensionarLibros();

    libros[cantidadLibros].id = id;
    cin.ignore();

    cout << "Titulo: ";
    getline(cin, libros[cantidadLibros].titulo);

    cout << "Autor: ";
    getline(cin, libros[cantidadLibros].autor);

    cout << "Anio: ";
    cin >> libros[cantidadLibros].anio;

    libros[cantidadLibros].disponible = true;

    cantidadLibros++;

    cout << "Libro agregado correctamente.\n";
}

void listarLibros()
{
    if (cantidadLibros == 0)
    {
        cout << "No hay libros registrados.\n";
        return;
    }

    for (int i = 0; i < cantidadLibros; i++)
    {
        cout << "\nID: " << libros[i].id << endl;
        cout << "Titulo: " << libros[i].titulo << endl;
        cout << "Autor: " << libros[i].autor << endl;
        cout << "Anio: " << libros[i].anio << endl;
        cout << "Disponible: "
             << (libros[i].disponible ? "Si" : "No") << endl;
    }
}

void agregarUsuario()
{
    int id;
    cout << "ID del usuario: ";
    cin >> id;

    if (buscarUsuarioPorId(id) != nullptr)
    {
        cout << "Error: ID ya existe.\n";
        return;
    }

    if (cantidadUsuarios == capacidadUsuarios)
        redimensionarUsuarios();

    usuarios[cantidadUsuarios].id = id;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, usuarios[cantidadUsuarios].nombre);

    cout << "Carrera: ";
    getline(cin, usuarios[cantidadUsuarios].carrera);

    cantidadUsuarios++;

    cout << "Usuario agregado correctamente.\n";
}

void listarUsuarios()
{
    if (cantidadUsuarios == 0)
    {
        cout << "No hay usuarios registrados.\n";
        return;
    }

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        cout << "\nID: " << usuarios[i].id << endl;
        cout << "Nombre: " << usuarios[i].nombre << endl;
        cout << "Carrera: " << usuarios[i].carrera << endl;
    }
}

void prestarLibro()
{
    int idUsuario, idLibro;

    cout << "ID Usuario: ";
    cin >> idUsuario;

    Usuario *usuario = buscarUsuarioPorId(idUsuario);
    if (usuario == nullptr)
    {
        cout << "Usuario no encontrado.\n";
        return;
    }

    cout << "ID Libro: ";
    cin >> idLibro;

    Libro *libro = buscarLibroPorId(idLibro);
    if (libro == nullptr)
    {
        cout << "Libro no encontrado.\n";
        return;
    }

    if (!libro->disponible)
    {
        cout << "Libro no disponible.\n";
        return;
    }

    if (cantidadPrestamos == capacidadPrestamos)
        redimensionarPrestamos();

    prestamos[cantidadPrestamos].idUsuario = idUsuario;
    prestamos[cantidadPrestamos].idLibro = idLibro;
    cantidadPrestamos++;

    libro->disponible = false;

    cout << "Prestamo realizado con exito.\n";
}

void devolverLibro()
{
    int idLibro;
    cout << "ID Libro a devolver: ";
    cin >> idLibro;

    for (int i = 0; i < cantidadPrestamos; i++)
    {
        if (prestamos[i].idLibro == idLibro)
        {

            Libro *libro = buscarLibroPorId(idLibro);
            if (libro != nullptr)
                libro->disponible = true;

            prestamos[i] = prestamos[cantidadPrestamos - 1];
            cantidadPrestamos--;

            cout << "Libro devuelto correctamente.\n";
            return;
        }
    }

    cout << "No existe prestamo activo para ese libro.\n";
}

void mostrarPrestamos()
{
    if (cantidadPrestamos == 0)
    {
        cout << "No hay prestamos activos.\n";
        return;
    }

    for (int i = 0; i < cantidadPrestamos; i++)
    {
        Usuario *u = buscarUsuarioPorId(prestamos[i].idUsuario);
        Libro *l = buscarLibroPorId(prestamos[i].idLibro);

        cout << "\nUsuario: " << (u ? u->nombre : "Desconocido");
        cout << " | Libro: " << (l ? l->titulo : "Desconocido") << endl;
    }
}

void buscarLibros()
{
    string texto;
    cin.ignore();
    cout << "Texto a buscar: ";
    getline(cin, texto);

    for (int i = 0; i < cantidadLibros; i++)
    {
        if (libros[i].titulo.find(texto) != string::npos ||
            libros[i].autor.find(texto) != string::npos)
        {

            cout << "\nID: " << libros[i].id;
            cout << " | Titulo: " << libros[i].titulo;
            cout << " | Autor: " << libros[i].autor << endl;
        }
    }
}

int main()
{

    capacidadLibros = 5;
    libros = new Libro[capacidadLibros];

    capacidadUsuarios = 3;
    usuarios = new Usuario[capacidadUsuarios];

    capacidadPrestamos = 5;
    prestamos = new Prestamo[capacidadPrestamos];

    int opcion;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Agregar libro\n";
        cout << "2. Listar libros\n";
        cout << "3. Agregar usuario\n";
        cout << "4. Listar usuarios\n";
        cout << "5. Prestar libro\n";
        cout << "6. Devolver libro\n";
        cout << "7. Buscar libro\n";
        cout << "8. Mostrar prestamos activos\n";
        cout << "9. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            agregarLibro();
            break;
        case 2:
            listarLibros();
            break;
        case 3:
            agregarUsuario();
            break;
        case 4:
            listarUsuarios();
            break;
        case 5:
            prestarLibro();
            break;
        case 6:
            devolverLibro();
            break;
        case 7:
            buscarLibros();
            break;
        case 8:
            mostrarPrestamos();
            break;
        case 9:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 9);

    delete[] libros;
    delete[] usuarios;
    delete[] prestamos;

    return 0;
}
