#include "utilidades.h"
#include "globales.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

void limpiarPantalla() { //limpia la pantalla de la consola
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() { //pausa la ejecución hasta que el usuario presione ENTER
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEntero(int min, int max) { //lee un número entero dentro de un rango específico, validando la entrada del usuario
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

string leerString(const string& mensaje, int maxLong) { //lee una cadena de texto con una longitud máxima, validando que no esté vacía ni exceda el límite
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

bool validarISBN(const string& isbn) { //valida que el ISBN ingresado tenga un formato correcto (solo dígitos y guiones, con una longitud adecuada)
    string limpio;
    for (char c : isbn) {
        if (isdigit(c))
            limpio += c;
        else if (c != '-')
            return false;
    }
    return limpio.length() >= 10 && limpio.length() <= 13;
}

void encabezado(const string& titulo) { //muestra un encabezado con el título del menú o sección actual, limpiando la pantalla antes de mostrarlo
    limpiarPantalla();
    cout << "\n============================================\n";
    cout << "||         " << titulo << "                ||" << endl;
    cout << "============================================\n";
}

string obtenerFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    ostringstream fecha;
    fecha << put_time(now, "%Y-%m-%d");
    return fecha.str();
}

int diasTranscurridos(const string& fecha) {
    // Convertir fecha string (YYYY-MM-DD) a tiempo
    int y, m, d;
    sscanf(fecha.c_str(), "%d-%d-%d", &y, &m, &d);
    tm t = {0};
    t.tm_year = y - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d;
    time_t t1 = mktime(&t);
    time_t t2 = time(nullptr);
    double diff = difftime(t2, t1) / (60 * 60 * 24);
    return static_cast<int>(diff);
}

int calcularMulta(const string& fechaPrestamo) {
    int dias = diasTranscurridos(fechaPrestamo);
    int retraso = dias - 7; // suponemos 7 días de préstamo
    return (retraso > 0) ? retraso * 1 : 0; // 1 unidad monetaria por día
}

int contarPrestamosUsuario(const string& idUsuario) {
    int count = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].idUsuario == idUsuario)
            count++;
    }
    return count;
}