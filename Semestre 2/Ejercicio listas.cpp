//Modificar las impelemtaciones de la lista dinamaica y lista enlazada para que sean utilizadas para crear listas con tipo de dato dinamico

#include <iostream>
#include <string>
#include <limits>
#include "LibreriaListas.h"

using namespace std;

int main() {

    ListaDinamica<string> listaArr;
    ListaEnlazada<string> listaEnl;

    int opcion = 0;
    string entrada;

    do {
        cout << "\n================================" << endl;
        cout << "   GESTION DE LISTAS GENERICAS  " << endl;
        cout << "================================" << endl;
        cout << "1. Agregar a Lista Dinamica (Arreglo)" << endl;
        cout << "2. Agregar a Lista Enlazada (Nodos)" << endl;
        cout << "3. Mostrar ambas listas" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione: ";
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Debe ingresar un numero del menu." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1:
                cout << "Texto para Lista Dinamica: ";
                getline(cin, entrada);
                listaArr.agregar(entrada);
                break;
            case 2:
                cout << "Texto para Lista Enlazada: ";
                getline(cin, entrada);
                listaEnl.insertar(entrada);
                break;
            case 3:
                cout << "\n--- CONTENIDO ---" << endl;
                cout << "Dinamica: ";
                listaArr.mostrar();
                cout << "Enlazada: ";
                listaEnl.imprimir();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 4);

    return 0;
}