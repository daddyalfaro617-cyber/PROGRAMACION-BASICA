#include <iostream>
 using namespace std;
 int main(){

    int hora;
    cout << "INGRESE LA HORA: ";
    cout << "(o-23): ";
    cin >> hora;

    if (hora >= 6 && hora <= 11){
        cout << "BUENOS DIAS" << endl;
    }
    else if (hora >= 12 && hora <= 18){
        cout << "BUENAS TARDES" << endl;
    }
    else if (hora >= 19 && hora <= 23){
        cout << "BUENAS NOCHES" << endl;
    }
    else {
        cout << "HORA NO VALIDA" << endl;
    }
    return 0;
    
 }