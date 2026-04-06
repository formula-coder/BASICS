#pragma once

#include "personaje.h"
#include "tablero.h"
#include "enemigo.h"
#include "archivos.h" // Se agrega porque ahora Juego usa directamente Archivos
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>

using namespace std;

class Juego {

private:
    Personaje* jugador;
    Tablero* tablero;
    Enemigo** enemigos;
    int totalEnemigos;
    bool juegoActivo;

public:
    Juego() {
        jugador = new Personaje();
        tablero = nullptr;
        enemigos = nullptr;
        totalEnemigos = 0;
        juegoActivo = true;
        srand(time(nullptr));
    }

    ~Juego() {
        delete jugador;
        delete tablero;
        if (enemigos != nullptr) {
            for (int i = 0; i < totalEnemigos; i++) {
                delete enemigos[i];
            }
            delete[] enemigos;
        }
    }

    void iniciar(int dimension, int numCofres, int numGoblins, int numArqueros, int numJefe) {
        if (tablero != nullptr) {
            delete tablero;
        }
        tablero = new Tablero(dimension);
        
        if (enemigos != nullptr) {
            for (int i = 0; i < totalEnemigos; i++) {
                delete enemigos[i];
            }
            delete[] enemigos;
        }
        
        cout << "Ingresa el nombre de tu personaje: ";
        cin.getline(jugador->nombre, 50);
        
        jugador->PV = 100;
        jugador->PH = 20;
        jugador->oro = 0;
        juegoActivo = true;

        generarSalida();
        colocarJugador();
        generarEnemigos(numGoblins, numArqueros, numJefe);
        generarCofres(numCofres);

        string codigoMapa = tablero->comprimirTableroInicial();
    cout << "\n=== CODIGO DEL MAPA GENERADO ===" << endl;
    cout << "Codigo: " << codigoMapa << endl;
    cout << "==================================" << endl;
        
        cout << "\n=== JUEGO INICIADO ===" << endl;
        cout << "Personaje: " << jugador->nombre << endl;
        cout << "PV: " << jugador->PV << " | PH: " << jugador->PH << " | Oro: " << jugador->oro << endl;
        cout << "Tablero de " << dimension << "x" << dimension << " creado." << endl;

        mostrarTablero();
    }

    void mostrarTablero() {
        cout << "\n=== TABLERO ACTUAL ===" << endl;
        tablero->mostrar();
        cout << "Posicion del jugador: [" << jugador->posX << "," << jugador->posY << "]" << endl;
    }

    void mostrarStats() {
        cout << "\n=== ESTADISTICAS DEL PERSONAJE ===" << endl;
        cout << "Nombre: " << jugador->nombre << endl;
        cout << "Puntos de Vida (PV): " << jugador->PV << endl;
        cout << "Puntos de Habilidad (PH): " << jugador->PH << endl;
        cout << "Oro: " << jugador->oro << endl;
        cout << "Posicion: [" << jugador->posX << "," << jugador->posY << "]" << endl;
    }

    void moverJugador(string direccion) {
        int nuevoX = jugador->posX;
        int nuevoY = jugador->posY;
        
        if (direccion == "up") nuevoX--;
        else if (direccion == "down") nuevoX++;
        else if (direccion == "left") nuevoY--;
        else if (direccion == "right") nuevoY++;
        else {
            cout << "Direccion no valida" << endl;
            return;
        }
        
        if (!tablero->posicionValida(nuevoX, nuevoY)) {
            cout << "No puedes moverte fuera del tablero" << endl;
            return;
        }
        
        Celda celdaDestino = tablero->getCelda(nuevoX, nuevoY);
        Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);

        if (celdaActual.tieneCofre) {
            if (celdaActual.cofreAbierto)
                tablero->setCelda(jugador->posX, jugador->posY, COFRE_ABIERTO);
            else
                tablero->setCelda(jugador->posX, jugador->posY, COFRE);
        }
        else if (celdaActual.tieneEnemigo) {
            tablero->setCelda(jugador->posX, jugador->posY, ENEMIGO);
        }
        else if (celdaActual.esSalida) {
            tablero->setCelda(jugador->posX, jugador->posY, SALIDA);
        }
        else if (celdaActual.simbolo == ENEMIGO_MUERTO) { 
            tablero->setCelda(jugador->posX, jugador->posY, ENEMIGO_MUERTO);
        }
        else {
            tablero->setCelda(jugador->posX, jugador->posY, VACIO);
        }
        
        jugador->posX = nuevoX;
        jugador->posY = nuevoY;
        tablero->setCelda(jugador->posX, jugador->posY, PERSONAJE);
        tablero->revelarCelda(nuevoX, nuevoY); 
        
        cout << "Te has movido a [" << nuevoX << "," << nuevoY << "]" << endl;

        if (celdaDestino.tieneEnemigo) {
            if (celdaDestino.tipoEnemigo == 1) {
                cout << "Te encontraste con un Goblin!" << endl;
                jugador->recibirDanio(10);
                tablero->setCelda(nuevoX, nuevoY, 'G'); 
            }
            else if (celdaDestino.tipoEnemigo == 2) {
                cout << "Te encontraste con un Arquero!" << endl;
                jugador->recibirDanio(10);
                tablero->setCelda(nuevoX, nuevoY, 'A'); 
            }
            else if (celdaDestino.tipoEnemigo == 3) {
                cout << "CUIDADO! Es el JEFE!" << endl;
                jugador->recibirDanio(20);
                tablero->setCelda(nuevoX, nuevoY, 'J'); 
            }
        }

        if (jugador->PV <= 0) {
            finJuego(false);
        }
    }

    void explorar() {
        Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);
        
        if (!celdaActual.tieneCofre) {
            cout << "No hay cofre en esta casilla" << endl;
            return;
        }
        if (celdaActual.cofreAbierto) {
            cout << "Este cofre ya ha sido abierto" << endl;
            return;
        }
        
        cout << "Has encontrado un cofre!" << endl;
        int probabilidad = rand() % 100;
        
        if (probabilidad < 50) { 
            int oro = 10;
            jugador->agregarOro(oro);
            cout << "Has encontrado " << oro << " piezas de oro!" << endl;
        }
        else if (probabilidad < 80) { 
            jugador->curar(50);
            cout << "Has encontrado una pocion de vida! +50 PV" << endl;
        }
        else { 
            cout << "Es una trampa! El cofre te ataca" << endl;
            int danio = jugador->PV * 0.20; 
            if (danio < 1) danio = 1; 
            jugador->recibirDanio(danio); 
            cout << "La trampa te hizo " << danio << " de dano (" << "20% de tu vida)" << endl;
        }
        
        tablero->abrirCofre(jugador->posX, jugador->posY);
    }

    void atacar() {
        Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);
        
        if (!celdaActual.tieneEnemigo) {
            cout << "No hay enemigo en esta casilla" << endl;
            return;
        }
        
        Enemigo* enemigoActual = nullptr;
        for (int i = 0; i < totalEnemigos; i++) {
            if (enemigos[i] != nullptr && enemigos[i]->vivo && 
                enemigos[i]->posX == jugador->posX && enemigos[i]->posY == jugador->posY) {
                enemigoActual = enemigos[i];
                break;
            }
        }
        
        if (enemigoActual == nullptr) {
            cout << "Error: No se encontro el enemigo" << endl;
            return;
        }
        
        cout << "Atacas al " << enemigoActual->getTipoString() << "!" << endl;
        
        int danio = 10 + (jugador->PH / 5);
        enemigoActual->recibirDanio(danio);
        
        if (!enemigoActual->vivo) {
            jugador->aumentarHabilidad(enemigoActual->getRecompensaPH());
            tablero->eliminarEnemigo(jugador->posX, jugador->posY);
            cout << "Has derrotado al " << enemigoActual->getTipoString() << "!" << endl;
        }
    }

    void actualizarTurno() {
        cout << "\n=== FIN DEL TURNO ===" << endl;
        ataqueArqueros();
        moverJefe();
        if (jugador->PV <= 0) {
            finJuego(false);
        }
    }

    void finJuego(bool ganado) {
        juegoActivo = false;
        cout << "\n=== FIN DEL JUEGO ===" << endl;
        if (ganado) {
            cout << "Felicidades! Has escapado de la mazmorra." << endl;
        } else {
            cout << "Game Over. Has sido derrotado." << endl;
        }
        
        int B = ganado ? 100 : 0;
        int puntaje = B + (jugador->oro * 2) + (jugador->PV * 2) + (jugador->PH * 5);
        
        cout << "\n=== PUNTAJE FINAL ===" << endl;
        cout << "Nombre: " << jugador->nombre << endl;
        cout << "Oro: " << jugador->oro << " x2 = " << (jugador->oro * 2) << endl;
        cout << "PV: " << jugador->PV << " x2 = " << (jugador->PV * 2) << endl;
        cout << "PH: " << jugador->PH << " x5 = " << (jugador->PH * 5) << endl;
        cout << "Puntaje base: " << B << endl;
        cout << "PUNTAJE TOTAL: " << puntaje << endl;
        
        guardarPuntaje(jugador->nombre, puntaje);
    }

    void guardarEstado() {
        guardarPartida(jugador, tablero, enemigos, totalEnemigos);
    }

    void cargarEstado() {
        if (cargarPartida(jugador, tablero, enemigos, totalEnemigos)) {
            cout << "Partida cargada. Bienvenido de vuelta!" << endl;
        }
    }

    void procesarComando(string comando) {
        if (!juegoActivo) {
            cout << "El juego ha terminado. Usa 'Start' para comenzar una nueva partida." << endl;
            return;
        }

        if (comando == "Board" || comando == "board" || comando == "b") {
            mostrarTablero();
        }
        else if (comando == "Stats" || comando == "stats" || comando == "i") {
            mostrarStats();
        }
        else if (comando == "w" || comando == "s" || comando == "a" || comando == "d") {
            if (comando == "w") moverJugador("up");
            else if (comando == "s") moverJugador("down");
            else if (comando == "a") moverJugador("left");
            else moverJugador("right");
            actualizarTurno();
            mostrarTablero();
        }
        else if (comando.rfind("Move ", 0) == 0 || comando.rfind("move ", 0) == 0) {
            string direccion = comando.substr(comando.find(" ") + 1);
            moverJugador(direccion);
            actualizarTurno();
            mostrarTablero();
        }
        else if (comando == "Seek" || comando == "seek" || comando == "e") {
            if (verificarVictoria()) {
                // Victoria manejada adentro
            } 
            else {
                explorar();
                actualizarTurno();
                if (juegoActivo) {
                    mostrarTablero();
                }
            }
        }
        else if (comando == "Attack" || comando == "attack" || comando == "f") {
            atacar();
            actualizarTurno();
            mostrarTablero();
        }
        else if (comando == "Save" || comando == "save") {
            guardarEstado();
        }
        else if (comando == "Load" || comando == "load") {
            cargarEstado();
            mostrarTablero(); 
        }
        else {
            cout << "Comando no reconocido" << endl;
        }
    }

private:
    void generarEnemigos(int goblins, int arqueros, int jefe) {
        totalEnemigos = goblins + arqueros + jefe;
        enemigos = new Enemigo*[totalEnemigos];
        int index = 0;
        
        for (int i = 0; i < goblins; i++) {
            int x, y;
            do {
                x = rand() % tablero->getDimension();
                y = rand() % tablero->getDimension();
            } while (tablero->getCelda(x, y).simbolo != VACIO || 
                     (abs(x - jugador->posX) < 2 && abs(y - jugador->posY) < 2) ||
                     tablero->getCelda(x, y).esSalida);
            
            enemigos[index] = new Enemigo(1, x, y);
            tablero->setEnemigo(x, y, 1, 30, 10);
            index++;
        }
        
        for (int i = 0; i < arqueros; i++) {
            int x, y;
            do {
                x = rand() % tablero->getDimension();
                y = rand() % tablero->getDimension();
            } while (tablero->getCelda(x, y).simbolo != VACIO || 
                     (abs(x - jugador->posX) < 2 && abs(y - jugador->posY) < 2) ||
                     tablero->getCelda(x, y).esSalida);
            
            enemigos[index] = new Enemigo(2, x, y);
            tablero->setEnemigo(x, y, 2, 20, 10);
            index++;
        }
        
        if (jefe > 0) {
            int x, y;
            do {
                x = rand() % tablero->getDimension();
                y = rand() % tablero->getDimension();
            } while (tablero->getCelda(x, y).simbolo != VACIO || 
                     (abs(x - jugador->posX) < 3 && abs(y - jugador->posY) < 3) ||
                     tablero->getCelda(x, y).esSalida);
            
            enemigos[index] = new Enemigo(3, x, y);
            tablero->setEnemigo(x, y, 3, 60, 40);
        }
    }

    void generarCofres(int cantidad) {
        for (int i = 0; i < cantidad; i++) {
            int x, y;
            do {
                x = rand() % tablero->getDimension();
                y = rand() % tablero->getDimension();
            } while (tablero->getCelda(x, y).simbolo != VACIO || 
                     (abs(x - jugador->posX) < 2 && abs(y - jugador->posY) < 2));
            
            tablero->setCofre(x, y);
        }
    }

    void generarSalida() {
        int borde = rand() % 4; 
        int pos;
        int x, y;
        
        switch(borde) {
            case 0: 
                pos = rand() % tablero->getDimension();
                x = 0;
                y = pos;
                break;
            case 1: 
                pos = rand() % tablero->getDimension();
                x = tablero->getDimension() - 1;
                y = pos;
                break;
            case 2: 
                pos = rand() % tablero->getDimension();
                x = pos;
                y = 0;
                break;
            case 3: 
                pos = rand() % tablero->getDimension();
                x = pos;
                y = tablero->getDimension() - 1;
                break;
        }
        tablero->setSalida(x, y);
    }

    void colocarJugador() {
        int centro = tablero->getDimension() / 2;
        int offsetX = rand() % 3 - 1; 
        int offsetY = rand() % 3 - 1;
        
        jugador->posX = centro + offsetX;
        jugador->posY = centro + offsetY;
        
        if (jugador->posX < 0) jugador->posX = 0;
        if (jugador->posX >= tablero->getDimension()) jugador->posX = tablero->getDimension() - 1;
        if (jugador->posY < 0) jugador->posY = 0;
        if (jugador->posY >= tablero->getDimension()) jugador->posY = tablero->getDimension() - 1;
        
        tablero->setCelda(jugador->posX, jugador->posY, PERSONAJE);
    }

    bool verificarVictoria() {
        Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);
        if (celdaActual.esSalida) {
            finJuego(true);
            return true;
        }
        return false;
    }

    void ataqueArqueros() {
        for (int i = 0; i < totalEnemigos; i++) {
            if (enemigos[i] != nullptr && enemigos[i]->vivo && enemigos[i]->tipo == 2) { 
                int dx = abs(enemigos[i]->posX - jugador->posX);
                int dy = abs(enemigos[i]->posY - jugador->posY);
                
                if (dx + dy == 1){
                    cout << "Un arquero te dispara desde [" << enemigos[i]->posX << "," << enemigos[i]->posY << "]!" << endl;
                    jugador->recibirDanio(10); 
                }
            }
        }
    }

void moverJefe() {
        Enemigo* jefe = nullptr;
        for (int i = 0; i < totalEnemigos; i++) {
            if (enemigos[i] != nullptr && enemigos[i]->vivo && enemigos[i]->tipo == 3) {
                jefe = enemigos[i];
                break;
            }
        }
        
        if (jefe == nullptr) return;
        
        static int contadorTurnos = 0;
        contadorTurnos++;
        
        if (contadorTurnos >= 2) {
            contadorTurnos = 0;
            
            int salidaX = -1, salidaY = -1;
            for (int i = 0; i < tablero->getDimension(); i++) {
                for (int j = 0; j < tablero->getDimension(); j++) {
                    if (tablero->getCelda(i, j).esSalida) {
                        salidaX = i;
                        salidaY = j;
                        break;
                    }
                }
            }
            
            if (salidaX != -1) {
                int nuevoX = jefe->posX;
                int nuevoY = jefe->posY;
                
                if (jefe->posX < salidaX) nuevoX++;
                else if (jefe->posX > salidaX) nuevoX--;
                
                if (jefe->posY < salidaY) nuevoY++;
                else if (jefe->posY > salidaY) nuevoY--;
                
                if (tablero->posicionValida(nuevoX, nuevoY)) {
                    
                    bool esJugador = (nuevoX == jugador->posX && nuevoY == jugador->posY);
                    bool esSalida = tablero->getCelda(nuevoX, nuevoY).esSalida;
                    
                    if (esJugador) {
                        // Si choca contigo, te ataca pero NO ocupa tu casilla
                        cout << "¡El Jefe te ha alcanzado y te ataca de frente!" << endl;
                        jugador->recibirDanio(20); 
                    } 
                    else if (esSalida) {
                        // Si choca con la salida, no la pisa, se queda custodiándola
                        cout << "El Jefe ha llegado a la salida y la esta custodiando..." << endl;
                    } 
                    else {
                        // Si no eres tú ni la salida, arrasa con lo que haya en la casilla
                        tablero->eliminarEnemigo(jefe->posX, jefe->posY);
                        tablero->setCelda(jefe->posX, jefe->posY, VACIO);
                        
                        jefe->posX = nuevoX;
                        jefe->posY = nuevoY;
                        tablero->setEnemigo(nuevoX, nuevoY, 3, jefe->PV, jefe->PH);
                        
                        cout << "El Jefe avanza implacablemente..." << endl;
                    }
                }
            }
        }
    }
};