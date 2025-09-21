#include <iostream>
#include<stdio.h>

using namespace std;
int tablero(int columnas, int filas);

int main(){
int opcion=0;
std::string nombre1; 
std::string nombre2;
int juego;
int columnas;
int filas;
int opcion1=0;
int opcion2=0;
do
{
    cout<<"Juego de cuatro en linea"<<endl;
    cout<<"-----------------------"<<endl;
    cout<<"menu de opciones"<<endl;
    cout<<"1. Jugar partida"<<endl;
    cout<<"2. Jugar torneo"<<endl;
    cout<<"3. Ver estadisticas"<<endl;
    cout<<"4. Cargar/guardar"<<endl;
    cout<<"5. Salir"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"Ingrese una opcion: ";
    cin>>opcion;
 switch(opcion){
        case 1:
            cout<<"Jugar partida"<<endl;
            cout<<"Ingrese el nombre del jugador 1: ";
            cin>>nombre1;
            cout<<"El nombre del jugador 1 es: "<<nombre1<<endl;
            cout<<"Ingrese el nombre del jugador 2: ";
            cin>>nombre2;
            cout<<"El nombre del jugador 2 es: "<<nombre2<<endl;
            juego = tablero(columnas, filas);
            cout<<juego;
            cout<<"salir(1) o continuar(2)?"<<endl;
                cin>>opcion2;
            break;
        case 2:
            cout<<"Jugar torneo"<<endl;
            break;
        case 3:
            cout<<"Ver estadisticas"<<endl;
            cout<<" Que estadisticas quiere ver?"<<endl;
            cout<<"Estadisticas torneo (1)"<<endl;
            cout<<"Estadisticas partida(2)"<<endl;
            cin>>opcion1;
            switch(opcion1){
                case 1:
                cout<<"=====Estadisticas del Torneo====="<<endl;
                cout<<"Jugador     Jugados  Ganados  Empates  Perdidos  Puntos "<<endl;
                cout<<"----------------------------------------------"<<endl;
                cout<<nombre1<<"\t0\t0\t0\t0\t0"<<endl;
                cout<<nombre2<<"\t0\t0\t0\t0\t0"<<endl;
                cout<<"salir(1) o continuar(2)?"<<endl;
                cin>>opcion2;
                if(opcion2 == 2){
                cout<<"se acabo el programa";	}
               break; 
			 }
			 
        case 4:
            cout<<"Cargar/guardar"<<endl;
            break;
        case 5:
            cout<<"salio"<<endl;
            break;
        default:
            cout<<"Opcion no valida"<<endl;
  
}
}  
	while(opcion2 == 2);
        if(opcion2 == 2){
        cout<<"se acabo el programa";	}
}
 int tablero(int columnas, int filas){
    for(int i=0; i<8; i++){
        for(int j=0; j<9; j++){
            cout<<"|_|";
        }
        cout<<endl;
    }
 }
