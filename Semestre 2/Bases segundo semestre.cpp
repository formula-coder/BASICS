/*Estructuras: Es una coleccion de uno a mas tipos de elementos denominados campos, cada uno de los cuales puede ser un tipo de dato diferente.*/
#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Coleccion {
    string titulo;
    string artista;
    int numCanciones;
    float precio;
    string fecha_compra;
};

int main() {
    Coleccion colecciones[30];
    int cantidad;
cout <<"Ingrese la cantidad de artistas que desea registrar: "<<endl;
cin >> cantidad;

    for (int i = 0; i < cantidad; ++i) {
        cout << "Ingrese el nombre del artista: ";
        getline(cin, colecciones[i].artista);

        cout << "Ingrese el titulo del disco: ";
        getline(cin, colecciones[i].titulo);

        cout << "Ingrese el numero de canciones: ";
        cin >> colecciones[i].numCanciones;

        cout << "Ingrese el precio del disco: ";
        cin >> colecciones[i].precio;

        // Limpiar el salto de linea pendiente antes de usar getline nuevamente
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Ingrese la fecha de compra: ";
        getline(cin, colecciones[i].fecha_compra);
    }

    for (int j = 0; j < cantidad; ++j) {
        cout << "Artista: " << colecciones[j].artista << endl;
        cout << "Titulo: " << colecciones[j].titulo << endl;
        cout << "Numero de canciones: " << colecciones[j].numCanciones << endl;
        cout << "Precio: " << colecciones[j].precio << endl;
        cout << "Fecha: " << colecciones[j].fecha_compra << endl;
    }
}
