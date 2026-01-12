/*Estructuras: Es una coleccion de uno a mas tipos de elementos denominados campos, cada uno de los cuales puede ser un tipo de dato diferente.*/
#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Coleccion {
    string titulo;
    string artista;
    int numCanciones;
    float precio;
    string fecha_compra;
};

int main() {
    Coleccion colecciones[30];
    int cantidad;
cout <<"Ingrese la cantidad de artistas que desea registrar: "<<endl;
cin >> cantidad;

    for (int i = 0; i < cantidad; ++i) {
        cout << "Ingrese el nombre del artista: ";
        getline(cin, colecciones[i].artista);

        cout << "Ingrese el titulo del disco: ";
        getline(cin, colecciones[i].titulo);

        cout << "Ingrese el numero de canciones: ";
        cin >> colecciones[i].numCanciones;

        cout << "Ingrese el precio del disco: ";
        cin >> colecciones[i].precio;

        // Limpiar el salto de linea pendiente antes de usar getline nuevamente
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Ingrese la fecha de compra: ";
        getline(cin, colecciones[i].fecha_compra);
    }

    for (int j = 0; j < cantidad; ++j) {
        cout << "Artista: " << colecciones[j].artista << endl;
        cout << "Titulo: " << colecciones[j].titulo << endl;
        cout << "Numero de canciones: " << colecciones[j].numCanciones << endl;
        cout << "Precio: " << colecciones[j].precio << endl;
        cout << "Fecha: " << colecciones[j].fecha_compra << endl;
    }
}
//archivos: creacion y escritura de archivos
#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

void escribir();
int main(){
    escribir();
    return 0;   
}

void escribir(){
    ofstream archivo;
    string nombreArchivo;
    string texto;
    cout<<"digite el nombre del archivo: ";
    getline(cin,nombreArchivo);
    archivo.open(nombreArchivo.c_str(),ios::out);
    archivo.open("C:\\Users\\Yezid Andres\\Documents\\UNIVERSIDAD\\archivo.txt",ios::out);
    archivo.open("archivo.txt",ios::out);

    if(archivo.fail()){
        cout<<"No se pudo crear el archivo";
        exit(1);
    }
cout<<"Escribiendo en el archivo"<<endl;
getline(cin,texto);
    archivo<<"gol de colombia"<<endl;
    archivo<<"gol de argentina"<<endl;

    archivo.close();
}

//archivos: lectura de archivos
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

void leer();
int main(){
    leer();
    return 0;   
}

void leer(){
    ifstream archivo;
    string nombreArchivo;
    string texto;
    cout<<"digite el nombre del archivo: ";
    getline(cin,nombreArchivo);
    archivo.open(nombreArchivo.c_str(),ios::in);
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    while(!archivo.eof()){
        getline(archivo,texto);
        cout<<texto<<endl;
    }
    archivo.close();
}

//punteros Bv
#include <iostream>
#include<conio.h>
using namespace std;
int main(){
    int num;
    int *dir_num;

    num=10;
    dir_num=&num;

    cout<<"Numero:"<<*dir_num<<endl;
    cout<<"Direccion de memoria de num:"<<dir_num<<endl;
}
//punteros ejemplo
#include <iostream>
#include<conio.h>
using namespace std;
int main(){
    int num;
    int *dir_num;
    cout<<"digite un numero: ";cin>>num;
    dir_num=&num;
    cout<<"El numero que digito es: "<<*dir_num<<endl;
    cout<<"La direccion de memoria es: "<<dir_num<<endl;
 if (*dir_num <= 1) {
        primo = false;
    } else {
        for (int i = 2; i < *dir_num; i++) {
            if (*dir_num % i == 0) {
                primo = false;
                break;
            }
        }
    }

    if (primo) {
        cout << "El numero es primo" << endl;
    } else {
        cout << "El numero no es primo" << endl;
    }

    getch();
    return 0;
}

#include<iostream>
#include<conio.h>

using namespace std;

int main(){
    int numeros[10];
    int *dir_numeros;

    for(int i=0;i<10;i++){
        cout<<"Digite un numero: ";cin>>numeros[i];
        cin>> numeros[i];
    }
    dir_numeros=numeros;
    for(int i=0;i<10;i++){
        if (*(dir_numeros%2==0)){
            cout<<"El numero "<<*(dir_numeros+i)<<" es par"<<endl;
            cout<<"Posicion de memoria: "<<(dir_numeros+i)<<endl;
        }
        else{
            cout<<"El numero "<<*(dir_numeros+i)<<" es impar"<<endl;
            cout<<"Posicion de memoria: "<<(dir_numeros+i)<<endl;
        }
    }
}

int *p = new int;
*p = 20;
delete p;


#include <iostream>
using namespace std;

int main() {
    int n;
    char opcion;

    cout << "Cuantas personas van a estar? ";
    cin >> n;

    // Crear memoria dinámica
    int *personas = new int[n];

    cout << "Se creo espacio para " << n << " personas.\n";

    cout << "Te equivocaste? (s/n): ";
    cin >> opcion;

    if (opcion == 's' || opcion == 'S') {
        cout << "Nueva cantidad: ";
        cin >> n;

        // Liberar memoria anterior
        delete[] personas;

        // Crear nueva memoria
        personas = new int[n];

        cout << "Ahora el espacio es para " << n << " personas.\n";
    }

    // Liberar memoria al final
    delete[] personas;

    return 0;
}


//cadenas de caracteres
#include <iostream>
#include<string.h>
using namespace std;

int main(){
    char palabra[]="alejandro";
    cout<<"La palabra es: "<<palabra<<endl;
    cout<<"La longitud de la palabra es: "<<strlen(palabra)<<endl;
    cout<<"La palabra en mayusculas es: ";
    for(int i=0;i<strlen(palabra);i++){
        cout<<(char)toupper(palabra[i]);
    }
    charpalabra2[]={"ANDRES"};
    cout<<"\nLa palabra en minusculas es: ";
    for(int i=0;i<strlen(palabra2);i++){
        cout<<(char)tolower(palabra2[i]);
    }
    char palabra3[20];
    cout<<"\nDigite una palabra no menor de 20 caracteres: ";
    cin.getline(palabra3,20);
    cout<<"La palabra digitada es: "<<palabra3<<endl;

}
#include <iostream>
#include <string.h>
using namespace std;
int main(){
    char nombre[]="Alejandro";
    char nombre2[20];
    cout<<"El nombre es: "<<nombre<<endl;
    strcpy(nombre2,nombre);
    cout<<"El nombre copiado es: "<<nombre2<<endl;
}

#include <iostream>
#include <string.h>
using namespace std;
int main(){
    char palabra1[]="Hola";
    char palabra2[]="Mundo";
    if(strcmp(palabra1,palabra2)==0){
        cout<<"Las palabras son iguales"<<endl;
}
    else{
        cout<<"Las palabras son diferentes"<<endl;
    }
    if (strcmp(palabra1,palabra2)<0){
        cout<<"La primera palabra es menor que la segunda"<<endl;
    }
    else{
        cout<<"La primera palabra es mayor que la segunda"<<endl;
    }
}

