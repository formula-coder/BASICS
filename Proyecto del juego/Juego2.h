#pragma once

#include "personaje.h"
#include "tablero.h"
#include "enemigo.h"
#include <iostream>
#include<string>

using namespace std;

class Juego {

    private:
    Personaje* jugador;
    Tablero* tablero;
    Enemigo** enemigos;
    int totalEnemigos;
    bool juegoActivo;

    public:
    Juego();
    ~Juego();
    void iniciar(int dimension, int numcofres, int numGoblins, int numarqueros, int numJefes);
    void mostrarTablero();
    void mostrarStats();
    void moverJugador(string direccion);
    void explorar();
    void atacar();
    void actualizarTurno();
    void finJuego(bool ganado);
    void guardarEstado();
    void cargarEstado();
    void procesarComando(string comando);

private:
    void generarEnemigos(int goblins, int arqueros, int jefe);
    void generarCofres(int cantidad);
    void generarSalida();
    void colocarJugador();
    bool verificarVictoria();
    void ataqueArqueros();
    void moverJefe();
};