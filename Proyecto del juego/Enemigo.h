#pragma once

#include<iostream>
using namespace std;

struct Enemigo {
    int tipo; // 1: Goblin, 2: Arquero, 3: Jefe
    int PV;
    int PH;
    int posX;
    int posY;
    bool vivo;
    
    Enemigo(int t, int x, int y) {
        tipo = t;
        posX = x;
        posY = y;
        vivo = true;
        
        switch(tipo) {
            case 1: // Goblin
                PV = 30;
                PH = 10;
                break;
            case 2: // Arquero
                PV = 20;
                PH = 10;
                break;
            case 3: // Jefe
                PV = 60;
                PH = 40;
                break;
        }
    }
    
    void recibirDanio(int danio) {
        PV -= danio;
        if (PV <= 0) {
            PV = 0;
            vivo = false;
            cout << "Has derrotado al enemigo!" << endl;
        } else {
            cout << "Enemigo recibe " << danio << " de dano. PV restantes: " << PV << endl;
        }
    }
    
    int getRecompensaPH() {
        switch(tipo) {
            case 1: return 2;
            case 2: return 3;
            case 3: return 5;
            default: return 0;
        }
    }
    
    string getTipoString() {
        switch(tipo) {
            case 1: return "Goblin";
            case 2: return "Arquero";
            case 3: return "Jefe";
            default: return "Desconocido";
        }
    }
};