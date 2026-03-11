#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <limits>
using namespace std;

void limpiarPantalla();
void pausa();
int leerEntero(int min, int max);
string leerString(const string& mensaje, int maxLong = 50);
bool validarISBN(const string& isbn);
void encabezado(const string& titulo);

// Plantilla para agregar elementos
template <typename T>
void agregar(T *&arr, int &total, const T &dato) {
    T *nuevo = new T[total + 1];
    for (int i = 0; i < total; i++)
        nuevo[i] = arr[i];
    nuevo[total] = dato;
    delete[] arr;
    arr = nuevo;
    total++;
}

// Funciones de fecha y multas
string obtenerFechaActual();
int diasTranscurridos(const string& fecha);
int calcularMulta(const string& fechaPrestamo);

// Función auxiliar para contar préstamos de un usuario
int contarPrestamosUsuario(const string& idUsuario);

#endif