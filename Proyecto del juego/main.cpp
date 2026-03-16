#include <iostream>
#include <string>
#include <sstream>
#include "juego2.h"

using namespace std;

int main() {
    Juego juego;
    string comando;
    bool juegoIniciado = false;
    
    cout << "=== JUEGO DE LA MAZMORRA ===" << endl;
    cout << "Comandos disponibles:" << endl;
    cout << "  Start - Iniciar nueva partida" << endl;
    cout << "  Board - Ver tablero" << endl;
    cout << "  Stats - Ver estadísticas" << endl;
    cout << "  Move [up|down|left|right] - Moverse" << endl;
    cout << "  Seek - Explorar cofre" << endl;
    cout << "  Attack - Atacar enemigo" << endl;
    cout << "  Save - Guardar partida" << endl;
    cout << "  Load - Cargar partida" << endl;
    cout << "  Exit - Salir del juego" << endl;
    cout << endl;
    
    while (true) {
        cout << "\n> ";
        getline(cin, comando);
        
        if (comando == "Exit" || comando == "exit") {
            cout << "¡Hasta luego!" << endl;
            break;
        }
        
        if (comando == "Start" || comando == "start") {
            int dimension, cofres, goblins, arqueros, jefe;
            
            cout << "=== NUEVA PARTIDA ===" << endl;
            cout << "Dimension del tablero: ";
            cin >> dimension;
            cin.ignore();
            
            cout << "Numero de cofres: ";
            cin >> cofres;
            cin.ignore();
            
            cout << "Numero de Goblins: ";
            cin >> goblins;
            cin.ignore();
            
            cout << "Numero de Arqueros: ";
            cin >> arqueros;
            cin.ignore();
            
            cout << "Numero de Jefes (0 o 1): ";
            cin >> jefe;
            cin.ignore();
            
            juego.iniciar(dimension, cofres, goblins, arqueros, jefe);
            juegoIniciado = true;
        }
        else if (comando == "Load" || comando == "load") {
            juego.cargarEstado();
            juegoIniciado = true;
        }
        else if (juegoIniciado) {
            juego.procesarComando(comando);
        }
        else {
            cout << "Debes iniciar o cargar una partida primero. Usa 'Start' o 'Load'." << endl;
        }
    }
    
    return 0;
}