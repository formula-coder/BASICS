#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string nombreArchivo = "tripulantes.dat";

struct Tripulante {
    char codigo[11];
    float radiacion;
};

void imprimirTripulantes(const vector<string>& codigos) {
    cout << "Tripulantes aislados: [";

    int totalCodigos = codigos.size();

    for (int indice = 0; indice < totalCodigos; indice = indice + 1) {
        if (indice > 0) {
            cout << ", ";
        }
        cout << '"' << codigos[indice] << '"';
    }

    cout << "]\n";
}

int tripulantesAislamiento(float umbral, vector<string>& tripulantesAislados) {
    ifstream archivo(nombreArchivo.c_str(), ios::binary);
    if (!archivo.is_open()) {
        return -1;
    }

    archivo.seekg(0, ios::end);
    if (archivo.tellg() <= 0) {
        return -1;
    }
    archivo.seekg(0, ios::beg);

    tripulantesAislados.clear();

    Tripulante tripulante;

    while (archivo.read((char*)&tripulante, sizeof(Tripulante))) {
        if (tripulante.radiacion > umbral) {
            tripulantesAislados.push_back(tripulante.codigo);
        }
    }

    return tripulantesAislados.size();
}

int main() {
    float umbralPrueba = 50.0;
    vector<string> tripulantesAislados;

    int cantidadAislados = tripulantesAislamiento(umbralPrueba, tripulantesAislados);

    cout << "Resultado: " << cantidadAislados << '\n';

    if (cantidadAislados >= 0) {
        imprimirTripulantes(tripulantesAislados);
    } else {
        cout << "No se pudo leer el archivo de tripulantes.\n";
    }

    return 0;
}