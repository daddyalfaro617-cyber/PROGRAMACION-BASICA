#include "Usuario.h"
#include <iostream>

Usuario::Usuario() : id(""), nombre(""), contrasenia(""), admin(false) {}

Usuario::Usuario(const string& id, const string& nombre, const string& contrasenia, bool admin)
    : id(id), nombre(nombre), contrasenia(contrasenia), admin(admin) {}

string Usuario::obtenerId() const { return id; }
string Usuario::obtenerNombre() const { return nombre; }
string Usuario::obtenerContrasenia() const { return contrasenia; }
bool Usuario::esAdmin() const { return admin; }

void Usuario::establecerNombre(const string& nombre) { this->nombre = nombre; }
void Usuario::establecerContrasenia(const string& contrasenia) { this->contrasenia = contrasenia; }

void Usuario::mostrar() const {
    cout << "ID: " << id << " | Nombre: " << nombre << " | Rol: " << (admin ? "Admin" : "Usuario") << endl;
}

bool Usuario::verificarContrasenia(const string& contrasenia) const {
    return this->contrasenia == contrasenia;
}