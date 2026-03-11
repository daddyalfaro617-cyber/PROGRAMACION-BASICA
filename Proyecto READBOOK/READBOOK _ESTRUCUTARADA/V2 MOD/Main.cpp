#include "globales.h"
#include "utilidades.h"
#include "archivos.h"
#include "funciones.h"
#include <iostream>
using namespace std;

int main()
{
    cargar();
    int op;
 
    do
    {
        encabezado("SISTEMA READBOOK"); //Menu principal 
        cout << "||        1. Ver catalogo                 ||\n";
        cout << "||        2. Buscar libro                 ||\n";
        cout << "||        3. Registrarse                  ||\n";
        cout << "||        4. Iniciar sesion               ||\n";
        cout << "||        5. Salir                        ||\n";
        cout << "===========================================\n";
        cout << "Seleccione una opcion: ";
        op = leerEntero(1, 5);

        switch (op)
        {
        case 1:
            mostrarCatalogo();
            break;
        case 2:
            buscarLibroMenu();
            break;
        case 3:
            registrar();
            break;
        case 4:
            if (login())
            {
                if (usuarios[usuarioActual].admin)
                    menuAdmin();
                else
                    menuUsuario();
            }
            break;
        }
    } while (op != 5);

    delete[] libros;
    delete[] usuarios;
    delete[] prestamos;

    cout << "\nSaliendo del sistema...\n";
    return 0;
}