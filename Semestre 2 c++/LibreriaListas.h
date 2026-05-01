#ifndef LIBRERIA_LISTAS_H
#define LIBRERIA_LISTAS_H

#include <iostream>

template <typename T>
class ListaDinamica {
private:
    T* datos;
    int capacidad;
    int cantidad;

    void redimensionar() {
        capacidad *= 2;
        T* nuevoArreglo = new T[capacidad];
        for (int i = 0; i < cantidad; i++) {
            nuevoArreglo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevoArreglo;
    }

public:
    ListaDinamica(int capInicial = 2) : capacidad(capInicial), cantidad(0) {
        datos = new T[capacidad];
    }

    void agregar(T valor) {
        if (cantidad == capacidad) redimensionar();
        datos[cantidad++] = valor;
    }

    void mostrar() {
        if (cantidad == 0) {
            std::cout << "La lista dinamica esta vacia." << std::endl;
            return;
        }
        for (int i = 0; i < cantidad; i++) {
            std::cout << "[" << datos[i] << "] ";
        }
        std::cout << std::endl;
    }

    ~ListaDinamica() {
        delete[] datos;
    }
};

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
};

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    void insertar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>();
        nuevo->dato = valor;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    void imprimir() {
        if (cabeza == nullptr) {
            std::cout << "La lista enlazada esta vacia." << std::endl;
            return;
        }
        Nodo<T>* temp = cabeza;
        while (temp != nullptr) {
            std::cout << temp->dato << " -> ";
            temp = temp->siguiente;
        }
        std::cout << "NULL" << std::endl;
    }

    ~ListaEnlazada() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

#endif
