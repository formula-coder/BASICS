#ifndef LISTA_DE_TAREAS_H
#define LISTA_DE_TAREAS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct TareaPendiente {
    int codigo;
    char descripcion[50];
    char fechaInicio[11];
    char fechaCambio[11];
};

// SOLO PROTOTIPOS (sin implementación)
void obtenerFechaActual(char* fecha);
int cargarTareas(const char* archivo, TareaPendiente lista[]);
void guardarTareas(const char* archivo, TareaPendiente lista[], int cantidad);
void mostrarTareas(TareaPendiente lista[], int cantidad, const char* titulo);
void moverTarea(TareaPendiente tarea, const char* origen, const char* destino, bool actualizarFecha);
void revisarDependencias(int codigoCompletado);
void crearArchivosIniciales();

#endif

