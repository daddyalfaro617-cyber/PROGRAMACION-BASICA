#include "Utilidades.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdio>

void limpiarPantalla() {
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

string leerString(const string& mensaje, int maxLong) {
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

bool validarISBN(const string& isbn) {
    string limpio;
    for (char c : isbn) {
        if (isdigit(c))
            limpio += c;
        else if (c != '-')
            return false;
    }
    return limpio.length() >= 10 && limpio.length() <= 13;
}

void encabezado(const string& titulo) {
    limpiarPantalla();
    cout << "\n============================================\n";
    cout << "||         " << titulo;
    // Rellenar con espacios para alinear (simple)
    int espacios = 40 - titulo.length() - 6;
    for (int i = 0; i < espacios; ++i) cout << " ";
    cout << "||" << endl;
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

int calcularMulta(const string& fechaPrestamo, const string& fechaDevolucion) {
    // Usamos la fecha actual como fechaDevolucion si no se provee (para simplificar)
    int dias = diasTranscurridos(fechaPrestamo);
    int retraso = dias - 7; // 7 dias de prestamo
    return (retraso > 0) ? retraso * 1 : 0;
}