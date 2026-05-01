#include <iostream>
#include <fstream>
#include <string.h> 
#include <cstdlib>

using namespace std;

// 1. (5 PUNTOS) ESTRUCTURAS
struct Libro {
    int id;
    char titulo[100];
    int precio;
    int inventario;
};

struct Linea {
    int id_libro;
    char titulo[100];
    int cantidad;
    float subtotal;
};

struct Compra {
    char cliente[100];
    int id_cliente;
    Linea* lineas;
    int num_lineas;
    float total;
};

struct Libreria {
    Libro* catalogo; 
    int num_libros;
    Compra* compras;
    int num_compras;
};

// 2. (10 PUNTOS) CARGAR CATALOGO
void inicializarCatalogo(Libreria* lib) {
    ifstream txt("libros.txt");
    if (!txt.is_open()) {
        cout << "Error: No se encontro el archivo libros.txt." << endl;
        return;
    }

    txt >> lib->num_libros;
    txt.ignore(); 

   
    lib->catalogo = new Libro[lib->num_libros];
    Libro* pLib = lib->catalogo;

    for (int i = 0; i < lib->num_libros; i++) {
       
        txt.getline((pLib + i)->titulo, 100);
        
        char buffer[100];
        txt.getline(buffer, 100);
        
       
        char* token = strtok(buffer, ",");
        (pLib + i)->id = atoi(token);
        
        token = strtok(NULL, ",");
        (pLib + i)->precio = atoi(token);
        
        token = strtok(NULL, ",");
        (pLib + i)->inventario = atoi(token);
        
        char hash[10];
        txt.getline(hash, 10); 
    }
    txt.close();

    ofstream dat("libros.dat", ios::binary);
    if (dat.is_open()) {
        dat.write((char*)&lib->num_libros, sizeof(int));
        for (int i = 0; i < lib->num_libros; i++) {
            dat.write((char*)(pLib + i), sizeof(Libro));
        }
        dat.close();
        cout << "Catalogo cargado en memoria y libros.dat generado con exito." << endl;
    }
}

// 3. (10 PUNTOS)
Libro* buscarLibro(Libreria* lib, const char* titulo) {
    Libro* pLib = lib->catalogo;
    for (int i = 0; i < lib->num_libros; i++) {
        if (strcmp((pLib + i)->titulo, titulo) == 0) {
            return (pLib + i); 
        }
    }
    return NULL; 
}

// 4. (25 PUNTOS)
void agregarLinea(Libreria* lib, Compra* comp, const char* titulo, int cantidad) {
    Libro* libroEncontrado = buscarLibro(lib, titulo);
    
    if (libroEncontrado != NULL) {
        if (libroEncontrado->inventario >= cantidad) {
            Linea* nuevasLineas = new Linea[comp->num_lineas + 1];
            Linea* pNuevas = nuevasLineas;
            Linea* pViejas = comp->lineas;

            for (int i = 0; i < comp->num_lineas; i++) {
                *(pNuevas + i) = *(pViejas + i);
            }

            Linea* nuevaLinea = (pNuevas + comp->num_lineas);
            nuevaLinea->id_libro = libroEncontrado->id;
            
            strcpy(nuevaLinea->titulo, libroEncontrado->titulo);
            
            nuevaLinea->cantidad = cantidad;
            nuevaLinea->subtotal = (float)(cantidad * libroEncontrado->precio); 

            libroEncontrado->inventario -= cantidad;

            if (comp->lineas != NULL) {
                delete[] comp->lineas;
            }
            
            comp->lineas = nuevasLineas;
            comp->num_lineas++;
            
            cout << "-> Linea agregada exitosamente." << endl;
        } else {
            cout << "-> Error: Cantidad disponible insuficiente." << endl; 
        }
    } else {
        cout << "-> Error: El libro '" << titulo << "' no existe en el catalogo." << endl; 
    }
}

// 5. (10 PUNTOS)
void calcularTotal(Compra& comp) {
    float suma = 0.0f;
    Linea* pLineas = comp.lineas;
    for (int i = 0; i < comp.num_lineas; i++) {
        // Desplazamiento del apuntador y uso de operador flecha
        suma += (pLineas + i)->subtotal; 
    }
    comp.total = suma * 1.19f; 
}

// 6. (10 PUNTOS) 
void generarRecibo(Compra* comp) {
    ofstream txt("compraCliente.txt"); 
    if (!txt.is_open()) return;

    txt << "Cliente de la compra: " << comp->cliente << endl;
    txt << "ID del cliente: " << comp->id_cliente << endl << endl;
    txt << "Lineas de compra (libros vendidos)" << endl;
    txt << "Titulo\t\t\t\tCantidad\tPrecio\t\tSubtotal" << endl;

    Linea* pLineas = comp->lineas;
    for (int i = 0; i < comp->num_lineas; i++) {
        int precioUnitario = (pLineas + i)->subtotal / (pLineas + i)->cantidad;
        txt << (pLineas + i)->titulo << "\t\t"
            << (pLineas + i)->cantidad << "\t\t"
            << "$" << precioUnitario << "\t\t"
            << "$" << (pLineas + i)->subtotal << endl;
    }
    
    txt << endl << "Valor total (con IVA): $" << comp->total << endl;
    txt.close();
    cout << "-> Recibo 'compraCliente.txt' generado con exito." << endl;
}

// 7. (10 PUNTOS) 
void guardarCompraBinario(Compra* comp) {
    ofstream dat("compras.dat", ios::binary | ios::app);
    if (!dat.is_open()) return;

    dat.write(comp->cliente, sizeof(char) * 100);
    dat.write((char*)&comp->id_cliente, sizeof(int));
    dat.write((char*)&comp->num_lineas, sizeof(int));

    Linea* pLineas = comp->lineas;
    for (int i = 0; i < comp->num_lineas; i++) {
        dat.write((char*)(pLineas + i), sizeof(Linea));
    }

    dat.write((char*)&comp->total, sizeof(float));
    dat.close();
    cout << "-> Compra respaldada en 'compras.dat'." << endl;
}

// MENU PRINCIPAL
int main() {
    Libreria miLibreria;
    miLibreria.catalogo = NULL;
    miLibreria.num_libros = 0;
    miLibreria.compras = NULL;
    miLibreria.num_compras = 0;

    Compra compraActual;
    compraActual.lineas = NULL;
    compraActual.num_lineas = 0;
    compraActual.total = 0.0f;

    int opcion;
    do {
        cout << endl << "=== SISTEMA DE LIBRERIA (PARCIAL 1) ===" << endl;
        cout << "1. Cargar catalogo desde libros.txt" << endl;
        cout << "2. Iniciar nueva compra" << endl;
        cout << "3. Buscar libro" << endl;
        cout << "4. Agregar libro a compra" << endl;
        cout << "5. Finalizar compra" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                inicializarCatalogo(&miLibreria);
                break;
            case 2:
                if (compraActual.lineas != NULL) {
                    delete[] compraActual.lineas;
                }
                compraActual.lineas = NULL;
                compraActual.num_lineas = 0;
                compraActual.total = 0.0f;

                cout << "Ingrese nombre del cliente: ";
                cin.getline(compraActual.cliente, 100);
                cout << "Ingrese ID del cliente: ";
                cin >> compraActual.id_cliente;
                cin.ignore();
                cout << "-> Compra iniciada." << endl;
                break;
            case 3: {
                char tituloBusqueda[100];
                cout << "Ingrese el titulo del libro: ";
                cin.getline(tituloBusqueda, 100);
                Libro* ptrLibro = buscarLibro(&miLibreria, tituloBusqueda);
                if (ptrLibro) {
                    cout << "-> Libro encontrado. Precio: $" << ptrLibro->precio 
                         << " | Inventario: " << ptrLibro->inventario << endl;
                } else {
                    cout << "-> Libro no encontrado." << endl;
                }
                break;
            }
            case 4: {
                char tituloAgregar[100];
                int cant;
                cout << "Titulo del libro a comprar: ";
                cin.getline(tituloAgregar, 100);
                cout << "Cantidad: ";
                cin >> cant;
                cin.ignore();
                agregarLinea(&miLibreria, &compraActual, tituloAgregar, cant);
                break;
            }
            case 5:
                if (compraActual.num_lineas > 0) {
                    calcularTotal(compraActual);
                    cout << "-> Total de la compra (con IVA): $" << compraActual.total <<endl;
                    generarRecibo(&compraActual);
                    guardarCompraBinario(&compraActual);
                } else {
                    cout << "-> No hay lineas en la compra."<<endl;
                }
                break;
            case 6:
                cout << "Saliendo..."<<endl;
                break;
            default:
                cout << "Opcion invalida."<<endl;
        }
    } while (opcion != 6);

   
    if (miLibreria.catalogo != NULL) delete[] miLibreria.catalogo;
    if (compraActual.lineas != NULL) delete[] compraActual.lineas;

    return 0;
}