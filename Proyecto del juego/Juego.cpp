#include "juego2.h"
#include "archivos.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
using namespace std;

Juego::Juego() {
    jugador = new Personaje();
    tablero = nullptr;
    enemigos = nullptr;
    totalEnemigos = 0;
    juegoActivo = true;
    srand(time(nullptr));
}

Juego::~Juego() {
    delete jugador;
    delete tablero;
    if (enemigos != nullptr) {
        for (int i = 0; i < totalEnemigos; i++) {
            delete enemigos[i];
        }
        delete[] enemigos;
    }
}

void Juego::iniciar(int dimension, int numCofres, int numGoblins, int numArqueros, int numJefe) {
  
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
    
    // Generar elementos del juego
    generarSalida();
    colocarJugador();
    generarEnemigos(numGoblins, numArqueros, numJefe);
    generarCofres(numCofres);
    
    cout << "\n=== JUEGO INICIADO ===" << endl;
    cout << "Personaje: " << jugador->nombre << endl;
    cout << "PV: " << jugador->PV << " | PH: " << jugador->PH << " | Oro: " << jugador->oro << endl;
    cout << "Tablero de " << dimension << "x" << dimension << " creado." << endl;

    mostrarTablero();

}

void Juego::generarSalida() {
    int borde = rand() % 4; // 0: arriba, 1: abajo, 2: izquierda, 3: derecha
    int pos;
    int x, y;
    
    switch(borde) {
        case 0: // arriba
            pos = rand() % tablero->getDimension();
            x = 0;
            y = pos;
            break;
        case 1: // abajo
            pos = rand() % tablero->getDimension();
            x = tablero->getDimension() - 1;
            y = pos;
            break;
        case 2: // izquierda
            pos = rand() % tablero->getDimension();
            x = pos;
            y = 0;
            break;
        case 3: // derecha
            pos = rand() % tablero->getDimension();
            x = pos;
            y = tablero->getDimension() - 1;
            break;
    }
    
    tablero->setSalida(x, y);
}

void Juego::colocarJugador() {
    int centro = tablero->getDimension() / 2;
    int offsetX = rand() % 3 - 1; // -1, 0, 1
    int offsetY = rand() % 3 - 1;
    
    jugador->posX = centro + offsetX;
    jugador->posY = centro + offsetY;
    
    // Asegurar que está dentro del tablero
    if (jugador->posX < 0) jugador->posX = 0;
    if (jugador->posX >= tablero->getDimension()) jugador->posX = tablero->getDimension() - 1;
    if (jugador->posY < 0) jugador->posY = 0;
    if (jugador->posY >= tablero->getDimension()) jugador->posY = tablero->getDimension() - 1;
    
    tablero->setCelda(jugador->posX, jugador->posY, PERSONAJE);
}

void Juego::generarEnemigos(int goblins, int arqueros, int jefe) {
    totalEnemigos = goblins + arqueros + jefe;
    enemigos = new Enemigo*[totalEnemigos];
    int index = 0;
    
    // Generar Goblins
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
    
    // Generar Arqueros
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
    
    // Generar Jefe (solo uno)
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

void Juego::generarCofres(int cantidad) {
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

void Juego::mostrarTablero() {
    cout << "\n=== TABLERO ACTUAL ===" << endl;
    tablero->mostrar();
    cout << "Posición del jugador: [" << jugador->posX << "," << jugador->posY << "]" << endl;
}

void Juego::mostrarStats() {
    cout << "\n=== ESTADÍSTICAS DEL PERSONAJE ===" << endl;
    cout << "Nombre: " << jugador->nombre << endl;
    cout << "Puntos de Vida (PV): " << jugador->PV << endl;
    cout << "Puntos de Habilidad (PH): " << jugador->PH << endl;
    cout << "Oro: " << jugador->oro << endl;
    cout << "Posición: [" << jugador->posX << "," << jugador->posY << "]" << endl;
}

void Juego::moverJugador(string direccion) {
    int nuevoX = jugador->posX;
    int nuevoY = jugador->posY;
    
    if (direccion == "up") nuevoX--;
    else if (direccion == "down") nuevoX++;
    else if (direccion == "left") nuevoY--;
    else if (direccion == "right") nuevoY++;
    else {
        cout << "Dirección no válida" << endl;
        return;
    }
    
    if (!tablero->posicionValida(nuevoX, nuevoY)) {
        cout << "No puedes moverte fuera del tablero" << endl;
        return;
    }
    
    Celda celdaDestino = tablero->getCelda(nuevoX, nuevoY);
    
    // Limpiar posición actual
    // Restaurar lo que había en la celda antes de movernos
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
else if (celdaActual.simbolo == ENEMIGO_MUERTO) { // 👈 IMPORTANTE
    tablero->setCelda(jugador->posX, jugador->posY, ENEMIGO_MUERTO);
}
else {
    tablero->setCelda(jugador->posX, jugador->posY, VACIO);
}
    
    // Mover jugador
    jugador->posX = nuevoX;
    jugador->posY = nuevoY;
    tablero->setCelda(jugador->posX, jugador->posY, PERSONAJE);
    tablero->revelarCelda(nuevoX, nuevoY); // 👈 REVELA enemigos al entrar a la celda
    
    cout << "Te has movido a [" << nuevoX << "," << nuevoY << "]" << endl;

    // Verificar si hay enemigo en la nueva posición
if (celdaDestino.tieneEnemigo) {

    if (celdaDestino.tipoEnemigo == 1) {
        cout << "¡Te encontraste con un Goblin!" << endl;
        jugador->recibirDanio(10);
        tablero->setCelda(nuevoX, nuevoY, 'G'); // 👈 REVELA
    }
    else if (celdaDestino.tipoEnemigo == 2) {
        cout << "¡Te encontraste con un Arquero!" << endl;
        jugador->recibirDanio(10);
        tablero->setCelda(nuevoX, nuevoY, 'A'); // 👈 REVELA
    }
    else if (celdaDestino.tipoEnemigo == 3) {
        cout << "¡CUIDADO! ¡Es el JEFE!" << endl;
        jugador->recibirDanio(20);
        tablero->setCelda(nuevoX, nuevoY, 'J'); // 👈 REVELA
    }
}

if (jugador->PV <= 0) {
    finJuego(false);
}
}

void Juego::explorar() {
    Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);
    
    if (!celdaActual.tieneCofre) {
        cout << "No hay cofre en esta casilla" << endl;
        return;
    }
    
    if (celdaActual.cofreAbierto) {
        cout << "Este cofre ya ha sido abierto" << endl;
        return;
    }
    
    cout << "¡Has encontrado un cofre!" << endl;
    
    int probabilidad = rand() % 100;
    
    if (probabilidad < 50) { // 50% oro
        int oro = 10;
        jugador->agregarOro(oro);
        cout << "¡Has encontrado " << oro << " piezas de oro!" << endl;
    }
    else if (probabilidad < 80) { // 30% poción
        jugador->curar(50);
        cout << "¡Has encontrado una poción de vida! +50 PV" << endl;
    }
    else { // 20% trampa
        cout << "¡Es una trampa! El cofre te ataca" << endl;
        int danio = jugador->PV * 0.20; // 20% de la vida actual
            if (danio < 1) danio = 1; // evitar 0
        jugador->recibirDanio(danio); // Daño fijo de 20 puntos
        cout << "La trampa te hizo " << danio << " de daño (" << "20% de tu vida)" << endl;
    }
    
    tablero->abrirCofre(jugador->posX, jugador->posY);
}

void Juego::atacar() {
    Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);
    
    if (!celdaActual.tieneEnemigo) {
        cout << "No hay enemigo en esta casilla" << endl;
        return;
    }
    
    // Buscar el enemigo en el arreglo
    Enemigo* enemigoActual = nullptr;
    for (int i = 0; i < totalEnemigos; i++) {
        if (enemigos[i] != nullptr && enemigos[i]->vivo && 
            enemigos[i]->posX == jugador->posX && enemigos[i]->posY == jugador->posY) {
            enemigoActual = enemigos[i];
            break;
        }
    }
    
    if (enemigoActual == nullptr) {
        cout << "Error: No se encontró el enemigo" << endl;
        return;
    }
    
    cout << "Atacas al " << enemigoActual->getTipoString() << "!" << endl;
    
    // Calcular daño (basado en PH del jugador)
    int danio = 10 + (jugador->PH / 5);
    enemigoActual->recibirDanio(danio);
    
    if (!enemigoActual->vivo) {
        // Enemigo derrotado
        jugador->aumentarHabilidad(enemigoActual->getRecompensaPH());
        tablero->eliminarEnemigo(jugador->posX, jugador->posY);
        cout << "¡Has derrotado al " << enemigoActual->getTipoString() << "!" << endl;
    }
}

void Juego::ataqueArqueros() {
    for (int i = 0; i < totalEnemigos; i++) {
        if (enemigos[i] != nullptr && enemigos[i]->vivo && enemigos[i]->tipo == 2) { // Arquero
            int dx = abs(enemigos[i]->posX - jugador->posX);
            int dy = abs(enemigos[i]->posY - jugador->posY);
            
            // Si está en casilla adyacente (distancia 1 en cualquier dirección)
            if (dx + dy == 1){
                cout << "¡Un arquero te dispara desde [" << enemigos[i]->posX << "," << enemigos[i]->posY << "]!" << endl;
                jugador->recibirDanio(10); // Daño del arquero
            }
        }
    }
}

void Juego::moverJefe() {
    // Buscar jefe
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
        
        // Buscar salida
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
            // Mover jefe hacia la salida
            int nuevoX = jefe->posX;
            int nuevoY = jefe->posY;
            
            if (jefe->posX < salidaX) nuevoX++;
            else if (jefe->posX > salidaX) nuevoX--;
            
            if (jefe->posY < salidaY) nuevoY++;
            else if (jefe->posY > salidaY) nuevoY--;
            
            // Verificar que la nueva posición sea válida y esté vacía
            if (tablero->posicionValida(nuevoX, nuevoY) && 
                tablero->getCelda(nuevoX, nuevoY).simbolo == VACIO) {
                
                // Limpiar posición anterior
                tablero->setCelda(jefe->posX, jefe->posY, VACIO);
                
                // Mover jefe
                jefe->posX = nuevoX;
                jefe->posY = nuevoY;
                tablero->setEnemigo(nuevoX, nuevoY, 3, jefe->PV, jefe->PH);
                
                cout << "El Jefe se ha movido más cerca de la salida..." << endl;
            }
        }
    }
}

void Juego::actualizarTurno() {
    cout << "\n=== FIN DEL TURNO ===" << endl;
    
    // Ataque de arqueros
    ataqueArqueros();
    
    // Mover jefe
    moverJefe();
    
    // Verificar si el jugador ha muerto
    if (jugador->PV <= 0) {
        finJuego(false);
    }
}

bool Juego::verificarVictoria() {
    Celda celdaActual = tablero->getCelda(jugador->posX, jugador->posY);
    if (celdaActual.esSalida) {
        finJuego(true);
        return true;
    }
    return false;
}

void Juego::finJuego(bool ganado) {
    juegoActivo = false;
    
    cout << "\n=== FIN DEL JUEGO ===" << endl;
    
    if (ganado) {
        cout << "¡Felicidades! Has escapado de la mazmorra." << endl;
    } else {
        cout << "Game Over. Has sido derrotado." << endl;
    }
    
    // Calcular puntaje
    int B = ganado ? 100 : 0;
    int puntaje = B + (jugador->oro * 2) + (jugador->PV * 2) + (jugador->PH * 5);
    
    cout << "\n=== PUNTAJE FINAL ===" << endl;
    cout << "Nombre: " << jugador->nombre << endl;
    cout << "Oro: " << jugador->oro << " x2 = " << (jugador->oro * 2) << endl;
    cout << "PV: " << jugador->PV << " x2 = " << (jugador->PV * 2) << endl;
    cout << "PH: " << jugador->PH << " x5 = " << (jugador->PH * 5) << endl;
    cout << "Puntaje base: " << B << endl;
    cout << "PUNTAJE TOTAL: " << puntaje << endl;
    
    // Guardar puntaje
    guardarPuntaje(jugador->nombre, puntaje);
}

void Juego::guardarEstado() {
    guardarPartida(jugador, tablero, enemigos, totalEnemigos);
}

void Juego::cargarEstado() {
    if (cargarPartida(jugador, tablero, enemigos, totalEnemigos)) {
        cout << "Partida cargada. ¡Bienvenido de vuelta!" << endl;
    }
}

void Juego::procesarComando(string comando) {
    if (!juegoActivo) {
        cout << "El juego ha terminado. Usa 'Start' para comenzar una nueva partida." << endl;
        return;
    }

    //  Tablero
    if (comando == "Board" || comando == "board" || comando == "b") {
        mostrarTablero();
    }

    //  Stats
    else if (comando == "Stats" || comando == "stats" || comando == "i") {
        mostrarStats();
    }

    //  Movimiento (WASD)
    else if (comando == "w" || comando == "s" || comando == "a" || comando == "d") {
        if (comando == "w") moverJugador("up");
        else if (comando == "s") moverJugador("down");
        else if (comando == "a") moverJugador("left");
        else moverJugador("right");

        actualizarTurno();
        mostrarTablero();
    }

    //  Movimiento largo (por si acaso)
    else if (comando.rfind("Move ", 0) == 0 || comando.rfind("move ", 0) == 0) {
        string direccion = comando.substr(comando.find(" ") + 1);
        moverJugador(direccion);
        actualizarTurno();
        mostrarTablero();
    }

    //  Cofre
    else if (comando == "Seek" || comando == "seek" || comando == "e") {
        explorar();
        actualizarTurno();
        mostrarTablero();
    }

    //  Ataque
    else if (comando == "Attack" || comando == "attack" || comando == "f") {
        atacar();
        actualizarTurno();
        mostrarTablero();
    }

    //  Guardar
    else if (comando == "Save" || comando == "save") {
        guardarEstado();
    }

    //  Cargar
    else if (comando == "Load" || comando == "load") {
        cargarEstado();
        mostrarTablero(); 
    }

    else {
        cout << "Comando no reconocido" << endl;
    }
}