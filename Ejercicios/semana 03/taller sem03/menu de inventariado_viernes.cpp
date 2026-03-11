#include <iostream>
#include <string>
#include <fstream> 
#include <limits>  
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

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void guardarProductos(Producto productos[], int n)
{
    ofstream archivo("inventario.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir archivo para guardar.\n";
        return;
    }
    for (int i = 0; i < n; i++)
    {
        archivo << productos[i].codigo << ";"
                << productos[i].nombre << ";"
                << productos[i].precio << ";"
                << productos[i].stock << "\n";
    }
    archivo.close();
    cout << "Inventario guardado en inventario.txt\n";
}

void cargarProductos(Producto productos[], int &n)
{
    ifstream archivo("inventario.txt");
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir inventario.txt\n";
        return;
    }
    n = 0;
    while (archivo >> productos[n].codigo)
    {
        archivo.ignore(); 
        getline(archivo, productos[n].nombre, ';');
        archivo >> productos[n].precio;
        archivo.ignore();
        archivo >> productos[n].stock;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        n++;
        if (n >= N)
            break;
    }
    archivo.close();
    cout << "Inventario cargado desde inventario.txt\n";
}

int main()
{
    Producto productos[N];
    int opcion;
    int cantidad = N;

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
        cout << "8. Guardar inventario en archivo\n";
        cout << "9. Cargar inventario desde archivo\n";
        cout << "10. Salir\n"
             << endl;
        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrarProductos(productos, cantidad);
            break;
        case 2:
            mostrarProductos(productos, cantidad);
            break;
        case 3:
            buscarPorCodigo(productos, cantidad);
            break;
        case 4:
            buscarPorNombre(productos, cantidad);
            break;
        case 5:
            productoMayorStock(productos, cantidad);
            break;
        case 6:
            productoMasCaro(productos, cantidad);
            break;
        case 7:
            valorInventario(productos, cantidad);
            break;
        case 8:
            guardarProductos(productos, cantidad);
            break;
        case 9:
            cargarProductos(productos, cantidad);
            break;
        }
    } while (opcion != 10);

    return 0;
}