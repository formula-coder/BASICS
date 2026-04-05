#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include "Juego.h"

using namespace std;

int main(int argc, char* argv[]) {
    Juego juego;
    string comando;
    string comandoInicialPendiente;
    bool juegoIniciado = false;

    system("cls");

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
    
    if (comandoInicialPendiente == "inicio") {
        juego.iniciar(10, 5, 3, 2, 1); 
        juegoIniciado = true;
    }
    else if (comandoInicialPendiente == "load") {
        juego.cargarEstado();
        juegoIniciado = true;
    }

    cout << "\n=== JUEGO DE LA MAZMORRA ===" << endl;
    cout << "Comandos disponibles:" << endl;
    cout << "  Start - Iniciar nueva partida" << endl;
    cout << "  Board - Ver tablero" << endl;
    cout << "  Stats - Ver estadisticas" << endl;
    cout << "  Move [up|down|left|right] - Moverse" << endl;
    cout << "  Seek - Explorar cofre o Salir de la mazmorra (e)" << endl;
    cout << "  Attack - Atacar enemigo" << endl;
    cout << "  Save - Guardar partida" << endl;
    cout << "  Load - Cargar partida" << endl;
    cout << "  Exit - Salir del juego" << endl;
    cout << endl;

    while (true) {
        cout << "\n> ";
        getline(cin, comando);
        
        if (comando == "Exit" || comando == "exit") {
            cout << "Hasta luego!" << endl;
            break;
        }
        
        if (comando == "Start" || comando == "start") {
            int dimension = -1, cofres = -1, goblins = -1, arqueros = -1, jefe = -1;
            
            system("cls"); 
            cout << "=== NUEVA PARTIDA ===" << endl;
            
            // 1. Validar Dimensión (entre 5 y 30)
            while (dimension < 5 || dimension > 30) {
                cout << "Dimension del tablero (5 a 30): ";
                while (!(cin >> dimension)) { 
                    cout << "Valor incorrecto. Ingresa un numero: "; 
                    cin.clear(); cin.ignore(10000, '\n'); 
                }
                if (dimension < 5 || dimension > 30) cout << "Por favor, ingresa un valor entre 5 y 30." << endl;
            }
            
            // Calculamos el espacio máximo (50% del tablero para no saturarlo)
            int espacioLibre = (dimension * dimension) / 2;
            cout << "(Espacio disponible para generar elementos: " << espacioLibre << " casillas)\n" << endl;
            
            // 2. Validar Cofres
            while (cofres < 0 || cofres > espacioLibre) {
                cout << "Numero de cofres: ";
                while (!(cin >> cofres)) { cout << "Valor incorrecto. Ingresa un numero: "; cin.clear(); cin.ignore(10000, '\n'); }
                if (cofres < 0 || cofres > espacioLibre) cout << "Supera el limite. Maximo permitido: " << espacioLibre << endl;
            }
            espacioLibre -= cofres; // Restamos el espacio que ocuparon los cofres
            
            // 3. Validar Goblins
            while (goblins < 0 || goblins > espacioLibre) {
                cout << "Numero de Goblins: ";
                while (!(cin >> goblins)) { cout << "Valor incorrecto. Ingresa un numero: "; cin.clear(); cin.ignore(10000, '\n'); }
                if (goblins < 0 || goblins > espacioLibre) cout << "Supera el limite. Maximo permitido: " << espacioLibre << endl;
            }
            espacioLibre -= goblins;
            
            // 4. Validar Arqueros
            while (arqueros < 0 || arqueros > espacioLibre) {
                cout << "Numero de Arqueros: ";
                while (!(cin >> arqueros)) { cout << "Valor incorrecto. Ingresa un numero: "; cin.clear(); cin.ignore(10000, '\n'); }
                if (arqueros < 0 || arqueros > espacioLibre) cout << "Supera el limite. Maximo permitido: " << espacioLibre << endl;
            }
            
            // 5. Validar Jefe (Solo 0 o 1)
            while (jefe < 0 || jefe > 1) {
                cout << "Numero de Jefes (0 o 1): ";
                while (!(cin >> jefe)) { cout << "Valor incorrecto. Ingresa un numero: "; cin.clear(); cin.ignore(10000, '\n'); }
                if (jefe < 0 || jefe > 1) cout << "Solo puede haber 0 o 1 jefe." << endl;
            }
            
            cin.ignore(10000, '\n'); // Limpia el enter final
            
            // Inicia el juego con los datos ya verificados y seguros
            juego.iniciar(dimension, cofres, goblins, arqueros, jefe);
            juegoIniciado = true;
        }
        else if (comando == "Load" || comando == "load") {
            system("cls"); // Limpia la pantalla al cargar
            juego.cargarEstado();
            juegoIniciado = true;
        }
        else if (juegoIniciado) {
            juego.procesarComando(comando);
        }
        else {
            cout << "Valor incorrecto. Ingrese la palabra 'Start' para empezar." << endl;
        }
    }
    return 0;
}