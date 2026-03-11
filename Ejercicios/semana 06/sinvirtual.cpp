#include <iostream>
using namespace std;

class Animal {
public:
    void hablar() {
        cout << "Animal generico" << endl;
    }
};

class Perro : public Animal {
public:
    void hablar() {
        cout << "El perro ladra" << endl;
    }
};

int main() {

    Animal* ptr;
    ptr = new Perro();

    ptr->hablar();

    delete ptr;

    return 0;
}