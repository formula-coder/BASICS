#include <iostream>   // Entrada y salida (cout, cin)
#include <string>   // Manejo de strings
#include <vector>   // Manejo de vectores dinamicos
#include <fstream>   // Manejo de archivos
#include <stdlib.h>   // Funciones generales de utilidad exit()
#include<iomanip>   // Formato de tablas (setw)
#include<limits>  // numeric_limits (limpiar buffer)

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

void mostrartablero(char tablero[8][9]);
bool colocarFicha(char tablero[8][9], int columna, char ficha);
bool jugarPartida(char tablero[8][9], string nombre1, string nombre2,vector<partida> &partidas);
bool verificarGanador(char tablero[8][9], char ficha);
bool jugartorneo(char tablero[8][9], vector<jugador>&jugadores, vector<partida>&partidas,string nombreTorneo);
bool verificarTorneo(char tablero[8][9],vector<jugador>&jugadores, vector<partida>&partidas,string nombreTorneo, int i, int j);
void guardarPartida(const vector<partida>& partidas, const string& nombreArchivo);
void cargarPartida(const string& nombreArchivo, vector<partida>& partidas);
void guardarTorneo(const vector<jugador>& jugadores, const string & nombreArchivo);
void cargarTorneo(const vector<jugador>& jugadores, const string & nombreArchivo);
void guardarPartidaAuto(const vector<partida>& partidas);
void guardarTorneoAuto(const vector<jugador>& jugadores);

int main() {
    int opcion = 0;
    int opcion1 = 0;
    int opcion2 = 0;
    int opcion3 = 0;
    bool opcion4=true;
    char ficha;
    int columna;
    bool turnoJugador1 = true;
    int players = 0;
    char tablero[8][9]; //tablero de 8 filas y 9 columnas
    vector<jugador>jugadores;//torneo
    vector<partida> partidas(2);//partida
    do{
    cout << "Bienvenido al juego de cuatro en linea" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Juego de cuatro en linea" << endl;
    cout << "------------------------" << endl;
        cout << "Menu de opciones" << endl;
        cout << "1. Jugar partida" << endl;
        cout << "2. Jugar torneo" << endl;
        cout << "3. Ver estadisticas" << endl;
        cout << "4. Cargar/guardar" << endl;
        cout << "5. Salir" << endl;
        cout << "---------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
            if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada invalida Intente de nuevo. Debe ingresar una opcion valida."<<endl;
            continue;
            }
        switch (opcion) {
            case 1: {
                cout << "Se escogio jugar partida" << endl; 
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                for(int p=0;p<2;p++){
                    cout <<"Ingrese el nombre del jugador "<<p+1<<": ";
                    getline(cin, partidas[p].player);
                    cout <<"El nombre del jugador "<<p+1<<" es: "<<partidas[p].player<<endl;
                }
                // reiniciar tablero antes de la partida
                for (int i = 0; i < 8; ++i)
                    for (int j = 0; j < 9; ++j)
                        tablero[i][j] = ' ';

               opcion2=jugarPartida(tablero,partidas[0].player,partidas[1].player,partidas);
                if(opcion4==false){
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
            cout << "Entrada invalida Intente de nuevo. Debe ingresar una cantidad de jugadores valida."<<endl;
            continue;
        }
                jugadores.resize(players);
                //hasta dies jugadores :)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                for (int i = 0; i < players; i++) {
                    cout << "Ingrese el nombre del jugador " << i+1 << ": ";
                    getline(cin,jugadores[i].nombre);
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
                        cout << "       ===== Estadisticas del Torneo =====" << endl;
                        cout << left << setw(15) << "Jugador"
                             << setw(10) << "Jugados"
                             << setw(10) << "Ganados"
                             << setw(10) << "Empates"
                             << setw(10) << "Perdidos"
                             << setw(10) << " Puntos" << endl;
                        cout << "--------------------------------------------------------------" << endl;
                     for (int s = 0; s < players; s++) {
                        cout << left << setw(16) << jugadores[s].nombre
                             << setw(11) << jugadores[s].jugados
                             << setw(11) << jugadores[s].ganados
                             << setw(11) << jugadores[s].empates
                             << setw(11) << jugadores[s].perdidos
                             << setw(9) << jugadores[s].puntos
                                << endl;
                                }
                        break;
                    }
                    case 2: {
                        cout << "       ===== Estadisticas de la partida =====" << endl;
                           cout << left << setw(15) << "Jugador"
                             << setw(10) << "Jugados"
                             << setw(10) << "Ganados"
                             << setw(10) << "Empates"
                             << setw(10) << "Perdidos"
                             << setw(10) << " Puntos" << endl;
                        cout << "--------------------------------------------------------------" << endl;
                    for(int t = 0; t < 2; t++) {
                            cout << left << setw(16) << partidas[t].player
                                 <<setw(11) << partidas[t].jugados1
                                 <<setw(11) << partidas[t].ganados1
                                 <<setw(11) << partidas[t].empates1
                                 <<setw(11) << partidas[t].perdidos1
                                 <<setw(9) << partidas[t].puntos1
                                    << endl;
                                  }
                        break;
                    }
                }
                break;
            }
            case 4: {
                cout << "Cargar/guardar" << endl;
                cout <<" Desea cargar o guardar la partida o torneo? 1.Partida 2. Torneo: ";
                cin >> opcion2;
                switch(opcion2){
                    case 1: {
                        cout<<"¿Desea cargar o guardar la partida?"<<endl;
                        cout<<"1. Cargar  2. Guardar"<<endl;
                        cin>>opcion3;
                        if(opcion3==1){
                            cout<<"Se va a cargar la partida"<<endl;
                            cargarPartida("partida",partidas);
                        } else if (opcion3==2){
                            cout<<"Se va a guardar la partida"<<endl;
                            guardarPartida(partidas,"partida");
                        } else {
                            cout << "Opcion no valida" << endl;
                        }
                        break;
                    }
                    case 2: {
                        cout<<"¿Desea cargar o guardar el torneo?"<<endl;
                        cout<<"1. Cargar  2.Guardar"<<endl;
                        cin>>opcion3;
                        if(opcion3==1){
                            cout<<"Se va a cargar el torneo"<<endl;
                            cargarTorneo(jugadores, "torneo");
                            
                        } else if (opcion3==2){
                            cout<<"Se va a guardar el torneo"<<endl;
                            guardarTorneo(jugadores, "torneo");
                        } else {
                            cout << "Opcion no valida" << endl;
                        }
                        break;
                    }
                    default: {
                        cout << "Opcion no valida" << endl;
                        break;
                    }
                }
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

void mostrartablero(char tablero[8][9]) {
    cout << endl;
    cout << "-------------------------------------" << endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            cout << "| " << tablero[i][j] << " ";  
        }
        cout << "|"<<endl;
    }
    cout << "-------------------------------------" << endl;
    cout << "  1   2   3   4   5   6   7   8   9 " << endl << endl;
}

bool colocarFicha(char tablero[8][9], int columna, char ficha) {
    for (int i = 7; i >= 0; i--) { // desde abajo hacia arriba
        if (tablero[i][columna] == ' '){
            tablero[i][columna] = ficha;
            return true;
        }
    }
    return false; // columna llena
}

bool jugarPartida(char tablero[8][9], string nombre1, string nombre2,vector<partida> &partidas) {
int pregunta;
    char ficha;
    int columna;
    bool turnoJugador1 = true;
    while (true) {
        mostrartablero(tablero);
        if (turnoJugador1) {
            cout << nombre1 << " (X), elige una columna (1-9) o 0 para salir: ";
            ficha = 'X';
        } else {
            cout << nombre2 << " (O), elige una columna (1-9) o 0 para salir: ";
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
        columna--; // ajustar al índice (0–8)
        if (columna < 0 || columna >= 9) {
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
            for(int i=0; i<8; i++){
                for(int j=0; j<9; j++){
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
                           cout << left << setw(15) << "Jugador"
                             << setw(10) << "Jugados"
                             << setw(10) << "Ganados"
                             << setw(10) << "Empates"
                             << setw(10) << "Perdidos"
                             << setw(10) << " Puntos" << endl;
            cout << "--------------------------------------------------------------" << endl;
            for (int i = 0; i < 2; i++) {
            cout << left << setw(16) << partidas[i].player
                 <<setw(11) << partidas[i].jugados1
                 <<setw(11) << partidas[i].ganados1
                 <<setw(11) << partidas[i].empates1
                 <<setw(11) << partidas[i].perdidos1
                 <<setw(9) << partidas[i].puntos1
                 << endl;
            }
        break;
         }
        // Cambiar turno
        turnoJugador1 = !turnoJugador1;
    }
    int pregunta2;
    cout<<"desea guardar la partida automaticamente? 1.Si 2.No: "<<endl;
    cin>>pregunta2;
    if(pregunta2 == 1) {
        guardarPartidaAuto(partidas);
    }
    else{
        cout<<"La partida no va a ser guardado automatico"<<endl;
    }
do{
    cout <<"\nDesea ir al menu principal? 1.Si 2.No: "<<endl;
    cin >> pregunta;
    if(pregunta==1){
        cout<<"Se escogio ir al menu principal"<<endl<<endl;
        return true;
    }else if(pregunta==2){
        cout<<"Se escogio no ir al menu principal cerrando programa"<<endl;
        exit(0);
    }else{
        cout<<"Opcion no valida,intente de nuevo"<<endl;
}
}while(pregunta!=1 and pregunta !=2);
return true;
}

bool verificarGanador(char tablero[8][9], char ficha){
    // Verificación del ganador :)
    //Verificación horizontal
    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            if(tablero[i][j]== ficha and
                tablero[i][j+1]== ficha and
                tablero[i][j+2]== ficha and
                tablero[i][j+3]==ficha){
                return true;
            }
        }
    }
//Verificación vertical
for(int j=0;j<9;j++){
    for(int i=0;i<5;i++){
        if(tablero[i][j]==ficha and
             tablero[i+1][j]==ficha and
             tablero[i+2][j]==ficha and
              tablero[i+3][j]==ficha){
            return true;
           
        }
    }
}
//Verificación diagonal derecha
for(int i=0;i<5;i++){
    for(int j=0;j<6;j++){
        if(tablero[i][j]==ficha and
             tablero[i+1][j+1]==ficha and
              tablero[i+2][j+2]==ficha and
               tablero[i+3][j+3]==ficha){
            return true;
        }
    }
}
//Verificación diagonal izquierda
for(int i=0;i<5;i++){
    for(int j=3;j<9;j++){
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

bool jugartorneo(char tablero[8][9], vector<jugador>&jugadores, vector<partida>&partidas, string nombreTorneo) {
    string nametournament = nombreTorneo;
    int i=0;
    int j=0;
    int players = jugadores.size();
    cout << "El torneo ha empezado!! "<<nametournament<< endl;
    cout << "Participan " << players << " jugadores" << endl;
    for(int i = 0; i < players; i++) {
        for(int j = i + 1; j < players; j++) {
            cout <<"Enfrentamiento entre: "<< jugadores[i].nombre << " Vs " << jugadores[j].nombre << endl;
            // reiniciar tablero antes de la partida
            for (int m = 0; m < 8; ++m)
                for (int n = 0; n < 9; ++n)
                    tablero[m][n] = ' ';
            bool continuar = verificarTorneo(tablero, jugadores, partidas, nametournament, i,j);
            if(!continuar) {
                cout << "El torneo ha sido interrumpido por el usuario" << endl;
                return false;
            }
            cout << "Estadisticas del torneo: "<<nametournament << endl;
                cout << left << setw(15) << "Jugador"
                     << setw(10) << "Jugados"
                     << setw(10) << "Ganados"
                     << setw(10) << "Empates"
                     << setw(10) << "Perdidos"
                     << setw(10) << " Puntos" << endl;
            cout << "--------------------------------------------------------------" << endl;
            for(int k = 0; k < players; k++) {  // Cambiado para mostrar todos los jugadores
                cout << left << setw(16) << jugadores[k].nombre
                     << setw(11) << jugadores[k].jugados
                     << setw(11) << jugadores[k].ganados
                     << setw(11) << jugadores[k].empates
                     << setw(11) << jugadores[k].perdidos
                     << setw(9) << jugadores[k].puntos << endl;
            }  
         }
        }
        jugador ganador=jugadores[0];
        bool empates=false;
        for(int l=1; l<players; l++){
            if(jugadores[l].puntos>ganador.puntos){
                ganador=jugadores[l];
                empates=false;
            } else if (jugadores[l].puntos==ganador.puntos){
                empates=true;
            }
        }
        cout<<"------------------------"<<endl;
        cout<<"El resultado final fue: "<<endl;
        cout<<"------------------------"<<endl;
        if(empates){
            cout<<"Hubo un empate entre estos jugadores!!"<<endl;
            for(int h=0; h<players; h++){   
                if(jugadores[h].puntos==ganador.puntos){
                    cout<<"-"<<jugadores[h].nombre<<"("<<jugadores[h].puntos<<" puntos)"<<endl;
                }
            }
        } else{
            cout<<"El ganador del torneo "<<nametournament<<" es...."<<ganador.nombre<<" con...."<<ganador.puntos<<" FELICIDADES :D!!"<<endl;
        }
        int pregunta;
        cout<<"desea guardar el torneo automaticamente? 1.Si 2.No: "<<endl;
        cin>>pregunta;
        if(pregunta == 1) {
            guardarTorneoAuto(jugadores);
        }
        else{
            cout<<"El torneo no va a ser guardado automatico"<<endl;
        }
        int opcion;
    do {
        cout << "\n¿Desea continuar? (1. Si / 2. No): ";
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
            exit (1);
        } else {
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 1 && opcion != 2);
    return true;
}

bool verificarTorneo(char tablero[8][9],vector<jugador>&jugadores, vector<partida>&partidas,string nombreTorneo,int i,int j){
    int pregunta;
    char ficha;
    int columna;
    bool turnoJugador1 = true;
    while (true) {
        mostrartablero(tablero);
        if (turnoJugador1) {
            cout << jugadores[i].nombre << " (X), elige una columna (1-9) o 0 para salir: ";
            ficha = 'X';
        } else {
            cout << jugadores[j].nombre << " (O), elige una columna (1-9) o 0 para salir: ";
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
        if (columna < 0 || columna >= 9) {
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
            for(int p=0; p<8; p++){
                for(int n=0; n<9; n++){
                    if(tablero[p][n]==' ') {
                        lleno=false;
                        break;
                    }
                }
            }
         jugadores[i].jugados++;
         jugadores[j].jugados++;
         if(lleno){
            cout<<"El tablero se lleno. Empate."<<endl;
            jugadores[i].empates++;
            jugadores[j].empates++;
         }
         if(turnoJugador1){
            cout<<"Felicidades "<<jugadores[i].nombre<<" has ganado!"<<endl;
            cout<<"Lo siento "<<jugadores[j].nombre<<" has perdido."<<endl<<endl;
            jugadores[i].ganados++;
            jugadores[j].perdidos++;
         }else{
            cout<<"Felicidades "<<jugadores[j].nombre<<" has ganado!"<<endl;
            cout<<"Lo siento "<<jugadores[i].nombre<<" has perdido."<<endl<<endl;
            jugadores[j].ganados++;
            jugadores[i].perdidos++;
         }
        // calcular puntos
        jugadores[i].puntos = jugadores[i].ganados * 3 + jugadores[i].empates;
        jugadores[j].puntos = jugadores[j].ganados * 3 + jugadores[j].empates;
        break;
         }
        // Cambiar turno
        turnoJugador1 = !turnoJugador1;
    } 
return true;
}

void guardarPartida(const vector<partida>& partidas, const string& nombreArchivo) {
    string guardado;
    ofstream archivo(guardado, ios::out);
    cout<<"Ingrese el nombre del archivo donde se va a guardar la partida"<<endl;
    cin.ignore();
    getline(cin, guardado);
    archivo.open(guardado.c_str(), ios::out);

       if (guardado.find(".txt") == string::npos) {
        guardado += ".txt";
    }
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo del juego"<<endl;
        exit(1);
    }
    archivo<< "       ===== Estadisticas de la partida =====" << endl;
            archivo<< left << setw(15) << "Jugador"
                 << setw(10) << "Jugados"
                 << setw(10) << "Ganados"
                 << setw(10) << "Empates"
                 << setw(10) << "Perdidos"
                 << setw(10) << " Puntos" << endl;
    archivo<< "--------------------------------------------------------------" << endl;
                     for(int t = 0; t < 2; t++) {
                 archivo<< left << setw(16) << partidas[t].player
                        <<setw(11) << partidas[t].jugados1
                        <<setw(11) << partidas[t].ganados1
                        <<setw(11) << partidas[t].empates1
                        <<setw(11) << partidas[t].perdidos1
                        <<setw(9) << partidas[t].puntos1
                        << endl;
                        }
    archivo.close();
    cout<<"Partida Guardada exitosamente"<<endl;
}

void cargarPartida(const string& nombreArchivo, vector<partida>& partidas) {
     ifstream archivo;
     string guardado;
     string texto;
    cout<<"Ingrese el nombre del archivo desde donde se va a cargar la partida"<<endl;
    cin.ignore();
    getline(cin, guardado);
    if (guardado.find(".txt") == string::npos) {
        guardado += ".txt";
    }
    archivo.open(guardado.c_str(),ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo del juego"<<endl;
        exit(1);
    }
    cout<<"Contenido de la partida "<<guardado<<endl;
    while(getline(archivo, texto)){
        cout<<texto<<endl;
    }
    archivo.close();
cout<<"Partida cargada correctamente."<<endl;
}

void guardarTorneo(const vector<jugador>& jugadores, const string & nombreArchivo){
    string guardado;
    ofstream archivo(guardado, ios::out);
    int players = jugadores.size();
    cout<<"Ingrese el nombre del archivo donde se va a guardar el torneo"<<endl;
    cin.ignore();
    getline(cin, guardado);
    archivo.open(guardado.c_str(), ios::out);
    if (guardado.find(".txt")==string::npos){
        guardado += ".txt";
    }
    if (archivo.fail()){
        cout<<"No se puedo abrir el archivo del torneo"<<endl;
        exit(1);
    }
    archivo<< "       ===== Estadisticas del Torneo =====" << endl;
    archivo<< left << setw(15) << "Jugador"
           << setw(10) << "Jugados"
           << setw(10) << "Ganados"
           << setw(10) << "Empates"
           << setw(10) << "Perdidos"
           << setw(10) << " Puntos" << endl;
    archivo<< "--------------------------------------------------------------" << endl;
        for(int k = 0; k< players; k++) {
            archivo<< left << setw(16) << jugadores[k].nombre
                   << setw(11) << jugadores[k].jugados
                   << setw(11) << jugadores[k].ganados
                   << setw(11) << jugadores[k].empates
                   << setw(11) << jugadores[k].perdidos
                   << setw(9) << jugadores[k].puntos
                    << endl;                  
}
archivo.close();
cout<<"Torneo guardado exitosamente!"<<endl;
}

void cargarTorneo(const vector<jugador>& jugadores, const string & nombreArchivo){
    ifstream archivo;
    string guardado;
    string texto;
    cout<<"Ingrese el nombre del archivo donde se va a cargar el torneo: "<<endl;
    cin.ignore();
    getline(cin, guardado);
    if (guardado.find(".txt") == string::npos){
        guardado += ".txt";
    }
    archivo.open(guardado.c_str(), ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo del juego."<<endl;
        exit(1);
    }
    cout<<"Contenido del torneo"<<guardado<<endl;
    while (getline(archivo, texto)){
        cout<<texto<<endl;
    }
    archivo.close();
cout<<"Torneo cargado exitosamente!"<<endl;
}

void guardarPartidaAuto(const vector<partida>& partidas) {
    static int contador=1;
    string nombreArchivo = "partida_auto" + to_string(contador) + ".txt";
    ofstream archivo(nombreArchivo);

    if (archivo.fail()){
        cout<<"Error al guardar automaticamente la partida"<<endl;
        exit(1);
    }
    archivo<< "       ===== Estadisticas de la partida =====" << endl;
                           archivo << left << setw(15) << "Jugador"
                             << setw(10) << "Jugados"
                             << setw(10) << "Ganados"
                             << setw(10) << "Empates"
                             << setw(10) << "Perdidos"
                             << setw(10) << " Puntos" << endl;
                        archivo << "--------------------------------------------------------------" << endl;
                    for(int t = 0; t < 2; t++) {
                            archivo << left << setw(16) << partidas[t].player
                                 <<setw(11) << partidas[t].jugados1
                                 <<setw(11) << partidas[t].ganados1
                                 <<setw(11) << partidas[t].empates1
                                 <<setw(11) << partidas[t].perdidos1
                                 <<setw(9) << partidas[t].puntos1
                                    << endl;
                                  }
    
    archivo.close();
    cout << "Partida guardada automaticamente en: " << nombreArchivo << endl;
    contador++;
}

void guardarTorneoAuto(const vector<jugador>& jugadores) {
    static int contador=1;
    string nombreArchivo = "torneo_auto" + to_string(contador) + ".txt";
    ofstream archivo(nombreArchivo);
    int players = jugadores.size();
    if (archivo.fail()){
        cout<<"Error al guardar automaticamente el torneo"<<endl;
        exit(1);
    }
    archivo<< "       ===== Estadisticas del Torneo =====" << endl;
    archivo<< left << setw(15) << "Jugador"
           << setw(10) << "Jugados"
           << setw(10) << "Ganados"
           << setw(10) << "Empates"
           << setw(10) << "Perdidos"
           << setw(10) << " Puntos" << endl;
    archivo<< "--------------------------------------------------------------" << endl;
        for(int k = 0; k< players; k++) {
            archivo<< left << setw(16) << jugadores[k].nombre
                   << setw(11) << jugadores[k].jugados
                   << setw(11) << jugadores[k].ganados
                   << setw(11) << jugadores[k].empates
                   << setw(11) << jugadores[k].perdidos
                   << setw(9) << jugadores[k].puntos
                    << endl;                    
}
}
