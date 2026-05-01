#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

map<string, int> variables;

bool esNumero(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        if ((texto[i] < '0' || texto[i] > '9') && texto[i] != '-') {
            return false;
        }
    }
    return true;
}

void aplicarOperacion(string operacion, string var, string operando) {
    int valor;

    if (esNumero(operando)) {
        valor = stoi(operando);
    } else {
        valor = variables[operando];
    }

    if (operacion == "SUM") {
        variables[var] = variables[var] + valor;
    } else if (operacion == "SUB") {
        variables[var] = variables[var] - valor;
    } else if (operacion == "MUL") {
        variables[var] = variables[var] * valor;
    } else if (operacion == "DIV") {
        if (valor != 0) {
            variables[var] = variables[var] / valor;
        }
    }
}

bool evaluarStack(string nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "false" << endl;
        return false;
    }

    int resultadoEsperado = 0;
    string ultimaVar = "";
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        istringstream iss(linea);
        string token;
        iss >> token;

        if (token == "=") {
            iss >> resultadoEsperado;
        } else if (token == "SUM" || token == "SUB" || token == "MUL" || token == "DIV") {
            string var, operando;
            iss >> var >> operando;
            ultimaVar = var;
            aplicarOperacion(token, var, operando);
        } else {
            int valor;
            iss >> valor;
            variables[token] = valor;
            ultimaVar = token;
        }
    }

    archivo.close();

    bool igual = (variables[ultimaVar] == resultadoEsperado);
    cout << (igual ? "true" : "false") << endl;
    return igual;
}

int main() {
    evaluarStack("stack.txt");
    system("pause");
    return 0;
}