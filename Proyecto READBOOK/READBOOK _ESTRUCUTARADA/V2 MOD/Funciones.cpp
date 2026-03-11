#include "funciones.h"
#include "globales.h"
#include "utilidades.h"
#include "archivos.h"
#include <iostream>
using namespace std;

// ====================== BÚSQUEDAS ======================
int buscarLibro(const string& isbn) {
    for (int i = 0; i < totalLibros; i++)
        if (libros[i].isbn == isbn)
            return i;
    return -1;
}

int buscarPrestamo(const string& isbn, int idUsuarioIdx) {
    if (idUsuarioIdx < 0 || idUsuarioIdx >= totalUsuarios) return -1;
    const string& idUsr = usuarios[idUsuarioIdx].id;
    for (int i = 0; i < totalPrestamos; i++)
        if (prestamos[i].idUsuario == idUsr && prestamos[i].isbn == isbn)
            return i;
    return -1;
}

int buscarUsuarioPorId(const string& id) {
    for (int i = 0; i < totalUsuarios; i++)
        if (usuarios[i].id == id)
            return i;
    return -1;
}

// ====================== FUNCIONES ========================
void mostrarCatalogo() { //muestra el catálogo completo de libros
    encabezado("CATALOGO DE LIBROS");
    if (totalLibros == 0) {
        cout << "No hay libros registrados.\n";
        pausa();
        return;
    }

    for (int i = 0; i < totalLibros; i++)
        cout << libros[i].isbn << " | " << libros[i].titulo << " | " << libros[i].autor << " | Stock: " << libros[i].cantidad << endl;
    pausa();
}

void buscarLibroMenu() { // permite buscar libros por título o ISBN
    encabezado("BUSCAR LIBRO");
    string dato = leerString("Ingrese titulo o ISBN: ", 100);

    bool encontrado = false;
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].isbn == dato ||
            libros[i].titulo.find(dato) != string::npos) {
            cout << "\n" << libros[i].isbn << " | " << libros[i].titulo << " | " << libros[i].autor << " | Stock: " << libros[i].cantidad << endl;
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No se encontraron resultados.\n";
    pausa();
}

void registrar() { //permite registrar un nuevo usuario
    encabezado("REGISTRO DE USUARIO");
    Usuario u;
    u.id = "U" + to_string(totalUsuarios + 1);
    u.nombre = leerString("Nombre: ");
    u.pass = leerString("Contrasenia: ");
    u.admin = false;
    agregar(usuarios, totalUsuarios, u);
    guardar();
    cout << "Usuario registrado con ID: " << u.id << endl;
    pausa();
}

bool login() { //permite iniciar sesión a un usuario existente
    encabezado("INICIAR SESION");
    int intentos = 3;
    while (intentos-- > 0) {
        string id, pass;
        cout << "ID: ";
        getline(cin, id);
        cout << "Contrasenia: ";
        getline(cin, pass);

        for (int i = 0; i < totalUsuarios; i++) {
            if (usuarios[i].id == id && usuarios[i].pass == pass) {
                usuarioActual = i;
                return true;
            }
        }
        cout << "Credenciales incorrectas. Intentos restantes: " << intentos << endl;
    }
    cout << "Demasiados intentos fallidos.\n";
    pausa();
    return false;
}

void agregarLibro() { //permite al administrador agregar un nuevo libro al catálogo
    encabezado("AGREGAR LIBRO");
    Libro l;
    do {
        l.isbn = leerString("ISBN: ", 20);
        if (!validarISBN(l.isbn))
            cout << "ISBN invalido. Debe contener solo digitos y guiones, y tener entre 10 y 13 digitos.\n";
    } while (!validarISBN(l.isbn));

    if (buscarLibro(l.isbn) != -1) {
        cout << "El ISBN ya existe.\n";
        pausa();
        return;
    }

    l.titulo = leerString("Titulo: ");
    l.autor = leerString("Autor: ");
    cout << "Cantidad: ";
    l.cantidad = leerEntero(0, 100000);
    agregar(libros, totalLibros, l);
    guardar();
    cout << "Libro agregado correctamente.\n";
    pausa();
}

void prestar() { //permite a un usuario prestar un libro, verificando stock y límites de préstamo
    encabezado("PRESTAR LIBRO");
    string isbn = leerString("ISBN: ", 20);
    if (!validarISBN(isbn)) {
        cout << "ISBN invalido.\n";
        pausa();
        return;
    }

    int pos = buscarLibro(isbn);
    if (pos == -1) {
        cout << "Libro no encontrado.\n";
        pausa();
        return;
    }
    if (libros[pos].cantidad == 0) {
        cout << "No hay stock disponible.\n";
        pausa();
        return;
    }

    // Verificar si ya tiene este libro prestado
    int pr = buscarPrestamo(isbn, usuarioActual);
    if (pr != -1) {
        cout << "Ya tienes un prestamo de este libro. No puedes pedir otro ejemplar del mismo.\n";
        pausa();
        return;
    }

    // Contar préstamos actuales
    string idUsr = usuarios[usuarioActual].id;
    int prestamosActuales = contarPrestamosUsuario(idUsr);

    if (prestamosActuales >= 3) {
        cout << "Has alcanzado el limite maximo de 3 prestamos.\n";
        pausa();
        return;
    }

    // Obtener fecha actual
    string fecha = obtenerFechaActual();

    // Realizar préstamo
    Prestamo nuevo = {idUsr, isbn, 1, fecha};
    agregar(prestamos, totalPrestamos, nuevo);
    libros[pos].cantidad -= 1;
    guardar();

    cout << "Prestamo registrado el " << fecha << ". Ahora tienes " << (prestamosActuales + 1) << " prestamo(s).\n";
    pausa();
}

void devolver() { //permite a un usuario devolver un libro, calculando multas por retraso y actualizando el historial
    encabezado("DEVOLVER LIBRO");
    string isbn = leerString("ISBN: ", 20);
    if (!validarISBN(isbn)) {
        cout << "ISBN invalido.\n";
        pausa();
        return;
    }

    int pr = buscarPrestamo(isbn, usuarioActual);
    if (pr == -1) {
        cout << "No tienes este libro prestado.\n";
        pausa();
        return;
    }

    // Calcular multa
    int multa = calcularMulta(prestamos[pr].fechaPrestamo);
    if (multa > 0) {
        cout << "El prestamo tiene " << multa << " dias de retraso. Multa: $" << multa << endl;
        cout << "¿Desea pagar la multa y devolver? (s/n): ";
        string resp;
        getline(cin, resp);
        if (resp != "s" && resp != "S") {
            cout << "Devolucion cancelada.\n";
            pausa();
            return;
        }
        cout << "Pago realizado. Procediendo con la devolucion.\n";
    }

    // Registrar en historial
    Historial hist;
    hist.idUsuario = prestamos[pr].idUsuario;
    hist.isbn = prestamos[pr].isbn;
    hist.cantidad = prestamos[pr].cantidad;
    hist.fechaPrestamo = prestamos[pr].fechaPrestamo;
    hist.fechaDevolucion = obtenerFechaActual();
    agregar(historial, totalHistorial, hist);

    // Actualizar stock
    int pos = buscarLibro(isbn);
    libros[pos].cantidad += prestamos[pr].cantidad;

    // Eliminar préstamo
    Prestamo *temp = new Prestamo[totalPrestamos - 1];
    for (int i = 0, j = 0; i < totalPrestamos; i++) {
        if (i != pr)
            temp[j++] = prestamos[i];
    }
    delete[] prestamos;
    prestamos = temp;
    totalPrestamos--;

    guardar();
    cout << "Devolucion realizada. Gracias.\n";
    pausa();
}

void mostrarPerfil() { //permite al usuario ver su información personal y los libros que tiene prestados actualmente
    encabezado("MI PERFIL");
    Usuario &u = usuarios[usuarioActual];
    cout << "ID: " << u.id << endl;
    cout << "Nombre: " << u.nombre << endl;
    cout << "Rol: " << (u.admin ? "Administrador" : "Usuario") << endl;

    cout << "\nLibros prestados actualmente:\n";
    string idUsr = u.id;
    bool tienePrestamos = false;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].idUsuario == idUsr) {
            int idxLibro = buscarLibro(prestamos[i].isbn);
            string titulo = (idxLibro != -1) ? libros[idxLibro].titulo : "Desconocido";
            cout << " - ISBN: " << prestamos[i].isbn
                 << " | Titulo: " << titulo
                 << " | Cantidad: " << prestamos[i].cantidad << endl;
            tienePrestamos = true;
        }
    }
    if (!tienePrestamos) cout << "No tienes libros prestados.\n";
    pausa();
}

void mostrarHistorialUsuario() { //permite a un usuario ver su historial completo de préstamos, incluyendo los libros prestados, las fechas de préstamo y devolución, y cualquier multa pagada por retrasos
    encabezado("MI HISTORIAL DE PRESTAMOS");
    string idUsr = usuarios[usuarioActual].id;
    bool hay = false;
    for (int i = 0; i < totalHistorial; i++) {
        if (historial[i].idUsuario == idUsr) {
            int idxLibro = buscarLibro(historial[i].isbn);
            string titulo = (idxLibro != -1) ? libros[idxLibro].titulo : "Desconocido";
            cout << "Libro: " << titulo << " (" << historial[i].isbn << ")\n";
            cout << "  Fecha prestamo: " << historial[i].fechaPrestamo;
            cout << "  Fecha devolucion: " << historial[i].fechaDevolucion;
            cout << "  Cantidad: " << historial[i].cantidad << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay registros en tu historial.\n";
    pausa();
}

void mostrarHistorialCompleto() { //permite al administrador ver el historial completo de todos los préstamos realizados en la biblioteca, con detalles de cada préstamo y devolución
    encabezado("HISTORIAL COMPLETO DE PRESTAMOS");
    if (totalHistorial == 0) {
        cout << "No hay registros en el historial.\n";
        pausa();
        return;
    }
    for (int i = 0; i < totalHistorial; i++) {
        int idxUser = buscarUsuarioPorId(historial[i].idUsuario);
        string nombre = (idxUser != -1) ? usuarios[idxUser].nombre : "Desconocido";
        int idxLibro = buscarLibro(historial[i].isbn);
        string titulo = (idxLibro != -1) ? libros[idxLibro].titulo : "Desconocido";
        cout << "Usuario: " << nombre << " (" << historial[i].idUsuario << ")\n";
        cout << "  Libro: " << titulo << " (" << historial[i].isbn << ")\n";
        cout << "  Fecha prestamo: " << historial[i].fechaPrestamo;
        cout << "  Fecha devolucion: " << historial[i].fechaDevolucion;
        cout << "  Cantidad: " << historial[i].cantidad << endl;
    }
    pausa();
}

void cambiarPassword() { //permite al usuario cambiar su contraseña actual, solicitando la contraseña actual para confirmación y validando la nueva contraseña
    encabezado("CAMBIAR CONTRASENIA");
    string passActual = leerString("Ingrese su contrasenia actual: ");
    if (usuarios[usuarioActual].pass != passActual) {
        cout << "Contrasenia incorrecta.\n";
        pausa();
        return;
    }
    string nueva = leerString("Nueva contrasenia: ");
    string confirmar = leerString("Confirme nueva contrasenia: ");
    if (nueva != confirmar) {
        cout << "Las contrasenias no coinciden.\n";
        pausa();
        return;
    }
    usuarios[usuarioActual].pass = nueva;
    guardar();
    cout << "Contrasenia cambiada exitosamente.\n";
    pausa();
}

void listarUsuarios() { //permite al administrador ver una lista de todos los usuarios registrados, mostrando su ID, nombre y rol (administrador o usuario)
    encabezado("LISTA DE USUARIOS");
    if (totalUsuarios == 0) {
        cout << "No hay usuarios registrados.\n";
        pausa();
        return;
    }
    for (int i = 0; i < totalUsuarios; i++) {
        cout << "ID: " << usuarios[i].id
             << " | Nombre: " << usuarios[i].nombre
             << " | Rol: " << (usuarios[i].admin ? "Admin" : "Usuario") << endl;
    }
    pausa();
}

void eliminarUsuario() { //permite al administrador eliminar un usuario existente, verificando que no tenga préstamos activos y que no sea el mismo administrador que está intentando eliminarse
    encabezado("ELIMINAR USUARIO");
    string id = leerString("Ingrese ID del usuario a eliminar: ");
    int idx = buscarUsuarioPorId(id);
    if (idx == -1) {
        cout << "Usuario no encontrado.\n";
        pausa();
        return;
    }
    if (idx == usuarioActual) {
        cout << "No puedes eliminarte a ti mismo.\n";
        pausa();
        return;
    }
    // Verificar si tiene préstamos activos
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].idUsuario == id) {
            cout << "No se puede eliminar: el usuario tiene prestamos activos.\n";
            pausa();
            return;
        }
    }
    // Eliminar usuario
    Usuario *temp = new Usuario[totalUsuarios - 1];
    for (int i = 0, j = 0; i < totalUsuarios; i++) {
        if (i != idx)
            temp[j++] = usuarios[i];
    }
    delete[] usuarios;
    usuarios = temp;
    totalUsuarios--;
    guardar();
    cout << "Usuario eliminado.\n";
    pausa();
}

void editarLibro() { //permite al administrador editar la información de un libro existente, como título, autor o cantidad disponible, buscando por ISBN
    encabezado("EDITAR LIBRO");
    string isbn = leerString("Ingrese ISBN del libro a editar: ");
    int idx = buscarLibro(isbn);
    if (idx == -1) {
        cout << "Libro no encontrado.\n";
        pausa();
        return;
    }
    Libro &l = libros[idx];
    cout << "Datos actuales:\n";
    cout << "ISBN: " << l.isbn << endl;
    cout << "Titulo: " << l.titulo << endl;
    cout << "Autor: " << l.autor << endl;
    cout << "Cantidad: " << l.cantidad << endl;

    cout << "\nIngrese nuevos datos (deje vacio para no modificar):\n";
    string nuevoTitulo = leerString("Nuevo titulo: ", 50);
    if (!nuevoTitulo.empty()) l.titulo = nuevoTitulo;

    string nuevoAutor = leerString("Nuevo autor: ", 50);
    if (!nuevoAutor.empty()) l.autor = nuevoAutor;

    cout << "Nueva cantidad (ingrese -1 para no modificar): ";
    int nuevaCant = leerEntero(-1, 100000);
    if (nuevaCant != -1) l.cantidad = nuevaCant;

    guardar();
    cout << "Libro actualizado.\n";
    pausa();
}

void eliminarLibro() { //permite al administrador eliminar un libro existente del catálogo, verificando que no tenga préstamos activos
    encabezado("ELIMINAR LIBRO");
    string isbn = leerString("Ingrese ISBN del libro a eliminar: ");
    int idx = buscarLibro(isbn);
    if (idx == -1) {
        cout << "Libro no encontrado.\n";
        pausa();
        return;
    }
    // Verificar si está prestado
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].isbn == isbn) {
            cout << "No se puede eliminar: el libro tiene prestamos activos.\n";
            pausa();
            return;
        }
    }
    // Eliminar libro
    Libro *temp = new Libro[totalLibros - 1];
    for (int i = 0, j = 0; i < totalLibros; i++) {
        if (i != idx)
            temp[j++] = libros[i];
    }
    delete[] libros;
    libros = temp;
    totalLibros--;
    guardar();
    cout << "Libro eliminado.\n";
    pausa();
}

void reportePrestamos() { //permite al administrador generar un reporte de todos los préstamos activos, mostrando el usuario, el libro prestado y la fecha del préstamo
    encabezado("REPORTE DE PRESTAMOS ACTIVOS");
    if (totalPrestamos == 0) {
        cout << "No hay prestamos activos.\n";
        pausa();
        return;
    }
    cout << "Total de prestamos: " << totalPrestamos << endl;
    cout << "Lista de prestamos:\n";
    for (int i = 0; i < totalPrestamos; i++) {
        int idxLibro = buscarLibro(prestamos[i].isbn);
        string titulo = (idxLibro != -1) ? libros[idxLibro].titulo : "Desconocido";
        int idxUser = buscarUsuarioPorId(prestamos[i].idUsuario);
        string nombre = (idxUser != -1) ? usuarios[idxUser].nombre : "Desconocido";
        cout << "Usuario: " << nombre << " (" << prestamos[i].idUsuario << ") | "
             << "Libro: " << titulo << " (" << prestamos[i].isbn << ") | "
             << "Cantidad: " << prestamos[i].cantidad << endl;
    }
    pausa();
}

// ====================== MENÚS ======================
void menuUsuario() {
    int op;
    do {
        encabezado("MENU USUARIO");
        cout << "||       1. Ver catalogo                  ||\n";
        cout << "||       2. Buscar libro                  ||\n";
        cout << "||       3. Prestar libro                 ||\n";
        cout << "||       4. Devolver libro                ||\n";
        cout << "||       5. Ver mi perfil                 ||\n";
        cout << "||       6. Ver mi historial              ||\n";          
        cout << "||       7. Cambiar contrasenia           ||\n";
        cout << "||       8. Cerrar sesion                 ||\n";
        cout << "===========================================\n";
        cout << "Seleccione una opcion: ";
        op = leerEntero(1, 8);

        switch (op) {
            case 1: mostrarCatalogo(); break;
            case 2: buscarLibroMenu(); break;
            case 3: prestar(); break;
            case 4: devolver(); break;
            case 5: mostrarPerfil(); break;
            case 6: mostrarHistorialUsuario(); break; 
            case 7: cambiarPassword(); break;
        }
    } while (op != 8);
    usuarioActual = -1;
}

void menuAdmin() {
    int op;
    do {
        encabezado("MENU ADMINISTRADOR");
        cout << "||       1. Agregar libro                 ||\n";
        cout << "||       2. Ver catalogo                  ||\n";
        cout << "||       3. Buscar libro                  ||\n";
        cout << "||       4. Listar usuarios               ||\n";
        cout << "||       5. Eliminar usuario              ||\n";
        cout << "||       6. Editar libro                  ||\n";
        cout << "||       7. Eliminar libro                ||\n";
        cout << "||       8. Reporte de prestamos          ||\n";
        cout << "||       9. Ver historial completo        ||\n";    
        cout << "||       10. Cambiar mi contrasenia       ||\n";
        cout << "||       11. Cerrar sesion                ||\n";
        cout << "===========================================\n";
        cout << "Seleccione una opcion: ";
        op = leerEntero(1, 11);

        switch (op) {
            case 1: agregarLibro(); break;
            case 2: mostrarCatalogo(); break;
            case 3: buscarLibroMenu(); break;
            case 4: listarUsuarios(); break;
            case 5: eliminarUsuario(); break;
            case 6: editarLibro(); break;
            case 7: eliminarLibro(); break;
            case 8: reportePrestamos(); break;
            case 9: mostrarHistorialCompleto(); break; 
            case 10: cambiarPassword(); break;
        }
    } while (op != 11);
    usuarioActual = -1;
}