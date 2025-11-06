#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct jugador{
    string nombre;
    int jugados=0;
    int ganados=0;
    int empates=0;
    int perdidos=0;
    int puntos=0;
};
struct partida{
    string player;
    int jugados1=0;
    int ganados1=0;
    int empates1=0;
    int perdidos1=0;
    int puntos1=0;
};
void mostrartablero(char tablero[6][7]);
bool colocarFicha(char tablero[6][7], int columna, char ficha);
bool jugarPartida(char tablero[6][7], string nombre1, string nombre2,vector<partida> &partidas);
bool verificarGanador(char tablero[6][7], char ficha);
bool jugartorneo(char tablero[6][7], vector<jugador>&jugadores, vector<partida>&partidas,string nombreTorneo);
bool verificarTorneo(char tablero[6][7],vector<jugador>&jugadores, vector<partida>&partidas,string nombreTorneo);

int main() {
    int opcion = 0;
    int opcion1 = 0;
    char ficha;
    int columna;
    bool turnoJugador1 = true;
    int players = 0;
    char tablero[6][7];
    bool opcion2;
    vector<jugador>jugadores;//torneo
    vector<partida> partidas(2);//partida
    do{
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
            case 1: {
                cout << " Se escogio jugar partida" << endl;
                for(int p=0;p<2;p++){
                    cout <<"Ingrese el nombre del jugador "<<p+1<<": ";
                    cin >> partidas[p].player;
                    cout <<"El nombre del jugador "<<p+1<<" es: "<<partidas[p].player<<endl;
                }
                // reiniciar tablero antes de la partida
                for (int i = 0; i < 6; ++i)
                    for (int j = 0; j < 7; ++j)
                        tablero[i][j] = ' ';

               opcion2=jugarPartida(tablero,partidas[0].player,partidas[1].player,partidas);
                if(opcion2==false){
                cout<<"Cerrando el juego, muchas gracias por jugar :)"<<endl; 
                return 0;
                }
                break;
            }
            case 2: {
                cout << "Se escogio jugar torneo" << endl;
                cout << "Cuantos jugadores van a participar? ";
                cin >> players;
            if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada inválida Intente de nuevo. Debe ingresar una cantidad de jugadores válida."<<endl;
            continue;
        }
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
                jugartorneo(tablero,jugadores,partidas,nombreTorneo); 
                break;
            }

            case 3: {
                cout << "Ver estadisticas" << endl;
                cout << "Que estadisticas quiere ver?" << endl;
                cout << "Estadisticas del Torneo(1)" << endl;
                cout << "Estadisticas de la Partida(2)" << endl;
                cin >> opcion1;

                switch (opcion1) {
                    case 1: {
                        cout << "===== Estadisticas del Torneo =====" << endl;
                        cout << "Jugador     Jugados  Ganados  Empates  Perdidos  Puntos" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        for(int s = 0; s < players; s++) {
                            cout << jugadores[s].nombre << "         " 
                                 << jugadores[s].jugados << "        " 
                                 << jugadores[s].ganados << "       " 
                                 << jugadores[s].empates << "       " 
                                 << jugadores[s].perdidos << "       " 
                                 << jugadores[s].puntos << endl;
                        }
                        break;
                    }
                    case 2: {
                        cout << "===== Estadisticas de la partida =====" << endl;
                        cout << "Jugador    Jugados  Ganados  Empates  Perdidos  Puntos" << endl; 
                        cout << "-------------------------------------------------------" << endl;
                        for(int t = 0; t < 2; t++) {
                            cout << partidas[t].player << "         " 
                                 << partidas[t].jugados1 << "        " 
                                 << partidas[t].ganados1 << "       " 
                                 << partidas[t].empates1 << "       " 
                                 << partidas[t].perdidos1 << "       " 
                                 << partidas[t].puntos1 << endl;
                        }
                        break;
                    }
                }
                break;
            }
            case 4: {
                cout << "Cargar/guardar" << endl;
                break;
            }

            case 5: {
                cout << "Salio" << endl;
                break;
            }

            default: {
                cout << "Opcion no valida" << endl;
                break;
            }
        
        }
} while(opcion != 5);
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

bool jugarPartida(char tablero[6][7], string nombre1, string nombre2,vector<partida> &partidas) {
int pregunta;
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
        if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada inválida Intente de nuevo. Debe ingresar un nuevo numero"<<endl;
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
        if (verificarGanador(tablero, ficha)) {
            mostrartablero(tablero);
            bool lleno=true;
            for(int i=0; i<6; i++){
                for(int j=0; j<7; j++){
                    if(tablero[i][j]==' ') {
                        lleno=false;
                        break;
                    }
                }
            }

         partidas[0].jugados1++;
         partidas[1].jugados1++;
         if(lleno){
            cout<<"El tablero se lleno. Empate."<<endl;
            partidas[0].empates1++;
            partidas[1].empates1++;
         }

         if(turnoJugador1){
            cout<<"Felicidades "<<partidas[0].player<<" has ganado!"<<endl;
            cout<<"Lo siento "<<partidas[1].player<<" has perdido."<<endl<<endl;
            partidas[0].ganados1++;
            partidas[1].perdidos1++;
         }else{
            cout<<"Felicidades "<<partidas[1].player<<" has ganado!"<<endl;
            cout<<"Lo siento "<<partidas[0].player<<" has perdido."<<endl<<endl;
            partidas[1].ganados1++;
            partidas[0].perdidos1++;
         }
        // calcular puntos
        partidas[0].puntos1 =partidas[0].ganados1 * 3 + partidas[0].empates1;
        partidas[1].puntos1 = partidas[1].ganados1 * 3 + partidas[1].empates1;
            cout << "===== Estadisticas de la partida====="<< endl;
            cout << "Jugador     Jugados  Ganados  Empates  Perdidos  Puntos"<<endl;
            cout << "-------------------------------------------------------"<<endl;
            for (int i = 0; i < 2; i++) {
                cout << partidas[i].player << "         "
                     << partidas[i].jugados1 << "        "
                     << partidas[i].ganados1 << "        "
                     << partidas[i].empates1 << "        "
                     << partidas[i].perdidos1 << "        "
                     << partidas[i].puntos1 << endl;
            }
        break;
         }
        // Cambiar turno
        turnoJugador1 = !turnoJugador1;
    } 
do{
    cout <<"\nDesea ir al menu principal? 1.Si 2.No: "<<endl;
    cin >> pregunta;
    if(pregunta==1){
        cout<<"Se escogio ir al menu principal"<<endl<<endl;
        return true;
    }else if(pregunta==2){
        cout<<"Se escogio no ir al menu principal cerrando programa"<<endl;
        return false;
    }else{
        cout<<"Opcion no valida,intente de nuevo"<<endl;
}
}while(pregunta!=1 and pregunta !=2);

}

bool verificarGanador(char tablero[6][7], char ficha){
    // Verificación del ganador :)
    //Verificación horizontal
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            if(tablero[i][j]== ficha and
                tablero[i][j+1]== ficha and
                tablero[i][j+2]== ficha and
                tablero[i][j+3]==ficha){
                return true;
            }
        }
    }
//Verificación vertical
for(int j=0;j<7;j++){
    for(int i=0;i<3;i++){
        if(tablero[i][j]==ficha and
             tablero[i+1][j]==ficha and
             tablero[i+2][j]==ficha and
              tablero[i+3][j]==ficha){
            return true;
           
        }
    }
}
//Verificación diagonal derecha
for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
        if(tablero[i][j]==ficha and
             tablero[i+1][j+1]==ficha and
              tablero[i+2][j+2]==ficha and
               tablero[i+3][j+3]==ficha){
            return true;
        }
    }
}
//Verificación diagonal izquierda
for(int i=0;i<3;i++){
    for(int j=3;j<7;j++){
        if(tablero[i][j]==ficha and
             tablero[i+1][j-1]==ficha and
              tablero[i+2][j-2]==ficha and
               tablero[i+3][j-3]==ficha){
            return true;
        }
    }
}
return false;
}

bool jugartorneo(char tablero[6][7], vector<jugador>&jugadores, vector<partida>&partidas, string nombreTorneo) {
    string nametournament = nombreTorneo;
    int players = jugadores.size();
    cout << "El torneo ha empezado!! "<<nametournament<< endl;
    cout << "Participan " << players << " jugadores" << endl;
    
    for(int i = 0; i < players; i++) {
        for(int j = i + 1; j < players; j++) {
            cout <<"Enfrentamiento entre: "<< jugadores[i].nombre << " Vs " << jugadores[j].nombre << endl;
            // reiniciar tablero antes de la partida
            for (int m = 0; m < 6; ++m)
                for (int n = 0; n < 7; ++n)
                    tablero[m][n] = ' ';
            bool continuar = verificarTorneo(tablero, jugadores, partidas, nametournament);
            if(!continuar) {
                cout << "El torneo ha sido interrumpido por el usuario" << endl;
                return false;
            }
            
            cout << "Estadisticas del torneo: "<<nametournament << endl;
            cout << "Jugador     Jugados  Ganados  Empates  Perdidos  Puntos" << endl;
            cout << "-------------------------------------------------------" << endl;
            for(int k = 0; k < players; k++) {  // Cambiado para mostrar todos los jugadores
                cout << jugadores[k].nombre << "         "
                     << jugadores[k].jugados << "        "
                     << jugadores[k].ganados << "        "
                     << jugadores[k].empates << "        "
                     << jugadores[k].perdidos << "        "
                     << jugadores[k].puntos << endl;
            }  
         }
        }
        int opcion;
    do {
        cout << "\n¿Desea continuar? (1. Sí / 2. No): ";
        cin >> opcion;
            if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada inválida Intente de nuevo. Debe ingresar una opción válida."<<endl;
            continue;
        }
        if (opcion == 1) {
            cout << "Volviendo al menú principal...\n";
            return true;
        } else if (opcion == 2) {
            cout << "Finalizando el programa. ¡Gracias por jugar!\n";
            return false;
        } else {
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 1 && opcion != 2);
    return true;
}

bool verificarTorneo(char tablero[6][7],vector<jugador>&jugadores, vector<partida>&partidas,string nombreTorneo){
    int pregunta;
    char ficha;
    int columna;
    bool turnoJugador1 = true;
    while (true) {
        mostrartablero(tablero);

        if (turnoJugador1) {
            cout << jugadores[0].nombre << " (X), elige una columna (1-7) o 0 para salir: ";
            ficha = 'X';
        } else {
            cout << jugadores[1].nombre << " (O), elige una columna (1-7) o 0 para salir: ";
            ficha = 'O';
        }

        cin >> columna;
        if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada inválida Intente de nuevo. Debe ingresar un nuevo numero"<<endl;
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
        if (verificarGanador(tablero, ficha)) {
            mostrartablero(tablero);
            bool lleno=true;
            for(int i=0; i<6; i++){
                for(int j=0; j<7; j++){
                    if(tablero[i][j]==' ') {
                        lleno=false;
                        break;
                    }
                }
            }

         jugadores[0].jugados++;
         jugadores[1].jugados++;
         if(lleno){
            cout<<"El tablero se lleno. Empate."<<endl;
            jugadores[0].empates++;
            jugadores[1].empates++;
         }

         if(turnoJugador1){
            cout<<"Felicidades "<<jugadores[0].nombre<<" has ganado!"<<endl;
            cout<<"Lo siento "<<jugadores[1].nombre<<" has perdido."<<endl<<endl;
            jugadores[0].ganados++;
            jugadores[1].perdidos++;
         }else{
            cout<<"Felicidades "<<jugadores[1].nombre<<" has ganado!"<<endl;
            cout<<"Lo siento "<<jugadores[0].nombre<<" has perdido."<<endl<<endl;
            jugadores[1].ganados++;
            jugadores[0].perdidos++;
         }
        // calcular puntos
        jugadores[0].puntos = jugadores[0].ganados * 3 + jugadores[0].empates;
        jugadores[1].puntos = jugadores[1].ganados * 3 + jugadores[1].empates;
        break;
         }
        // Cambiar turno
        turnoJugador1 = !turnoJugador1;
    } 
return true;
}
/*  terminar archivo guardado*/