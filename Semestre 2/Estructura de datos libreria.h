#include <iostream>
using namespace std;
void agregarnumero(int *&lista, int &total){
    int n;
    cout << "Cuantos numeros desea agregar?: ";
    cin >> n;

    if(cin.fail() || n <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Entrada invalida\n";
        return;
    }

    int* nuevaLista = new int[total + n];

    for(int i = 0; i < total; i++){
        nuevaLista[i] = lista[i];
    }

    for(int i = 0; i < n; i++){
        cout << "Ingrese numero: ";
        cin >> nuevaLista[total + i];
    }

    delete[] lista;
    lista = nuevaLista;
    total += n;

    cout << "Numeros agregados correctamente\n";
}
void mostrarlista(int *lista, int total){
    if(total == 0){
        cout << "La lista esta vacia\n";
        return;
    }

    cout << "Elementos de la lista:\n";
    for(int i = 0; i < total; i++){
        cout << lista[i] << endl;
    }
}
void eliminarnumero(int *&lista, int &total){
    if(total == 0){
        cout << "La lista esta vacia\n";
        return;
    }

    int numero;
    cout << "Ingrese el numero a eliminar: ";
    cin >> numero;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Entrada invalida\n";
        return;
    }

    int pos = -1;
    for(int i = 0; i < total; i++){
        if(lista[i] == numero){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        cout << "Numero no encontrado\n";
        return;
    }

    int* nuevaLista = nullptr;

    if(total - 1 > 0){
        nuevaLista = new int[total - 1];
        for(int i = 0, j = 0; i < total; i++){
            if(i != pos){
                nuevaLista[j++] = lista[i];
            }
        }
    }

    delete[] lista;
    lista = nuevaLista;
    total--;

    cout << "Numero eliminado correctamente\n";
}
