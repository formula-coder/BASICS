#include <iostream>

using namespace std;

int* buscarValor(int* inicio, int* fin, int valorBuscado) {
    for (int* p = inicio; p < fin; p++) {
        if (*p == valorBuscado) {
            return p;
        }
    }
    return nullptr;
}


