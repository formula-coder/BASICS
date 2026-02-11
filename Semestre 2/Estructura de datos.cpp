//Crear una estructura de datos llamada lista dinamica la cual se compone de una arreglo el cual se ira escalando a medida que se agreguen o se eliminen elementos de esta. Hacer gestion correcta de la memoria dinamica de l sistema.

#include <iostream>
#include <stdlib.h>
#include "Estructura de datos libreria.h"
using namespace std;

void agregarnumero(int *&lista,int &total);
void mostrarlista(int *lista, int total);
void eliminarnumero(int *&lista, int &total);

int main(){
    int* lista = nullptr; // Puntero a la lista dinámica
    int total = 0; // Cantidad de elementos en la lista

    while(true){
        int opcion;
        cout<<"Menu de opciones"<<endl;
        cout<<"1. Agregar elemento a la lista"<<endl;
        cout<<"2. Eliminar elemento de la lista"<<endl;
        cout<<"3. Mostrar lista"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada invalida Intente de nuevo. Debe ingresar una opcion valida."<<endl;
            continue;
            }
    switch (opcion){
        case 1:{
            cout<<"Se escogio agregar elemento a la lista"<<endl;
            agregarnumero(lista, total);
            break;
        }
        case 2:{
            cout<<"Se escogio eliminar elemento de la lista"<<endl;
            eliminarnumero(lista, total);
            break;
        }
        case 3:{
            cout<<"Se escogio mostrar lista"<<endl;
            mostrarlista(lista, total);
            break;
        }
        case 4:{
            cout<<"Se escogio salir"<<endl;
            exit(0);
        }
        default:{
            cout<<"Opcion no valida, intente de nuevo"<<endl;
            break;
        }
    }
}  
return 0;
}
