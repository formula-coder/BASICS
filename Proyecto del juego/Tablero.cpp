#include "tablero.h"
#include <iostream>
#include <iomanip>
using namespace std;

Tablero::Tablero(int n) {
    dimension = n;
    celdas = new Celda*[dimension];
    for (int i = 0; i < dimension; i++) {
        celdas[i] = new Celda[dimension];
    }
}

Tablero::~Tablero() {
    for (int i = 0; i < dimension; i++) {
        delete[] celdas[i];
    }
    delete[] celdas;
}

void Tablero::setCelda(int x, int y, char sim) {
    if (posicionValida(x, y)) {
        celdas[x][y].simbolo = sim;
    }
}

Celda Tablero::getCelda(int x, int y) {
    if (posicionValida(x, y)) {
        return celdas[x][y];
    }
    return Celda();
}

void Tablero::setEnemigo(int x, int y, int tipo, int pv, int ph) {
    if (posicionValida(x, y)) {
        celdas[x][y].tieneEnemigo = true;
        celdas[x][y].tipoEnemigo = tipo;
        celdas[x][y].enemigoPV = pv;
        celdas[x][y].enemigoPH = ph;
        celdas[x][y].visible = false;
        celdas[x][y].simbolo = ENEMIGO;
    }
}

void Tablero::setCofre(int x, int y) {
    if (posicionValida(x, y)) {
        celdas[x][y].tieneCofre = true;
        celdas[x][y].cofreAbierto = false;
        celdas[x][y].simbolo = COFRE;
    }
}

void Tablero::setSalida(int x, int y) {
    if (posicionValida(x, y)) {
        celdas[x][y].esSalida = true;
        celdas[x][y].simbolo = SALIDA;
    }
}

void Tablero::mostrar() {
for (int i = 0; i < dimension; i++) {
    cout << setw(2) << i << " ";
    for (int j = 0; j < dimension; j++) {

        if (celdas[i][j].tieneEnemigo && !celdas[i][j].visible)
            cout << ENEMIGO << " "; // 👈 oculto (E)
        else
            cout << celdas[i][j].simbolo << " "; // 👈 real

    }
    cout << endl;
}
}

bool Tablero::posicionValida(int x, int y) {
    return (x >= 0 && x < dimension && y >= 0 && y < dimension);
}

void Tablero::abrirCofre(int x, int y) {
    if (posicionValida(x, y) && celdas[x][y].tieneCofre && !celdas[x][y].cofreAbierto) {
        celdas[x][y].cofreAbierto = true;
        celdas[x][y].simbolo = COFRE_ABIERTO;
    }
}

void Tablero::eliminarEnemigo(int x, int y) {
    if (posicionValida(x, y) && celdas[x][y].tieneEnemigo) {
        celdas[x][y].tieneEnemigo = false;
        celdas[x][y].tipoEnemigo = 0;
        celdas[x][y].simbolo = ENEMIGO_MUERTO;
    }
}

void Tablero::revelarCelda(int x, int y) {
    if (posicionValida(x, y)) {
        celdas[x][y].visible = true;

        if (celdas[x][y].tieneEnemigo) {
            if (celdas[x][y].tipoEnemigo == 1)
                celdas[x][y].simbolo = 'G';
            else if (celdas[x][y].tipoEnemigo == 2)
                celdas[x][y].simbolo = 'A';
            else if (celdas[x][y].tipoEnemigo == 3)
                celdas[x][y].simbolo = 'J';
        }
    }
}