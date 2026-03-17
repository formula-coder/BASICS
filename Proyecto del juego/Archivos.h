
#pragma once

#include "personaje.h"
#include "tablero.h"
#include "enemigo.h"
#include <fstream>
#include <string>
using namespace std;

struct DatosPartida {
    Personaje personaje;
    int dimension;
    int totalEnemigos;
    // Los datos completos se guardarán en binario
};

void guardarPartida(Personaje* p, Tablero* t, Enemigo** e, int numEnemigos);
bool cargarPartida(Personaje* p, Tablero* t, Enemigo** e, int& numEnemigos);
void guardarPuntaje(string nombre, int puntaje);

