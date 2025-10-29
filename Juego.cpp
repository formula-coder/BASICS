#include <iostream>
#include <string>
#include <vector>

using namespace std;

void mostrartablero(char tablero[6][7]);
bool colocarFicha(char tablero[6][7], int columna, char ficha);
void jugarPartida(char tablero[6][7], string nombre1, string nombre2);
bool verificarGanador(char tablero[6][7], char ficha);

struct jugador{
    string nombre;
    int jugados=0;
    int ganados=0;
    int empates=0;
    int perdidos=0;
    int puntos=0;
};

int main() {
    int opcion = 0;
    string nombre1;
    string nombre2;
    int opcion1 = 0;
    char ficha;
    int columna;
    bool turnoJugador1 = true;
    int players = 0;
    char tablero[6][7];
    vector<jugador>jugadores;
    cout << "Bienvenido al juego de cuatro en linea" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Juego de cuatro en linea" << endl;
    cout << "-----------------------" << endl;
        cout << "Menu de opciones" << endl;
        cout << "1. Jugar partida" << endl;
        cout << "2. Jugar torneo" << endl;
        cout << "3. Ver estadisticas" << endl;
        cout << "4. Cargar/guardar" << endl;
        cout << "5. Salir" << endl;
        cout << "---------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << " Se escogio jugar partida" << endl;
                cout << "Ingrese el nombre del jugador 1: ";
                cin >> nombre1;
                cout << "El nombre del jugador 1 es: " << nombre1 << endl;
                cout << "Ingrese el nombre del jugador 2: ";
                cin >> nombre2;
                cout << "El nombre del jugador 2 es: " << nombre2 << endl;

                // reiniciar tablero antes de la partida
                for (int i = 0; i < 6; ++i)
                    for (int j = 0; j < 7; ++j)
                        tablero[i][j] = ' ';
                jugarPartida(tablero, nombre1, nombre2);
                break;

            case 2: {
                cout << "Se escogio jugar torneo" << endl;
                cout << "Cuantos jugadores van a participar? ";
                cin >> players;
                jugadores.resize(players);
                //hasta dies jugadores :)
                for (int i = 0; i < players; i++) {
                    cout << "Ingrese el nombre del jugador " << i+1 << ": ";
                    cin >> jugadores[i].nombre;
                    cout << "El nombre del jugador " << i+1 << " es: " << jugadores[i].nombre << endl;
                }
                cout << "Ingrese el nombre del torneo: ";
                string nombreTorneo;
                cin >> nombreTorneo;
                cout << "El nombre del torneo es: " << nombreTorneo << endl;
                cout<<"jugadores participantes: "<<players<<endl;
                for(int w=0;w<players;w++){
                    cout<<"Jugador "<<w+1<<": "<<jugadores[w].nombre<<endl;
                }
                jugarPartida(tablero,jugadores[0].nombre,jugadores[1].nombre); 
                break;
            }

            case 3:
                cout << "Ver estadisticas" << endl;
                cout << "Que estadisticas quiere ver?" << endl;
                cout << "Estadisticas del Torneo(1)" << endl;
                cout << "Estadisticas  de la Partida(2)" << endl;
                cin >> opcion1;

                switch (opcion1) {
                    case 1:
                        cout << "===== Estadisticas del Torneo =====" << endl;
                        cout << "Jugador     Jugados  Ganados  Empates  Perdidos  Puntos" << endl;
                        cout << "----------------------------------------------" << endl;
                        for(int s=0;s<players;s++){
                            cout << jugadores[s].nombre<< "         " << jugadores[s].jugados<< "        " << jugadores[s].ganados << "       " << jugadores[s].empates<< "       " << jugadores[s].perdidos<< "       " << jugadores[s].puntos<< endl;
                        }
                        break;
                }
                break;

            case 4:
                cout << "Cargar/guardar" << endl;
                break;

            case 5:
                cout << "Salio" << endl;
                break;

            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    return 0;
    }
    
void mostrartablero(char tablero[6][7]) {
    cout << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << "| " << tablero[i][j] << " ";  
        }
        cout << "|"<<endl;
    }
    cout << "-----------------------------" << endl;
    cout << "  1   2   3   4   5   6   7 " << endl << endl;
}

bool colocarFicha(char tablero[6][7], int columna, char ficha) {
    for (int i = 5; i >= 0; i--) { // desde abajo hacia arriba
        if (tablero[i][columna] == ' '){
            tablero[i][columna] = ficha;
            return true;
        }
    }
    return false; // columna llena
}

void jugarPartida(char tablero[6][7], string nombre1, string nombre2) {

    char ficha;
    int columna;
    bool turnoJugador1 = true;
    while (true) {
        mostrartablero(tablero);

        if (turnoJugador1) {
            cout << nombre1 << " (X), elige una columna (1-7) o 0 para salir: ";
            ficha = 'X';
        } else {
            cout << nombre2 << " (O), elige una columna (1-7) o 0 para salir: ";
            ficha = 'O';
        }

        cin >> columna;
        if (!cin) { // simple input guard
            cout << "Entrada invalida. Intente de nuevo." << endl;
            continue;
        }

        if (columna == 0) {
            cout << "Saliendo de la partida." << endl;
            break;
        }

        columna--; // ajustar al índice (0–6)

        if (columna < 0 || columna >= 7) {
            cout << "Columna invalida. Intente de nuevo." << endl;
            continue;
        }

        if (!colocarFicha(tablero, columna, ficha)) {
            cout << "Columna llena. Intente con otra." << endl;
            continue;
        }
        // Cambiar turno
        turnoJugador1 = !turnoJugador1;
    } 
}

bool verificarGanador(char tablero[6][7], char ficha){
    // Verificación del ganador :)
    //Verificación horizontal
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            if(tablero[i][j]==ficha and tablero[i][j+1] and tablero[i][j+2] and tablero[i][j+3]==ficha){
                cout<<"Ganador horizontal"<<endl; 
                return true;

                
            }
        }
    }
//Verificación vertical
for(int j=0;j<7;j++){
    for(int i=0;i<3;i++){
        if(tablero[i][j]==ficha and tablero[i+1][j] and tablero[i+2][j] and tablero[i+3][j]==ficha){
            cout<<"Ganador vertical"<<endl;
            return true;
           
        }
    }
}
//Verificación diagonal derecha
for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
        if(tablero[i][j]==ficha and tablero[i+1][j+1] and tablero[i+2][j+2] and tablero[i+3][j+3]==ficha){
             cout<<"Ganador diagonal derecha"<<endl;
            return true;
           
        }
    }
}
//Verificación diagonal izquierda
for(int i=0;i<3;i++){
    for(int j=3;j<7;j++){
        if(tablero[i][j]==ficha and tablero[i+1][j-1] and tablero[i+2][j-2] and tablero[i+3][j-3]==ficha){
            cout<<"Ganador diagonal izquierda"<<endl;
            return true;
           
        }
    }
}
}