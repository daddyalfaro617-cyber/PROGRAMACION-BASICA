#include <iostream>
using namespace std;

int main() {
    const int n = 7;
    int datos[n];

    cout << "Ingrese los datos de los " << n << " dias: ";
    for (int i = 0; i < n; i++) {
        cin >> datos[i];
    }

    int rachaActual = 0;
    int rachaMaxima = 0;

    for (int i = 0; i < n; i++) {
        if (datos[i] > 0) {
            rachaActual++; 
            if (rachaActual > rachaMaxima) {
                rachaMaxima = rachaActual; 
            }
        } else {
            rachaActual = 0; 
        }
    }

    cout << "Mayor racha positiva: " << rachaMaxima << " dias" << endl;

    return 0;
}