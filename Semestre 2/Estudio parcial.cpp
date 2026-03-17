//cantidad de bytes por tipo de dato
//char: 1 byte
//short: 2 bytes
//int: 4 bytes
//long: 4 bytes
//long long: 8 bytes
//float: 4 bytes
//double: 8 bytes
//bool: 1 byte


//structuras de datos primera forma 
#include <iostream>
#include <string>
using namespace std;
struct Persona{
    string nombre;
    int edad;
    Persona(string nombre, int edad){
        this->nombre = nombre;
        this->edad = edad;
    }
}

//segunda forma de estructuras de datos
#include <iostream> 
#include <string>
using namespace std;

struct Persona{
    string nombre;
    int edad;
    
};  

int main(){
    Persona p1;
    p1.nombre = "Juan";
    p1.edad = 30;
    
    cout << "Nombre: " << p1.nombre << endl;
    cout << "Edad: " << p1.edad << endl;
    
    return 0;
}


//archivos binarios (Estilo C++ moderno)
#include <iostream>
#include <fstream> // Librería de C++ para lectura y escritura de archivos

using namespace std; 

int main(){
    // ofstream es la clase para ESCRITURA (Output File Stream)
    // ios::binary indica que no le de formato de texto, sino que lo guarde en bytes crudos
    ofstream archivobin("archivobin.bin", ios::binary);
    
    // is_open() comprueba si el archivo se abrió correctamente
    if (!archivobin.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    else{
        cout << "Archivo abierto correctamente" << endl;
        cout << "Escribiendo en el archivo..." << endl;
        
        int numero = 12345;
        
        // El método .write() recibe 2 parámetros:
        // 1. Un puntero tipo caracter: (char*)&numero
        // 2. El tamaño en bytes que vas a escribir: sizeof(int)
        archivobin.write((char*)&numero, sizeof(int));
        
        cout << "Numero escrito en el archivo: " << numero << endl;
    }

    // Cerramos el archivo con un simple método
    archivobin.close();
    return 0;
}
