#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
private:
    string id;
    string nombre;
    string contrasenia;
    bool admin;

public:
    Usuario();
    Usuario(const string& id, const string& nombre, const string& contrasenia, bool admin);

    // Getters
    string obtenerId() const;
    string obtenerNombre() const;
    string obtenerContrasenia() const;
    bool esAdmin() const;

    // Setters
    void establecerNombre(const string& nombre);
    void establecerContrasenia(const string& contrasenia);

    // Metodos
    void mostrar() const;
    bool verificarContrasenia(const string& contrasenia) const;
};

#endif