#pragma once

#include <iostream>
using namespace std;

constexpr char VACIO = '.';
constexpr char PERSONAJE = '@';
constexpr char ENEMIGO = 'E';
constexpr char COFRE = '?';
constexpr char SALIDA = '#';
constexpr char COFRE_ABIERTO = 'O';
constexpr char ENEMIGO_MUERTO = 'X';
constexpr char JEFE = 'J';


struct Celda {
    char simbolo;
    bool tieneCofre;
    bool tieneEnemigo;
    bool esSalida;
    int tipoEnemigo; // 0: ninguno, 1: goblin, 2: arquero, 3: jefe
    int enemigoPV;
    int enemigoPH;
    bool cofreAbierto;
    bool descubierto; // Para revelar enemigos al entrar a la celda
    bool visible; // Para mostrar enemigos al atacar desde lejos (arqueros)

        Celda() {
        simbolo = VACIO;
        tieneCofre = false;
        tieneEnemigo = false;
        esSalida = false;
        tipoEnemigo = 0;
        enemigoPV = 0;
        enemigoPH = 0;
        cofreAbierto = false;
        descubierto = false;
    }
};

class Tablero {
private:
    Celda** celdas;
    int dimension;

public:
    Tablero(int n);
    ~Tablero();
    
    void setCelda(int x, int y, char sim);
    Celda getCelda(int x, int y);
    void setEnemigo(int x, int y, int tipo, int pv, int ph);
    void setCofre(int x, int y);
    void setSalida(int x, int y);
    void mostrar();
    int getDimension() { return dimension; }
    bool posicionValida(int x, int y);
    void abrirCofre(int x, int y);
    void eliminarEnemigo(int x, int y);
    void revelarCelda(int x, int y);
};