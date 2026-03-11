#include "Biblioteca.h"
#include "Menu.h"
#include "Utilidades.h"

int main() {
    Biblioteca biblioteca;
    biblioteca.cargarDesdeArchivo();

    menuPrincipal(biblioteca);

    // Liberar memoria automaticamente (vectores)
    return 0;
}