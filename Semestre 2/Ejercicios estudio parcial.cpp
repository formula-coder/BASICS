#include <iostream>
#include <stdio.h>

using namespace std;    

// Clase Libro con constructor adecuado
class Libro {
public:
    string titulo;
    string autor;

    // Constructor que acepta dos cadenas
    Libro(string t, string a) {
     this ->titulo = t;
     this ->autor = a;
    }
};

// Función para mostrar libros
void mostrarLibros() {
    Libro libros[3];

    // Inicializamos los libros con el constructor
    libros[0] = Libro("El principito", "Antoine de Saint-Exupéry");
    libros[1] = Libro("Cien años de soledad", "Gabriel García Márquez");
    libros[2] = Libro("Don Quijote de la Mancha", "Miguel de Cervantes");

    cout << "Libros disponibles en la biblioteca:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Titulo: " << libros[i].titulo << ", Autor: " << libros[i].autor << endl;
    }
}

int main(){ 
    do{
    int opcion;
    cout<<"Bienvenido a la biblioteca de C++"<<endl;
    cout<<"menu de opciones"<<endl;
    cout<<"1.Desea prestar un libro"<<endl;
    cout<<"2.Desea devolver un libro"<<endl;
    cout<<"3.Desea consultar un libro"<<endl;
    cout<<"4.Desea salir"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opcion;

    switch(opcion){
        case 1:
            cout<<"Ha seleccionado prestar un libro"<<endl;
            prestarlibro();
            break;
        case 2:
            cout<<"Ha seleccionado devolver un libro"<<endl;
            devolverlibro();
            break;
        case 3:
            cout<<"Ha seleccionado consultar un libro"<<endl;
            mostrarLibros();
            break;
        case 4:
            cout<<"Ha seleccionado salir"<<endl;
            break;
        }
    return 0;
    }while(true);
    }

int prestarlibro(){
    ofstream archivobin("archivobin.bin", ios::binary);
    if (!archivobin.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    else{
        cout<<"Ingrese el titulo del libro que desea prestar: ";
        string titulo;
        cin>>titulo;
        cout<<"Ingrese el autor del libro que desea prestar: ";
        string autor;
        cin>>autor;
        cout << "Libro prestado: " << titulo << " por " << autor << endl;
        cout << "Guardando información del libro prestado en el archivo binario..." << endl;
        cout << "Información guardada correctamente." << endl;
        Libro libroprestado(titulo, autor);
        archivobin.write((char*)&libroprestado, sizeof(libroprestado));
        archivobin.close();
    }
}

int devolverlibro(){
    ifstream archivobin("archivobin.bin", ios::binary);
    if (!archivobin.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    else{
        Libro librodevuelto;
        archivobin.read((char*)&librodevuelto, sizeof(librodevuelto));
        cout<<"ingrese el libro a devolver: ";
        string titulo, autor;
        cin>>titulo>>autor;
        if(librodevuelto.titulo == titulo && librodevuelto.autor == autor){
            cout << "Libro devuelto correctamente." << endl;
        }
        else{
            cout << "El libro que intenta devolver no coincide con el libro prestado." << endl;
        }
        cout << "Libro devuelto: " << librodevuelto.titulo << " por " << librodevuelto.autor << endl;
        archivobin.close();
    }
}

