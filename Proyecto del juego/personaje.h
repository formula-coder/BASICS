#pragma once

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct Personaje {
   char nombre[50];
    int PV; // Puntos de Vida
    int PH; // Puntos de Habilidad
    int oro;
    int posX;
    int posY;

       Personaje() {
        strcpy(nombre, "Heroe");
        PV = 100;
        PH = 20;
        oro = 0;
        posX = 0;
        posY = 0;
    }
        void recibirDanio(int daño) {
        PV -= daño;
        if (PV < 0) PV = 0;
        cout << "Has recibido " << daño << " puntos de dano!" << endl;
    }
      void curar(int cantidad) {
        PV += cantidad;
        cout << "Has recuperado " << cantidad << " PV!" << endl;
    }
        void aumentarHabilidad(int cantidad) {
        PH += cantidad;
        cout << "PH aumentado en " << cantidad << " puntos!" << endl;
    }
    
    void agregarOro(int cantidad) {
        oro += cantidad;
        cout << "Has encontrado " << cantidad << " piezas de oro!" << endl;
    }
};