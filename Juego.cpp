#include <iostream>
#include<stdio.h>

using namespace std;

int mostrartablero(char tablero[6][7]);
bool colocarFicha(char tablero[6][7], int columna, char ficha);
int main(){
int opcion=0;
string nombre1; 
string nombre2;
int opcion1=0;
int opcion2=0;
char tablero[6][7];

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
            mostrartablero(tablero);
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
 int mostrartablero(char tablero[6][7]){
    for(int i=0; i<8; i++){
        for(int j=0; j<9; j++){
            cout<<"|_|";
        }
        cout<<endl;
    }
        cout << "---------------" << endl;
    cout << " 1 2 3 4 5 6 7 " << endl << endl;
 }
bool colocarFicha(char tablero[6][7], int columna, char ficha){
    bool turn=true;
    for (int i = 5; i >= 0; i--) { // desde abajo hacia arriba
        if (tablero[i][columna] == ' ') {
            tablero[i][columna] = ficha;
            return true;
        }
    }
    return false; // columna llena
while (true) {
        mostrarTablero(tablero);
        if (turnoJugador1) {
            cout << nombre1 << " (X), elige una columna (1-7): ";
            ficha = 'X';
        } else {
            cout << nombre2 << " (O), elige una columna (1-7): ";
            ficha = 'O';
        }

        cin >> columna;
        columna--; // ajustar al índice (0–6)

        if (columna < 0 || columna >= 7) {
            cout << "Columna inválida. Intente de nuevo." << endl;
            continue;
        }

        if (!colocarFicha(tablero, columna, ficha)) {
            cout << "Columna llena. Intente con otra." << endl;
            continue;
        }

        // Cambiar de turno
        turnoJugador1 = !turnoJugador1;
    }

    return 0;

}
