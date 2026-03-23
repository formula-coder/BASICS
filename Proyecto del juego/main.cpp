#include <iostream>
#include <string>
#include <sstream>
#include "juego2.h"

using namespace std;

int main(int argc, char* argv[]) {
    Juego juego;
    string comando;
    string comandoInicialPendiente;
    bool juegoIniciado = false;

    cout << "[argc/argv] Programa ejecutado desde consola con " << argc - 1
         << " argumento(s)." << endl;
    if (argc > 0) {
        cout << "[argc/argv] argv[0] = " << argv[0] << endl;
    }
    for (int i = 1; i < argc; ++i) {
        cout << "[argc/argv] argv[" << i << "] = " << argv[i] << endl;
    }
    if (argc == 1) {
        cout << "[argc/argv] Sin argumentos. Prueba: start o load" << endl;
    }

    if (argc > 1) {
        comandoInicialPendiente = argv[1];

        if (comandoInicialPendiente == "start") {
            cout << "Iniciando partida desde consola" << endl;
        }
        else if (comandoInicialPendiente == "load") {
            cout << "Cargando partida desde consola" << endl;
        }
    }
    
    if (comandoInicialPendiente == "start") {
        juego.iniciar(10, 5, 3, 2, 1); // valores por defecto
        juegoIniciado = true;
    }
    else if (comandoInicialPendiente == "load") {
        juego.cargarEstado();
        juegoIniciado = true;
    }

    cout << "=== JUEGO DE LA MAZMORRA ===" << endl;
    cout << "Comandos disponibles:" << endl;
    cout << "  Start - Iniciar nueva partida" << endl;
    cout << "  Board - Ver tablero" << endl;
    cout << "  Stats - Ver estadisticas" << endl;
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
            
            cout << "Numero de cofres: ";
            cin >> cofres;
            
            cout << "Numero de Goblins: ";
            cin >> goblins;
            
            cout << "Numero de Arqueros: ";
            cin >> arqueros;
            
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