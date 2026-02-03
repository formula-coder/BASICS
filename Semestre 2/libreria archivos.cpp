#include<iostream>// Librería para entrada y salida estándar
#include<fstream> // Librería para manejo de archivos
#include<string> // Librería para manejo de cadenas de texto

using namespace std;
struct libro{
    int id;
    char titulo[50];
    int stock;
};

void crearArchivo();
void mostrarlibros();
void modificarstock(int id_libro, int cantidad);

int main(){
int opcion;
int id_libro;
// Crear el archivo de datos si no existe
crearArchivo();
do{
cout<<"Menu Principal"<<endl;
cout<<"=====Biblioteca====="<<endl;
cout<<"mostrar libros (1)"<<endl;
cout<<"Prestar libros (2)"<<endl;
cout<<"Devolver libros (3)"<<endl;
cout<<"Salir (4)"<<endl;
cout<<"Ingrese una opcion: ";
cin>>opcion;

switch(opcion){
    case 1:{
        cout<<"Mostrando libros disponibles..."<<endl;
        mostrarlibros();
        break;
    }
    case 2:{
        cout<<"Ingrese el ID del libro a prestar: ";
        cin>>id_libro;
        modificarstock(id_libro, -1);
        break;
    }
    case 3:{
        cout<<"Ingrese el ID del libro a devolver: ";
        cin>>id_libro;
        modificarstock(id_libro, +1);
        break;
    }
    case 4:{
        cout<<"Saliendo del programa..."<<endl;
        break;
    }
    default:{
        cout<<"Opcion invalida. Por favor intente de nuevo."<<endl;
        break;
}
} 
}while (opcion != 4);
}

void crearArchivo(){
    ifstream archivo_in("biblioteca.dat", ios::binary);
    if (archivo_in.good()) {
        archivo_in.close();
        return;
    }
    archivo_in.close();
    ofstream archivo_out("biblioteca.dat", ios::binary);
    libro libros[7] = {
        {1, "Cien Años de Soledad", 5},
        {2, "Don Quijote de la Mancha", 3},
        {3, "La Sombra del Viento", 4},
        {4, "El Amor en los Tiempos del Cólera", 2},
        {5, "1984", 6},
        {6, "Crimen y Castigo", 4},
        {7, "El Gran Gatsby", 5},
    };
    archivo_out.write(reinterpret_cast<char*>(libros), sizeof(libros));
    archivo_out.close();
}

void mostrarlibros(){
    ifstream archivo("biblioteca.dat", ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo de biblioteca." << endl;
        return;
    }

    libro libro;
    cout << "Libros disponibles en la biblioteca:" << endl;
    while(archivo.read(reinterpret_cast<char*>(&libro), sizeof(libro))) {
        cout << "ID: " << libro.id << ", Titulo: " << libro.titulo << ", Stock: " << libro.stock << endl;
    }
    archivo.close();
}

void modificarstock(int id_libro, int cantidad) {
 fstream archivo("biblioteca.dat", ios::in | ios::out | ios::binary);
 if (!archivo) {
    cout << "No se pudo abrir el archivo de biblioteca." << endl;
    return;
 }
 libro libro;

 while(archivo.read(reinterpret_cast<char*>(&libro), sizeof(libro))) {
    if(libro.id == id_libro){
        // Evitar prestar si no hay stock
        if (cantidad < 0 && libro.stock <= 0) {
            cout << "No hay stock disponible para prestar este libro." << endl;
            break;
        }
        libro.stock += cantidad;

        archivo.seekp(-sizeof(libro), ios::cur);
        archivo.write(reinterpret_cast<char*>(&libro), sizeof(libro));
        break;
}
}
archivo.close();
}



