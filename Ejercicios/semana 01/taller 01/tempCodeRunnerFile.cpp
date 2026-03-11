#include <iostream>
#include <string>
using namespace std;

string ISBN[5];
string titulos[5];
string autores[5];
int copias[5];
int totalLibros = 0;

string userID[5];
string nombres[5];
string contrasenias[5];
int totalUsuarios = 0;

int usuarioActual = -1;

void mostrarMenuPrincipal()
{
    cout << "\n........READBOOK......\n";
    cout << "1. Registrarse\n";
    cout << "2. Iniciar sesion\n";
    cout << "3. Ver libros\n";
    cout << "4. Agregar libro\n";
    cout << "5. Salir\n";
    cout << "Opcion: ";
}

void limpiarPantalla()
{
    for (int i = 0; i < 20; i++)
    {
        cout << endl;
    }
}

void registrarUsuario()
{
    if (totalUsuarios >= 5)
    {
        cout << "¡Ya hay 5 usuarios registrados!\n";
        return;
    }

    cout << "\n........REGISTRO.......\n";

    cout << "Tu ID sera: I" << (totalUsuarios + 1) << endl;
    userID[totalUsuarios] = "I" + to_string(totalUsuarios + 1);

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nombres[totalUsuarios]);

    cout << "Contrasenia: ";
    cin >> contrasenias[totalUsuarios];

    totalUsuarios++;
    cout << "¡Usuario registrado!\n";
}

bool iniciarSesion()
{
    string id, contra;

    cout << "\n......INICIAR SESION.....\n";
    cout << "ID: ";
    cin >> id;
    cout << "Contrasenia: ";
    cin >> contra;

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (userID[i] == id && contrasenias[i] == contra)
        {
            usuarioActual = i;
            cout << "¡Hola " << nombres[i] << "!\n";
            return true;
        }
    }

    cout << "ID o contrasena incorrectos\n";
    return false;
}

void mostrarLibros()
{
    if (totalLibros == 0)
    {
        cout << "\nNo hay libros registrados\n";
        return;
    }

    cout << "\n=== LIBROS DISPONIBLES ===\n";
    for (int i = 0; i < totalLibros; i++)
    {
        cout << (i + 1) << ". " << titulos[i] << endl;
        cout << "   Autor: " << autores[i] << endl;
        cout << "   ISBN: " << ISBN[i] << endl;
        cout << "   Copias: " << copias[i] << endl;
        cout << "   -----------------\n";
    }
}

void agregarLibro()
{
    if (totalLibros >= 5)
    {
        cout << "¡Ya hay 5 libros registrados!\n";
        return;
    }

    cout << "\n........AGREGAR LIBRO........\n";

    cout << "ISBN: ";
    cin >> ISBN[totalLibros];

    cout << "Titulo: ";
    cin.ignore();
    getline(cin, titulos[totalLibros]);

    cout << "Autor: ";
    getline(cin, autores[totalLibros]);

    cout << "Copias: ";
    cin >> copias[totalLibros];

    while (copias[totalLibros] <= 0)
    {
        cout << "Debe tener al menos 1 copia: ";
        cin >> copias[totalLibros];
    }

    totalLibros++;
    cout << "¡Libro agregado!\n";
}

void buscarLibro()
{
    string busqueda;

    cout << "\n.....BUSCAR LIBRO......\n";
    cout << "Buscar por titulo: ";
    cin.ignore();
    getline(cin, busqueda);

    bool encontrado = false;

    for (int i = 0; i < totalLibros; i++)
    {
        // Buscar si el título contiene lo que escribió el usuario
        string tituloMin = titulos[i];
        string busquedaMin = busqueda;

        // Convertir a minúsculas (forma simple)
        for (int j = 0; j < tituloMin.length(); j++)
        {
            tituloMin[j] = tolower(tituloMin[j]);
        }
        for (int j = 0; j < busquedaMin.length(); j++)
        {
            busquedaMin[j] = tolower(busquedaMin[j]);
        }

        if (tituloMin.find(busquedaMin) != string::npos)
        {
            cout << "\n¡ENCONTRADO!\n";
            cout << "Titulo: " << titulos[i] << endl;
            cout << "Autor: " << autores[i] << endl;
            cout << "ISBN: " << ISBN[i] << endl;
            cout << "Copias: " << copias[i] << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
    {
        cout << "No se encontro el libro\n";
    }
}

void menuUsuario()
{
    int opcion;

    do
    {
        cout << "\n=== MENU USUARIO ===\n";
        cout << "Usuario: " << nombres[usuarioActual] << endl;
        cout << "1. Ver libros\n";
        cout << "2. Buscar libro\n";
        cout << "3. Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarLibros();
            break;
        case 2:
            buscarLibro();
            break;
        case 3:
            usuarioActual = -1;
            cout << "Sesion cerrada\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 3);
}

void menuAdmin()
{
    int opcion;

    do
    {
        cout << "\n=== MENU ADMINISTRADOR ===\n";
        cout << "1. Ver libros\n";
        cout << "2. Agregar libro\n";
        cout << "3. Buscar libro\n";
        cout << "4. Ver usuarios\n";
        cout << "5. Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarLibros();
            break;
        case 2:
            agregarLibro();
            break;
        case 3:
            buscarLibro();
            break;
        case 4:
            cout << "\n=== USUARIOS REGISTRADOS ===\n";
            for (int i = 0; i < totalUsuarios; i++)
            {
                cout << (i + 1) << ". " << nombres[i]
                     << " (ID: " << userID[i] << ")\n";
            }
            break;
        case 5:
            usuarioActual = -1;
            cout << "Sesion cerrada\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
}
int main()
{
    cout << "........BIENVENIDO A READBOOK......\n";

    userID[0] = "ADMIN";
    nombres[0] = "Administrador";
    contrasenias[0] = "readbook123";
    totalUsuarios = 1;

    ISBN[0] = "001";
    titulos[0] = "El Principito";
    autores[0] = "Antoine de Saint-Exupery";
    copias[0] = 3;
    totalLibros = 1;

    ISBN[1] = "002";
    titulos[1] = "Cien Anios de Soledad";
    autores[1] = "Gabriel Garcia Marquez";
    copias[1] = 2;
    totalLibros = 2;

    int opcion;

    do
    {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrarUsuario();
            break;

        case 2:
            if (iniciarSesion())
            {
                if (userID[usuarioActual] == "admin")
                {
                    menuAdmin();
                }
                else
                {
                    menuUsuario();
                }
            }
            break;

        case 3:
            mostrarLibros();
            break;

        case 4:
            if (usuarioActual != -1 && userID[usuarioActual] == "admin")
            {
                agregarLibro();
            }
            else
            {
                cout << "Solo el admin puede agregar libros\n";
            }
            break;

        case 5:
            cout << "¡Gracias por usar ReadBook!\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 5);

    return 0;
}