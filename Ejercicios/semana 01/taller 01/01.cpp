#include <iostream>
#include <string>
using namespace std;

// ================= VARIABLES GLOBALES =================
// Solo 5 libros y 5 usuarios para ser simple
string ISBN[5];
string titulos[5];
string autores[5];
int copias[5];
int totalLibros = 0;

string userID[5];
string nombres[5];
string contrasenas[5];
int totalUsuarios = 0;

int usuarioActual = -1;  // -1 significa que nadie ha iniciado sesión

// ================= FUNCIONES BÁSICAS =================
void mostrarMenuPrincipal() {
    cout << "\n=== BIBLIOTECA SIMPLE ===\n";
    cout << "1. Registrarse\n";
    cout << "2. Iniciar sesión\n";
    cout << "3. Ver libros\n";
    cout << "4. Agregar libro\n";
    cout << "5. Salir\n";
    cout << "Opcion: ";
}

void limpiarPantalla() {
    // Simular limpieza de pantalla
    for (int i = 0; i < 20; i++) {
        cout << endl;
    }
}

// ================= USUARIOS =================
void registrarUsuario() {
    if (totalUsuarios >= 5) {
        cout << "¡Ya hay 5 usuarios registrados!\n";
        return;
    }
    
    cout << "\n=== REGISTRO ===\n";
    
    cout << "Tu ID sera: U" << (totalUsuarios + 1) << endl;
    userID[totalUsuarios] = "U" + to_string(totalUsuarios + 1);
    
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nombres[totalUsuarios]);
    
    cout << "Contrasena: ";
    cin >> contrasenas[totalUsuarios];
    
    totalUsuarios++;
    cout << "¡Usuario registrado!\n";
}

bool iniciarSesion() {
    string id, contra;
    
    cout << "\n=== INICIAR SESION ===\n";
    cout << "ID: ";
    cin >> id;
    cout << "Contrasena: ";
    cin >> contra;
    
    // Buscar usuario
    for (int i = 0; i < totalUsuarios; i++) {
        if (userID[i] == id && contrasenas[i] == contra) {
            usuarioActual = i;  // Guardar quién inició sesión
            cout << "¡Hola " << nombres[i] << "!\n";
            return true;
        }
    }
    
    cout << "ID o contrasena incorrectos\n";
    return false;
}

// ================= LIBROS =================
void mostrarLibros() {
    if (totalLibros == 0) {
        cout << "\nNo hay libros registrados\n";
        return;
    }
    
    cout << "\n=== LIBROS DISPONIBLES ===\n";
    for (int i = 0; i < totalLibros; i++) {
        cout << (i + 1) << ". " << titulos[i] << endl;
        cout << "   Autor: " << autores[i] << endl;
        cout << "   ISBN: " << ISBN[i] << endl;
        cout << "   Copias: " << copias[i] << endl;
        cout << "   -----------------\n";
    }
}

void agregarLibro() {
    if (totalLibros >= 5) {
        cout << "¡Ya hay 5 libros registrados!\n";
        return;
    }
    
    cout << "\n=== AGREGAR LIBRO ===\n";
    
    cout << "ISBN: ";
    cin >> ISBN[totalLibros];
    
    cout << "Titulo: ";
    cin.ignore();
    getline(cin, titulos[totalLibros]);
    
    cout << "Autor: ";
    getline(cin, autores[totalLibros]);
    
    cout << "Copias: ";
    cin >> copias[totalLibros];
    
    // Validar que haya al menos 1 copia
    while (copias[totalLibros] <= 0) {
        cout << "Debe tener al menos 1 copia: ";
        cin >> copias[totalLibros];
    }
    
    totalLibros++;
    cout << "¡Libro agregado!\n";
}

void buscarLibro() {
    string busqueda;
    
    cout << "\n=== BUSCAR LIBRO ===\n";
    cout << "Buscar por titulo: ";
    cin.ignore();
    getline(cin, busqueda);
    
    bool encontrado = false;
    
    for (int i = 0; i < totalLibros; i++) {
        // Buscar si el título contiene lo que escribió el usuario
        string tituloMin = titulos[i];
        string busquedaMin = busqueda;
        
        // Convertir a minúsculas (forma simple)
        for (int j = 0; j < tituloMin.length(); j++) {
            tituloMin[j] = tolower(tituloMin[j]);
        }
        for (int j = 0; j < busquedaMin.length(); j++) {
            busquedaMin[j] = tolower(busquedaMin[j]);
        }
        
        if (tituloMin.find(busquedaMin) != string::npos) {
            cout << "\n¡ENCONTRADO!\n";
            cout << "Titulo: " << titulos[i] << endl;
            cout << "Autor: " << autores[i] << endl;
            cout << "ISBN: " << ISBN[i] << endl;
            cout << "Copias: " << copias[i] << endl;
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        cout << "No se encontro el libro\n";
    }
}

// ================= MENÚ DE USUARIO =================
void menuUsuario() {
    int opcion;
    
    do {
        cout << "\n=== MENU USUARIO ===\n";
        cout << "Usuario: " << nombres[usuarioActual] << endl;
        cout << "1. Ver libros\n";
        cout << "2. Buscar libro\n";
        cout << "3. Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
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

// ================= MENÚ DE ADMIN =================
void menuAdmin() {
    int opcion;
    
    do {
        cout << "\n=== MENU ADMINISTRADOR ===\n";
        cout << "1. Ver libros\n";
        cout << "2. Agregar libro\n";
        cout << "3. Buscar libro\n";
        cout << "4. Ver usuarios\n";
        cout << "5. Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
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
                for (int i = 0; i < totalUsuarios; i++) {
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

// ================= PROGRAMA PRINCIPAL =================
int main() {
    cout << "=== BIENVENIDO A BIBLIOTECA SIMPLE ===\n";
    
    // Crear admin por defecto
    userID[0] = "admin";
    nombres[0] = "Administrador";
    contrasenas[0] = "123";
    totalUsuarios = 1;
    
    // Agregar algunos libros de ejemplo
    ISBN[0] = "001";
    titulos[0] = "El Principito";
    autores[0] = "Antoine de Saint-Exupery";
    copias[0] = 3;
    totalLibros = 1;
    
    ISBN[1] = "002";
    titulos[1] = "Cien Anos de Soledad";
    autores[1] = "Gabriel Garcia Marquez";
    copias[1] = 2;
    totalLibros = 2;
    
    int opcion;
    
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        
        switch(opcion) {
            case 1:  // Registrarse
                registrarUsuario();
                break;
                
            case 2:  // Iniciar sesión
                if (iniciarSesion()) {
                    if (userID[usuarioActual] == "admin") {
                        menuAdmin();
                    } else {
                        menuUsuario();
                    }
                }
                break;
                
            case 3:  // Ver libros
                mostrarLibros();
                break;
                
            case 4:  // Agregar libro (solo admin puede)
                if (usuarioActual != -1 && userID[usuarioActual] == "admin") {
                    agregarLibro();
                } else {
                    cout << "Solo el admin puede agregar libros\n";
                }
                break;
                
            case 5:  // Salir
                cout << "¡Gracias por usar Biblioteca Simple!\n";
                break;
                
            default:
                cout << "Opcion invalida\n";
        }
        
    } while (opcion != 5);
    
    return 0;
}