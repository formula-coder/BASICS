#pragma once

#include "personaje.h"
#include "tablero.h"
#include "enemigo.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct DatosPartida {
    Personaje personaje;
    int dimension;
    int totalEnemigos;
};

inline void guardarPartida(Personaje* p, Tablero* t, Enemigo** e, int numEnemigos) {
    ofstream archivo("partida.bin", ios::binary);
    
    if (!archivo) {
        cout << "Error al guardar la partida" << endl;
        return;
    }
    
    // Guardar personaje
    archivo.write(reinterpret_cast<char*>(p), sizeof(Personaje));
    
    // Guardar dimensión del tablero
    int dim = t->getDimension();
    archivo.write(reinterpret_cast<char*>(&dim), sizeof(int));
    
    // Guardar número de enemigos
    archivo.write(reinterpret_cast<char*>(&numEnemigos), sizeof(int));
    
    // Guardar enemigos
    for (int i = 0; i < numEnemigos; i++) {
        if (e[i] != nullptr) {
            archivo.write(reinterpret_cast<char*>(e[i]), sizeof(Enemigo));
        }
    }
    
    archivo.close();
    cout << "Partida guardada exitosamente" << endl;
}

inline bool cargarPartida(Personaje* p, Tablero* t, Enemigo** e, int& numEnemigos) {
    ifstream archivo("partida.bin", ios::binary);
    
    if (!archivo) {
        cout << "No hay partida guardada" << endl;
        return false;
    }
    
    // Cargar personaje
    archivo.read(reinterpret_cast<char*>(p), sizeof(Personaje));
    
    // Cargar dimensión del tablero
    int dim;
    archivo.read(reinterpret_cast<char*>(&dim), sizeof(int));
    
    // Cargar número de enemigos
    archivo.read(reinterpret_cast<char*>(&numEnemigos), sizeof(int));
    
    // Cargar enemigos
    for (int i = 0; i < numEnemigos; i++) {
        e[i] = new Enemigo(0, 0, 0);
        archivo.read(reinterpret_cast<char*>(e[i]), sizeof(Enemigo));
    }
    
    archivo.close();
    cout << "Partida cargada exitosamente" << endl;
    return true;
}

inline void guardarPuntaje(string nombre, int puntaje) {
    ofstream archivo("puntajes.txt", ios::app);
    
    if (archivo) {
        archivo << nombre << ": " << puntaje << " puntos" << endl;
        archivo.close();
    }
}