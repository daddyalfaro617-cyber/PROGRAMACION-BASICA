/*
Explicación de las excepciones:

En el sistema bancario se utilizaron las siguientes excepciones:
- invalid_argument: Se lanza en depositar y retirar cuando el monto es ≤ 0, y al crear cuenta si el número ya existe.
- runtime_error: Se lanza en retirar si el saldo es insuficiente.
- out_of_range: Se lanza en el menú si la opción ingresada no está entre 1 y 6.
Excepción personalizada:
CuentaNoEncontrada: Hereda de runtime_error y se lanza al buscar una cuenta inexistente, 
permitiendo un tratamiento específico.
En el main se capturan en orden (de más específica a general): CuentaNoEncontrada, invalid_argument, runtime_error,
 out_of_range y exception. Esto evita que el programa termine abruptamente y muestra mensajes claros al usuario.
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
using namespace std;

class CuentaNoEncontrada : public runtime_error
{
public:
    CuentaNoEncontrada(const string &mensaje) : runtime_error(mensaje) {}
};

class CuentaBancaria
{
private:
    int numeroCuenta;
    string titular;
    double saldo;

public:
    CuentaBancaria(int numero, const string &tit)
        : numeroCuenta(numero), titular(tit), saldo(0.0) {}

    void depositar(double monto)
    {
        if (monto <= 0)
        {
            throw invalid_argument("El monto a depositar debe ser positivo.");
        }
        saldo += monto;
    }

    void retirar(double monto)
    {
        if (monto <= 0)
        {
            throw invalid_argument("El monto a retirar debe ser positivo.");
        }
        if (monto > saldo)
        {
            throw runtime_error("Saldo insuficiente para realizar el retiro.");
        }
        saldo -= monto;
    }

    double consultarSaldo() const
    {
        return saldo;
    }

    int getNumeroCuenta() const
    {
        return numeroCuenta;
    }

    void mostrar() const
    {
        cout << "Cuenta: " << numeroCuenta << " | Titular: " << titular
             << " | Saldo: $" << saldo << endl;
    }
};

class Banco
{
private:
    vector<CuentaBancaria> cuentas;
    CuentaBancaria &buscarCuentaPorNumero(int numero)
    {
        for (auto &cuenta : cuentas)
        {
            if (cuenta.getNumeroCuenta() == numero)
            {
                return cuenta;
            }
        }
        throw CuentaNoEncontrada("No existe la cuenta numero " + to_string(numero));
    }

public:
    void agregarCuenta()
    {
        int numero;
        string titular;

        cout << "Ingrese numero de cuenta: ";
        cin >> numero;

        try
        {
            buscarCuentaPorNumero(numero);
            throw invalid_argument("Ya existe una cuenta con ese numero.");
        }
        catch (const CuentaNoEncontrada &)
        {
        }

        cout << "Ingrese nombre del titular: ";
        cin.ignore();
        getline(cin, titular);

        cuentas.emplace_back(numero, titular);
        cout << "Cuenta creada exitosamente.\n";
    }

    void depositar()
    {
        int numero;
        double monto;

        cout << "Ingrese numero de cuenta: ";
        cin >> numero;

        CuentaBancaria &cuenta = buscarCuentaPorNumero(numero);

        cout << "Ingrese monto a depositar: $";
        cin >> monto;

        cuenta.depositar(monto);
        cout << "Deposito exitoso. Nuevo saldo: $" << cuenta.consultarSaldo() << endl;
    }

    void retirar()
    {
        int numero;
        double monto;

        cout << "Ingrese numero de cuenta: ";
        cin >> numero;

        CuentaBancaria &cuenta = buscarCuentaPorNumero(numero);

        cout << "Ingrese monto a retirar: $";
        cin >> monto;

        cuenta.retirar(monto);
        cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.consultarSaldo() << endl;
    }

    void consultarSaldo()
    {
        int numero;
        cout << "Ingrese numero de cuenta: ";
        cin >> numero;

        CuentaBancaria &cuenta = buscarCuentaPorNumero(numero);
        cout << "El saldo de la cuenta " << numero << " es: $" << cuenta.consultarSaldo() << endl;
    }

    void mostrarCuentas() const
    {
        if (cuentas.empty())
        {
            cout << "No hay cuentas registradas.\n";
            return;
        }
        cout << "\n--- Listado de cuentas ---\n";
        for (const auto &cuenta : cuentas)
        {
            cuenta.mostrar();
        }
        cout << "--------------------------\n";
    }
};

int main()
{
    Banco banco;
    int opcion;

    do
    {
        cout << "\n========== SISTEMA BANCARIO ==========\n"<<endl;
        cout << "1. Crear cuenta\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Retirar dinero\n";
        cout << "4. Consultar saldo\n";
        cout << "5. Mostrar todas las cuentas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        try
        {
            if (opcion < 1 || opcion > 6)
            {
                throw out_of_range("Opcion invalida. Debe ser entre 1 y 6.");
            }

            switch (opcion)
            {
            case 1:
                banco.agregarCuenta();
                break;
            case 2:
                banco.depositar();
                break;
            case 3:
                banco.retirar();
                break;
            case 4:
                banco.consultarSaldo();
                break;
            case 5:
                banco.mostrarCuentas();
                break;
            case 6:
                cout << "Saliendo del sistema...\n";
                break;
            }
        }
        catch (const CuentaNoEncontrada &e)
        {
            cerr << "Error (cuenta no encontrada): " << e.what() << endl;
        }
        catch (const invalid_argument &e)
        {
            cerr << "Error (argumento invalido): " << e.what() << endl;
        }
        catch (const runtime_error &e)
        {
            cerr << "Error (runtime): " << e.what() << endl;
        }
        catch (const out_of_range &e)
        {
            cerr << "Error (fuera de rango): " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error inesperado: " << e.what() << endl;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (opcion != 6);

    return 0;
}

