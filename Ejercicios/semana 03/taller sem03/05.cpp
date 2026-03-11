#include <iostream>
using namespace std;

int sumaDigitos(int n)
{
    if (n < 0)
        n = -n;
    int suma = 0;
    while (n > 0)
    {
        suma += n % 10;
        n /= 10;
    }
    return suma;
}

int contarDigitos(int n)
{
    if (n < 0)
        n = -n;
    int c = 0;
    if (n == 0)
        return 1;
    while (n > 0)
    {
        c++;
        n /= 10;
    }
    return c;
}

int main()
{
    int M;
    cout << "Ingrese cantidad de consultas: ";
    cin >> M;

    int x;
    for (int i = 1; i <= M; i++)
    {
        cout << "Ingrese x: ";
        cin >> x;

        int suma = sumaDigitos(x);
        int digitos = contarDigitos(x);

        if (suma % 2 == 0 && x % 4 == 0)
        {
            cout << "A" << endl;
        }
        else if (suma % 2 == 1 && x % 6 == 0)
        {
            cout << "B" << endl;
        }
        else if (digitos == 3)
        {
            cout << "C" << endl;
        }
        else
        {
            cout << "D" << endl;
        }
    }

    return 0;
}