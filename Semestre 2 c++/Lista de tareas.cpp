//Crea un sistema el cual simule una lista de tareas, donde cada estado dentro del tablero (pendiente, bloqueado, activo, terminado) debe estar disponible en un archivo .CSV diferente.
//Tarea (id, nombre, fechaInicio, fechaActaulizacion)

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Lista de tareas2.h"

using namespace std;



void obtenerFechaActual(char* fecha) {
    time_t ahora = time(0);
    struct tm* tiempoLocal = localtime(&ahora);
    sprintf(fecha, "%04d-%02d-%02d", tiempoLocal->tm_year + 1900, tiempoLocal->tm_mon + 1, tiempoLocal->tm_mday);
}

int cargarTareas(const char* archivo, TareaPendiente lista[]) {
    ifstream lectura(archivo);
    if (!lectura.is_open()) {
        return 0;
    }
    
    char linea[100];
    int contador = 0;
    
    while (lectura.getline(linea, 100)) {
        char* pedazo = strtok(linea, ",");
        if (pedazo != NULL) lista[contador].codigo = atoi(pedazo);
        
        pedazo = strtok(NULL, ",");
        if (pedazo != NULL) strcpy(lista[contador].descripcion, pedazo);
        
        pedazo = strtok(NULL, ",");
        if (pedazo != NULL) strcpy(lista[contador].fechaInicio, pedazo);
        
        pedazo = strtok(NULL, ",");
        if (pedazo != NULL) strcpy(lista[contador].fechaCambio, pedazo);
        
        contador++;
    }
    
    lectura.close();
    return contador;
}

void guardarTareas(const char* archivo, TareaPendiente lista[], int cantidad) {
    ofstream escritura(archivo);
    
    for (int i = 0; i < cantidad; i++) {
        escritura << lista[i].codigo << "," << lista[i].descripcion << "," << lista[i].fechaInicio << "," << lista[i].fechaCambio << endl;
    }
    
    escritura.close();
}

void mostrarTareas(TareaPendiente lista[], int cantidad, const char* titulo) {
    cout << "\n----------------------------------------\n";
    cout << "   " << titulo << " (" << cantidad << " tareas)" << endl;
    cout << "----------------------------------------\n";
    
    if(cantidad == 0){
        cout << "   No hay tareas aqui" << endl;
    } else {
        for (int i = 0; i < cantidad; i++) {
            cout << " " << i+1 << ". [" << lista[i].codigo << "] " << lista[i].descripcion;
            cout << " | Inicio: " << lista[i].fechaInicio;
            cout << " | Actualizacion: " << lista[i].fechaCambio << endl;
        }
    }
    cout << "----------------------------------------\n";
}

void moverTarea(TareaPendiente tarea, const char* origen, const char* destino, bool actualizarFecha) {
    TareaPendiente tareasOrigen[100];
    int cantidadOrigen = cargarTareas(origen, tareasOrigen);
    
    TareaPendiente tareasDestino[100];
    int cantidadDestino = cargarTareas(destino, tareasDestino);
    
    int posEliminar = -1;
    for (int i = 0; i < cantidadOrigen; i++) {
        if (tareasOrigen[i].codigo == tarea.codigo) {
            posEliminar = i;
            break;
        }
    }
    
    if (posEliminar != -1) {
        if (actualizarFecha) {
            obtenerFechaActual(tarea.fechaCambio);
        }
        
        tareasDestino[cantidadDestino] = tarea;
        cantidadDestino++;
        
        for (int i = posEliminar; i < cantidadOrigen - 1; i++) {
            tareasOrigen[i] = tareasOrigen[i + 1];
        }
        cantidadOrigen--;
        
        guardarTareas(origen, tareasOrigen, cantidadOrigen);
        guardarTareas(destino, tareasDestino, cantidadDestino);
        
        cout << "\n>>> Tarea movida a " << destino << " <<<\n";
    }
}

void revisarDependencias(int codigoCompletado) {
    TareaPendiente tareasTrabadas[100];
    int cantidadTrabadas = cargarTareas("trabado.csv", tareasTrabadas);
    TareaPendiente tareasPorHacer[100];
    int cantidadPorHacer = cargarTareas("porhacer.csv", tareasPorHacer);
    
    bool huboCambios = false;
    
    for (int i = 0; i < cantidadTrabadas; i++) {
        if (tareasTrabadas[i].codigo == codigoCompletado + 100) { 
            tareasPorHacer[cantidadPorHacer] = tareasTrabadas[i];
            cantidadPorHacer++;
            
            int tempCodigo = tareasTrabadas[i].codigo; 
            
            for (int j = i; j < cantidadTrabadas - 1; j++) {
                tareasTrabadas[j] = tareasTrabadas[j + 1];
            }
            cantidadTrabadas--;
            i--;
            huboCambios = true;
            
            cout << "\n>>> La tarea " << tempCodigo << " ya se puede hacer <<<\n";
        }
    }
    
    if (huboCambios) {
        guardarTareas("trabado.csv", tareasTrabadas, cantidadTrabadas);
        guardarTareas("porhacer.csv", tareasPorHacer, cantidadPorHacer);
    }
}

void crearArchivosIniciales() {
    TareaPendiente pendientes[] = {
        {101, "matematicas", "2024-01-10", "2024-01-10"},
        {102, "castellano", "2024-01-10", "2024-01-10"},
        {103, "fisica", "2024-01-10", "2024-01-10"}
    };
    guardarTareas("porhacer.csv", pendientes, 3);
    
    TareaPendiente vacio[1] = {0};
    guardarTareas("activo.csv", vacio, 0);
    
    TareaPendiente trabados[] = {
        {201, "biologia", "2024-01-10", "2024-01-10"},
        {202, "sociales", "2024-01-10", "2024-01-10"}
    };
    guardarTareas("trabado.csv", trabados, 2);
    
    guardarTareas("terminado.csv", vacio, 0);
    
    cout << "\n Archivos creados\n";
}

int main(int argc, char* argumentos[]) {
    srand(time(0));
    
    if (argc > 1) {
        if (strcmp(argumentos[1], "crear") == 0 && argc >= 5) {
            TareaPendiente nueva;
            nueva.codigo = rand() % 1000 + 100;
            strcpy(nueva.descripcion, argumentos[2]);
            strcpy(nueva.fechaInicio, argumentos[3]);
            strcpy(nueva.fechaCambio, argumentos[4]);
            
            TareaPendiente pendientes[100];
            int cuantas = cargarTareas("porhacer.csv", pendientes);
            pendientes[cuantas] = nueva;
            guardarTareas("porhacer.csv", pendientes, cuantas + 1);
            
            cout << "\n>>> Tarea creada con ID: " << nueva.codigo << " <<<\n";
            return 0;
        }
        else if (strcmp(argumentos[1], "mover") == 0 && argc == 4) {
            int codigo = atoi(argumentos[2]);
            const char* aDonde = argumentos[3];
            
            char archivoDestino[30];
            strcpy(archivoDestino, aDonde);
            strcat(archivoDestino, ".csv");
            
            const char* origenes[] = {"porhacer.csv", "activo.csv", "trabado.csv"};
            TareaPendiente encontrada;
            bool existe = false;
            
            for (int i = 0; i < 3; i++) {
                TareaPendiente tareas[100];
                int cuantas = cargarTareas(origenes[i], tareas);
                
                for (int j = 0; j < cuantas; j++) {
                    if (tareas[j].codigo == codigo) {
                        encontrada = tareas[j];
                        moverTarea(encontrada, origenes[i], archivoDestino, true);
                        existe = true;
                        break;
                    }
                }
                if (existe) break;
            }
            
            if (!existe) {
                cout << "\nNo se encontro esa tarea men\n";
            }
            return 0;
        }
    }
    
    crearArchivosIniciales();
    
    int opcion;
    do {
        TareaPendiente porHacer[100], enProgreso[100], trabados[100], finalizados[100];
        int cuantosPorHacer = cargarTareas("porhacer.csv", porHacer);
        int cuantosActivos = cargarTareas("activo.csv", enProgreso);
        int cuantosTrabados = cargarTareas("trabado.csv", trabados);
        int cuantosTerminados = cargarTareas("terminado.csv", finalizados);
        
        cout << "\n========================================\n";
        cout << "            MENU PRINCIPAL" << endl;
        cout << "========================================\n";
        cout << " 1. Ver todo" << endl;
        cout << " 2. Empezar tarea (por hacer -> activo)" << endl;
        cout << " 3. Terminar tarea (activo -> terminado)" << endl;
        cout << " 4. Bloquear tarea (por hacer -> trabado)" << endl;
        cout << " 5. Desbloquear tarea (trabado -> por hacer)" << endl;
        cout << " 6. Agregar tarea nueva" << endl;
        cout << " 7. Mover tarea manual" << endl;
        cout << " 0. Salir" << endl;
        cout << "========================================\n";
        cout << "Elige una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch(opcion) {
            case 1:
                cout << "\n";
                mostrarTareas(porHacer, cuantosPorHacer, "POR HACER");
                mostrarTareas(enProgreso, cuantosActivos, "EN PROGRESO");
                mostrarTareas(trabados, cuantosTrabados, "TRABADOS");
                mostrarTareas(finalizados, cuantosTerminados, "TERMINADOS");
                break;
                
            case 2: {
                if (cuantosPorHacer == 0) {
                    cout << "\nNo hay tareas pendientes pa\n";
                    break;
                }
                mostrarTareas(porHacer, cuantosPorHacer, "POR HACER");
                cout << "Cual vas a empezar?: ";
                int cual;
                cin >> cual;
                cin.ignore();
                
                if (cual >= 1 && cual <= cuantosPorHacer) {
                    moverTarea(porHacer[cual-1], "porhacer.csv", "activo.csv", true);
                } else {
                    cout << "\nEse numero no es valido\n";
                }
                break;
            }
            
            case 3: {
                if (cuantosActivos == 0) {
                    cout << "\nNo hay tareas activas\n";
                    break;
                }
                mostrarTareas(enProgreso, cuantosActivos, "EN PROGRESO");
                cout << "Cual terminaste?: ";
                int cual;
                cin >> cual;
                cin.ignore();
                
                if (cual >= 1 && cual <= cuantosActivos) {
                    int codigoTemp = enProgreso[cual-1].codigo;
                    moverTarea(enProgreso[cual-1], "activo.csv", "terminado.csv", true);
                    revisarDependencias(codigoTemp);
                } else {
                    cout << "\nEse numero no es valido\n";
                }
                break;
            }
            
            case 4: {
                if (cuantosPorHacer == 0) {
                    cout << "\nNo hay tareas pendientes\n";
                    break;
                }
                mostrarTareas(porHacer, cuantosPorHacer, "POR HACER");
                cout << "Cual vas a bloquear?: ";
                int cual;
                cin >> cual;
                cin.ignore();
                
                if (cual >= 1 && cual <= cuantosPorHacer) {
                    moverTarea(porHacer[cual-1], "porhacer.csv", "trabado.csv", false);
                } else {
                    cout << "\nEse numero no es valido\n";
                }
                break;
            }
            
            case 5: {
                if (cuantosTrabados == 0) {
                    cout << "\nNo hay tareas bloqueadas\n";
                    break;
                }
                mostrarTareas(trabados, cuantosTrabados, "TRABADOS");
                cout << "Cual vas a desbloquear?: ";
                int cual;
                cin >> cual;
                cin.ignore();
                
                if (cual >= 1 && cual <= cuantosTrabados) {
                    moverTarea(trabados[cual-1], "trabado.csv", "porhacer.csv", false);
                } else {
                    cout << "\nEse numero no es valido\n";
                }
                break;
            }
            
            case 6: {
                TareaPendiente nueva;
                cout << "\nID de la tarea: ";
                cin >> nueva.codigo;
                cin.ignore();
                cout << "Nombre: ";
                cin.getline(nueva.descripcion, 50);
                cout << "Fecha inicio (YYYY-MM-DD): ";
                cin.getline(nueva.fechaInicio, 11);
                strcpy(nueva.fechaCambio, nueva.fechaInicio);
                
                TareaPendiente pendientes[100];
                int cuantas = cargarTareas("porhacer.csv", pendientes);
                pendientes[cuantas] = nueva;
                guardarTareas("porhacer.csv", pendientes, cuantas + 1);
                cout << "\n>>> Tarea agregada! <<<\n";
                break;
            }
            
            case 7: {
                cout << "\nID de la tarea: ";
                int codigo;
                cin >> codigo;
                cin.ignore();
                
                cout << "Mover a (porhacer/activo/trabado/terminado): ";
                char destino[20];
                cin.getline(destino, 20);
                
                char archivoDestino[30];
                strcpy(archivoDestino, destino);
                strcat(archivoDestino, ".csv");
                
                const char* origenes[] = {"porhacer.csv", "activo.csv", "trabado.csv", "terminado.csv"};
                TareaPendiente encontrada;
                bool existe = false;
                
                for (int i = 0; i < 4; i++) {
                    TareaPendiente tareas[100];
                    int cuantas = cargarTareas(origenes[i], tareas);
                    
                    for (int j = 0; j < cuantas; j++) {
                        if (tareas[j].codigo == codigo) {
                            encontrada = tareas[j];
                            moverTarea(encontrada, origenes[i], archivoDestino, true);
                            existe = true;
                            break;
                        }
                    }
                    if (existe) break;
                }
                
                if (!existe) {
                    cout << "\nNo se encontro esa tarea\n";
                }
                break;
            }
            
            case 0:
                cout << "\nvemos\n";
                break;
                
            default:
                cout << "\nEsa opcion no existe\n";
        }
        
    } while (opcion != 0);
    
    return 0;
}