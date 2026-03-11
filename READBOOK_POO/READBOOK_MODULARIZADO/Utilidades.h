#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <iostream>
#include <limits>
using namespace std;

void limpiarPantalla();
void pausa();
int leerEntero(int min, int max);
string leerString(const string& mensaje, int maxLong = 50);
bool validarISBN(const string& isbn);
void encabezado(const string& titulo);
string obtenerFechaActual();
int diasTranscurridos(const string& fecha);
int calcularMulta(const string& fechaPrestamo, const string& fechaDevolucion);
int contarPrestamosUsuario(const string& idUsuario); // Auxiliar

#endif