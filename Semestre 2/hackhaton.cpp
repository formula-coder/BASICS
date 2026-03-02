#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

// Estructura para guardar las estadísticas de cada IP
struct Stats {
    int total = 0;
    int ok = 0;
};

// Función auxiliar para separar un string por un delimitador
vector<string> separarPorComa(const string& linea) {
    vector<string> resultado;
    string campo = "";
    
    for (char c : linea) {
        if (c == ',') {
            resultado.push_back(campo);
            campo = "";
        } else {
            campo += c;
        }
    }
    resultado.push_back(campo);  // Agregar el último campo
    
    return resultado;
}

// Función principal solicitada en el problema
vector<string> obtenerErrores(const string& nombre_archivo, double porcentaje_minimo) {
    vector<string> ips_a_revisar;
    ifstream archivo(nombre_archivo);

    // 1. Manejar el caso donde el archivo no existe
    if (!archivo.is_open()) {
        return ips_a_revisar; // Retorna un vector vacío []
    }

    map<string, Stats> stats_ips;
    string linea;

    // 2 y 3. Leer y procesar el archivo (si está vacío, el ciclo no se ejecuta)
    while (getline(archivo, linea)) {
        // Ignorar líneas vacías
        if (linea.empty()) continue;

        vector<string> campos = separarPorComa(linea);
        
        // Necesitamos al menos 3 campos: IP, método, estado
        if (campos.size() >= 3) {
            string ip = campos[0];
            string metodo = campos[1];
            string estado = campos[2];
            
            // Limpiar posible salto de línea de Windows (\r) al final del estado
            if (!estado.empty() && estado.back() == '\r') {
                estado.pop_back();
            }

            // Registrar la transacción
            stats_ips[ip].total++;
            if (estado == "OK") {
                stats_ips[ip].ok++;
            }
        }
    }

    archivo.close();

    // 4. Calcular los porcentajes y filtrar las IPs
    for (const auto& par : stats_ips) {
        const string& ip = par.first;
        int total = par.second.total;
        int ok = par.second.ok;

        // Calcular el porcentaje de éxito asegurando que la división sea con decimales
        double porcentaje_exito = (static_cast<double>(ok) / total) * 100.0;

        // Si el porcentaje es menor al mínimo, agregar a la lista
        if (porcentaje_exito < porcentaje_minimo) {
            ips_a_revisar.push_back(ip);
        }
    }

    return ips_a_revisar;
}

// =========================================================================
// Código auxiliar para probar los casos del enunciado
// =========================================================================

// Función para imprimir los resultados
void imprimirResultado(int caso, const vector<string>& resultado) {
    cout << "Caso " << caso << " - Resultado: [";
    for (size_t i = 0; i < resultado.size(); ++i) {
        cout << "\"" << resultado[i] << "\"";
        if (i < resultado.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

// Función para crear archivos de prueba rápidamente
void crearArchivo(const string& nombre, const string& contenido) {
    ofstream archivo(nombre);
    archivo << contenido;
    archivo.close();
}

int main() {
    // Caso 1: Archivo no existe (Porcentaje mínimo: 80)
    vector<string> res1 = obtenerErrores("no_existe.csv", 80.0);
    imprimirResultado(1, res1);

    // Caso 2: Archivo vacío (Porcentaje mínimo: 80)
    crearArchivo("vacio.csv", "");
    vector<string> res2 = obtenerErrores("vacio.csv", 80.0);
    imprimirResultado(2, res2);

    // Caso 3: Sin errores a reportar (Porcentaje mínimo: 70)
    crearArchivo("caso3.csv", 
        "192.168.1.1,GET,OK\n"
        "192.168.1.1,POST,OK\n"
        "192.168.1.2,GET,OK\n"
        "192.168.1.2,POST,OK\n");
    vector<string> res3 = obtenerErrores("caso3.csv", 70.0);
    imprimirResultado(3, res3);

    // Caso 4: Errores detectados (Porcentaje mínimo: 50)
    crearArchivo("caso4.csv", 
        "192.168.1.1,GET,OK\n"
        "192.168.1.1,POST,FAIL\n"
        "192.168.1.1,PUT,FAIL\n" // 33.3% éxito -> Falla
        "192.168.1.2,GET,OK\n"
        "192.168.1.2,POST,OK\n"   // 100% éxito -> Pasa
        "192.168.1.3,GET,FAIL\n"
        "192.168.1.3,POST,FAIL\n");// 0% éxito -> Falla
    vector<string> res4 = obtenerErrores("caso4.csv", 50.0);
    imprimirResultado(4, res4);

    return 0;
}