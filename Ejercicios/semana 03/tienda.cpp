#include <iostream>
#include <string>
using namespace std;

const int N = 5;

struct Producto
{
    int codigo;
    string nombre;
    float precio;
    int stock;
};

void registrarProductos(Producto productos[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "\nProducto " << i + 1 << endl;

        cout << "Codigo: ";
        cin >> productos[i].codigo;

        cin.ignore();
        cout << "Nombre: ";
        getline(cin, productos[i].nombre);

        do
        {
            cout << "Precio: ";
            cin >> productos[i].precio;
        } while (productos[i].precio <= 0);

        do
        {
            cout << "Stock: ";
            cin >> productos[i].stock;
        } while (productos[i].stock < 0);
    }
}

void mostrarProductos(Producto productos[], int n)
{
    cout << "\nLISTA DE PRODUCTOS\n";
    cout << "Codigo | Nombre | Precio | Stock\n";
    for (int i = 0; i < n; i++)
    {
        cout << productos[i].codigo << " | "
             << productos[i].nombre << " | $"
             << productos[i].precio << " | "
             << productos[i].stock << " unidades\n";
    }
}

void buscarPorCodigo(Producto productos[], int n)
{
    int codigo;
    cout << "Ingrese codigo: ";
    cin >> codigo;

    for (int i = 0; i < n; i++)
    {
        if (productos[i].codigo == codigo)
        {
            cout << "Producto encontrado:\n";
            cout << productos[i].codigo << " | "
                 << productos[i].nombre << " | $"
                 << productos[i].precio << " | "
                 << productos[i].stock << endl;
            return;
        }
    }
    cout << "No encontrado\n";
}

void buscarPorNombre(Producto productos[], int n)
{
    string nombre;
    cin.ignore();
    cout << "Ingrese nombre: ";
    getline(cin, nombre);

    for (int i = 0; i < n; i++)
    {
        if (productos[i].nombre == nombre)
        {
            cout << "Producto encontrado:\n";
            cout << productos[i].codigo << " | "
                 << productos[i].nombre << " | $"
                 << productos[i].precio << " | "
                 << productos[i].stock << endl;
            return;
        }
    }
    cout << "No encontrado\n";
}

void productoMayorStock(Producto productos[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (productos[i].stock > productos[pos].stock)
        {
            pos = i;
        }
    }
    cout << "Producto con mayor stock:\n";
    cout << productos[pos].nombre << " - "
         << productos[pos].stock << " unidades\n";
}

void productoMasCaro(Producto productos[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (productos[i].precio > productos[pos].precio)
        {
            pos = i;
        }
    }
    cout << "Producto mas caro:\n";
    cout << productos[pos].nombre << " - $"
         << productos[pos].precio << endl;
}

void valorInventario(Producto productos[], int n)
{
    double total = 0;
    for (int i = 0; i < n; i++)
    {
        total += productos[i].precio * productos[i].stock;
    }
    cout << "Valor total del inventario: $" << total << endl;
}

int main()
{
    Producto productos[N];
    int opcion;

    do
    {

        cout << "\nBIENVENIDO A TIENDA A&G PRECIOS ESPECIALES\n"
             << endl;
        cout << ".................MENU DE OPCIONES.................\n"
             << endl;
        cout << "1. Registrar productos\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar producto por codigo\n";
        cout << "4. Buscar producto por nombre\n";
        cout << "5. Mostrar producto con mayor stock\n";
        cout << "6. Mostrar producto mas caro\n";
        cout << "7. Calcular valor total del inventario\n";
        cout << "8. Salir\n"
             << endl;
        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrarProductos(productos, N);
            break;
        case 2:
            mostrarProductos(productos, N);
            break;
        case 3:
            buscarPorCodigo(productos, N);
            break;
        case 4:
            buscarPorNombre(productos, N);
            break;
        case 5:
            productoMayorStock(productos, N);
            break;
        case 6:
            productoMasCaro(productos, N);
            break;
        case 7:
            valorInventario(productos, N);
            break;
        }
    }
        while (opcion != 8)
            ;

        return 0;
    }
