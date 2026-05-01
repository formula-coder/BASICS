#include<iostream>
#include<string>
#include<conio.h>
using namespace std;

bool validarNumero(string numeroTarjeta);
int main(){
    int opcion;
    do{
        string numeroTarjeta;
        cout<<"--------------------"<<endl;
        cout<<"Algoritmo de luhn"<<endl;
        cout<<"--------------------"<<endl;
        cout << "Ingrese el numero de tarjeta: ";
        cin >> numeroTarjeta;
        if(validarNumero(numeroTarjeta)){
            cout<<"el numero de la tarjeta es valido: "<<numeroTarjeta<<endl;
        }else{
            cout<<"el numero de la tarjeta no es valido: "<<numeroTarjeta<<endl;
        }
        cout<<"Desea validar otro numero de tarjeta? (1: si, 0: no): ";
        cin >> opcion;
        if(opcion == 2){
            cout<<"Gracias por usar el programa"<<endl;
            cout<<"--------------------"<<endl;
            cout<<"cerrando el programa..."<<endl;
            break;
        }
        getch();
    } while(opcion == 1);
    return 0;
}

bool validarNumero(string numeroTarjeta){
    int suma = 0;
    int longitud = numeroTarjeta.length();
    for(int i = longitud - 1; i >= 0; i--){
        int digito = numeroTarjeta[i]-'0';
        if((longitud - i) % 2 == 1){
            digito *= 2;
            if(digito > 9){
                digito -= 9;
            }
        }
        suma += digito;
    }
    return suma % 10 == 0;
}