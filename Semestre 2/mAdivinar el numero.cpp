#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
    int numerosospechoso = rand() % 100 + 1; // Numero aleatorio entre 1 y 100

    int intento;
    cout << "¡Bienvenido al juego de adivinar el numero!" << endl;
    cout << "Intenta adivinar el numero entre 1 y 100: ";
    do{
        cin>>intento;
        if (intento < numerosospechoso){
            cout<<"El numero es menor que el numero sospechoso. Intenta de nuevo: ";
        }
        if(intento > numerosospechoso){
            cout<<"El numero es mayor que el numero sospechoso. Intenta de nuevo: ";
        }
        if(intento == numerosospechoso){
            cout<<"¡Felicidades! Has adivinado el numero sospechoso: "<<numerosospechoso<<endl;
        system("pause");
        }
    }   while(intento != numerosospechoso);    
    return 0;
}