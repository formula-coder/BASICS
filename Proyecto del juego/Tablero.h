#pragma once

#include <iostream>
#include <iomanip> // Agregado para el setw
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
    bool descubierto; 
    bool visible; 

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
        visible = false;
    }
};

class Tablero {
private:
    Celda** celdas;
    int dimension;

public:
    Tablero(int n) {
        dimension = n;
        celdas = new Celda*[dimension];
        for (int i = 0; i < dimension; i++) {
            celdas[i] = new Celda[dimension];
        }
    }

    ~Tablero() {
        for (int i = 0; i < dimension; i++) {
            delete[] celdas[i];
        }
        delete[] celdas;
    }
    string comprimirTableroInicial() {//funcion para convertir el tablero a una cadena de texto comprimida
        //función nueva que pidio el profe --------------------------------------
    string resultado = "";  //cadena vacia en la que se va a ir concatenando
    int contadorVacios = 0;  //lleva la cuenta de los espacios vacíos consecutivos
    
    for (int i = 0; i < dimension; i++) {  //reorre cada fila del tablero
        for (int j = 0; j < dimension; j++) { // recorre cada columna de la fila actual
            Celda celda = celdas[i][j];   //contiene la informacion de la celda actual
            char simbolo = celda.simbolo; //el simbolo 
            
            // Verificar si es espacio vacío
            if (simbolo == VACIO) {
                contadorVacios++;
                
                // Si llegamos a 26, escribimos Z y reiniciamos
                if (contadorVacios == 26) {
                    resultado += 'Z';
                    contadorVacios = 0;
                }
            } 
            else {
                // Antes de poner otro elemento, escribimos los vacíos pendientes
                if (contadorVacios > 0) {
                    resultado += (char)('A' + contadorVacios - 1);
                    contadorVacios = 0;
                }
                
                // Escribir el elemento especial
                if (celda.esSalida) {
                    resultado += 'S';
                }
                else if (simbolo == PERSONAJE) {
                    resultado += 'P';
                }
                else if (celda.tieneCofre) {
                    resultado += 'C';
                }
                else if (celda.tieneEnemigo) {
                    
                    switch(celda.tipoEnemigo) {
                        case 1: resultado += 'G'; break;  // Goblin
                        case 2: resultado += 'A'; break;  // Arquero
                        case 3: resultado += 'J'; break;  // Jefe
                        default: resultado += 'E'; break;
                    }
                }
                else {
                    resultado += simbolo;
                }
            }
        }
    }
    
    // Al final del tablero, si quedaron vacíos sin escribir
    if (contadorVacios > 0) {
        resultado += (char)('A' + contadorVacios - 1);
    }
    
    return resultado;
}
    
    void setCelda(int x, int y, char sim) {
        if (posicionValida(x, y)) {
            celdas[x][y].simbolo = sim;
        }
    }

    Celda getCelda(int x, int y) {
        if (posicionValida(x, y)) {
            return celdas[x][y];
        }
        return Celda();
    }

    void setEnemigo(int x, int y, int tipo, int pv, int ph) {
        if (posicionValida(x, y)) {
            celdas[x][y].tieneEnemigo = true;
            celdas[x][y].tipoEnemigo = tipo;
            celdas[x][y].enemigoPV = pv;
            celdas[x][y].enemigoPH = ph;
            celdas[x][y].visible = false;
            celdas[x][y].simbolo = ENEMIGO;
        }
    }

    void setCofre(int x, int y) {
        if (posicionValida(x, y)) {
            celdas[x][y].tieneCofre = true;
            celdas[x][y].cofreAbierto = false;
            celdas[x][y].simbolo = COFRE;
        }
    }

    void setSalida(int x, int y) {
        if (posicionValida(x, y)) {
            celdas[x][y].esSalida = true;
            celdas[x][y].simbolo = SALIDA;
        }
    }

void mostrar() {
        cout << "   "; 
        for (int j = 0; j < dimension; j++) {
            cout << setw(3) << j; 
        }
        cout << "\n";
        for (int i = 0; i < dimension; i++) {
            cout << setw(2) << i << " "; 
            for (int j = 0; j < dimension; j++) {
                char aImprimir;
                if (celdas[i][j].tieneEnemigo && !celdas[i][j].visible) {
                    aImprimir = ENEMIGO;
                } else {
                    aImprimir = celdas[i][j].simbolo;
                }
                cout << setw(3) << aImprimir; 
            }
            cout << "\n";
        }
    }
    int getDimension() { return dimension; }

    bool posicionValida(int x, int y) {
        return (x >= 0 && x < dimension && y >= 0 && y < dimension);
    }

    void abrirCofre(int x, int y) {
        if (posicionValida(x, y) && celdas[x][y].tieneCofre && !celdas[x][y].cofreAbierto) {
            celdas[x][y].cofreAbierto = true;
            celdas[x][y].simbolo = COFRE_ABIERTO;
        }
    }

    void eliminarEnemigo(int x, int y) {
        if (posicionValida(x, y) && celdas[x][y].tieneEnemigo) {
            celdas[x][y].tieneEnemigo = false;
            celdas[x][y].tipoEnemigo = 0;
            celdas[x][y].simbolo = ENEMIGO_MUERTO;
        }
    }

    void revelarCelda(int x, int y) {
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
};