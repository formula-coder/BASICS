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

#include<iostream>
#include<string>
#include<vector>

using namespace std;
struct Persona{
    string name;
    int age;
};
int main(){
    vector<Persona*> personas;
cout <<"cuantas personas desea ingresar: ";
int n;
cin>>n;
for(int i=0; i<n; i++){
Persona *p1 = new Persona; // Creamos un puntero a Persona y lo inicializamos con un nuevo objeto Persona en el heap
cout<<"Ingrese su nombre: ";
getline(cin, p1->name); // Usamos el operador -> para acceder al miembro name a través del puntero p1
cout<<"Ingrese su edad: ";
cin>>p1->age; // Usamos el operador -> para acceder al miembro age a través del puntero p1
personas.push_back(p1); // Agregamos el objeto a la vector
}
for(int i=0; i<n; i++){
   cout<<"persona:"<<personas[i]->name<<" "<<personas[i]->age<<endl; // Imprimimos el nombre y la edad de cada persona ingresada
}
    string nombre;
    string *pnombre = &nombre; // Declaramos un puntero a string y lo inicializamos con la dirección de nombre
    int edad;
    int *pedad = &edad; // Declaramos un puntero a int y lo
    int* array = new int[5]; // Declaramos un puntero a int y lo inicializamos con un arreglo dinámico de 5 enteros
    cout<<"ingrese valores para el arreglo: ";
    for(int i=0; i<5; i++){
        cin>>array[i];
    }
    for(int i=0; i<5; i++){
        cout<<"Valor "<<i+1<<": "<<array[i]<<endl;
    }
    cout<<"Ingrese su edad: ";
    cin>>edad;
    cout<<"Su edad es: " << *pedad << endl;
    cout<<"Ingrese su nombre: ";
    getline(cin, nombre);
    cout<<"Su nombre es: " << *pnombre << endl;
}
//templates

#include <iostream>
using namespace std;

template <typename int>

int sumar(int a, int b){
    return a + b;
}

int main(){
    cout<<add(5, 10)<<endl; // Llamamos a la función sumar con dos enteros
    cout<<add(3.5, 2.5)<<endl; // Llamamos a la función sumar con dos números de punto flotante
    return 0;
}

#include <iostream>
using namespace std;
 
template <class T, class U>

struct Valores{
    Valores <int, double> v1{5,3.0};
    Valores<double, int>{5.5, 3};
    return 0; 
}

