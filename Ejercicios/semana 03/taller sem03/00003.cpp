#include <iostream>
using namespace std;

bool esPrimo(int n) {
    if (n <= 1) return false;
    int div = 2;
    while (div * div <= n) {
        if (n % div == 0) return false;
        div++;
    }
    return true;
}

bool masImparesQuePares(int n) {
    if (n < 0) n = -n; 
    int pares = 0, impares = 0;
    if (n == 0) pares++; 
    while (n > 0) {
        int dig = n % 10;
        if (dig % 2 == 0) pares++;
        else impares++;
        n /= 10;
    }
    return (impares > pares);
}

int main() {
    int N;
    cout << "Ingrese cantidad de numeros: ";
    cin >> N;

    int num;
    int maximo, minimo;
    int cantPrimos = 0;
    int sumaPositivosPares = 0, contPositivosPares = 0;
    int mayorImpares = 0;
    bool existeImpares = false;

    for (int i = 1; i <= N; i++) {
        cout << "Ingrese numero #" << i << ": ";
        cin >> num;

        if (i == 1) { maximo = minimo = num; }
        if (num > maximo) maximo = num;
        if (num < minimo) minimo = num;

        if (esPrimo(num)) cantPrimos++;

        if (num > 0 && num % 2 == 0) {
            sumaPositivosPares += num;
            contPositivosPares++;
        }

        if (masImparesQuePares(num)) {
            if (!existeImpares || num > mayorImpares) {
                mayorImpares = num;
                existeImpares = true;
            }
        }
    }

    cout << "\nMaximo: " << maximo << endl;
    cout << "MMinimo: " << minimo << endl;

    if (cantPrimos > 0) cout << "Cantidad de primos: " << cantPrimos << endl;
    else cout << "Cantidad de primos: NO EXISTE" << endl;

    if (contPositivosPares > 0)
        cout << "Promedio positivos pares: " << (sumaPositivosPares / (float)contPositivosPares) << endl;
    else
        cout << "Promedio positivos pares: NO EXISTE" << endl;

    if (existeImpares)
        cout << "Mayor con más dígitos impares que pares: " << mayorImpares << endl;
    else
        cout << "Mayor con más dígitos impares que pares: NO EXISTE" << endl;

    return 0;
}