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

//Archivos

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void escribir();

int main() {
    escribir();
    system("pause");
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
    int numero;
    int *dir_num;

    cout<<"Digite un numero: ";cin>>numero;
    dir_num=&numero;
    
    if(*dir_num%2==0){
        cout<<"El numero "<<*dir_num<<" es par"<<endl;
        cout <<"Direccion de memoria: "<<dir_num<<endl;
    }
    else{
        cout<<"El numero "<<*dir_num<<" es impar"<<endl;
        cout<<"Direccion de memoria: "<<dir_num<<endl;
    }
    getch();
    return 0;
}

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

#include <iostream>
#include<conio.h>
using namespace std;
int main(){
    int numeros[10]={1,2,3,4,5,6,7,8,9,10};
    int *dir_numeros;
    dir_numeros=numeros;

    for(int i=0;i<10;i++){
        cout<<"Elemento "<<i+1<<": "<<*(dir_numeros+i)<<endl;
    }
    for(int i=0;i<10;i++){
        cout<<"Posición de memoria de el elemento"<<numeros[i]<<": "<<(dir_numeros+i)<<endl;
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
#include <iostream>
#include<conio.h>
using namespace std;
@@ -180,24 +157,6 @@ int main(){
    return 0;
}

#include <iostream>
#include<conio.h>
using namespace std;
int main(){
    int numeros[10]={1,2,3,4,5,6,7,8,9,10};
    int *dir_numeros;
    dir_numeros=numeros;

    for(int i=0;i<10;i++){
        cout<<"Elemento "<<i+1<<": "<<*(dir_numeros+i)<<endl;
    }
    for(int i=0;i<10;i++){
        cout<<"Posición de memoria de el elemento"<<numeros[i]<<": "<<(dir_numeros+i)<<endl;
    }
getch();
return 0;
}

#include<iostream>
#include<conio.h>

 int main(){
            cout<<"Posicion de memoria: "<<(dir_numeros+i)<<endl;
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
#include <iostream>
#include <string.h>

using namespace std;

int main( ){
    char cad1[]="Hola";
    char cad2[]="Mundo";
    char cad3[30];

    strcpy(cad3,cad1);//copiar cad1 en cad3
    strcat(cad3,cad2);//concatenar cad2 al final de cad3
    cout << "La cadena concatenada es: " << cad3 << endl;
}

#include <iostream>
#include <string.h>

using namespace std;

int main(){
    char cad1[]="hola mundo";
    strrev(cad1);
    cout<<"La cadena invertida es: "<<cad1<<endl;

}

#include <iostream>
#include <string.h>
using namespace std;
int main(){
    char palabra[]="programacion";
    strupr(palabra);
    cout<<"La palabra en mayusculas es: "<<palabra<<endl;
}

#include <iostream>
#include <string.h>
using namespace std;
int main(){
    char palabra[]="PROGRAMACION";
    strlwr(palabra);
    cout<<"La palabra en minusculas es: "<<palabra<<endl;
}

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
    char cadena[]="12345";
    float numeros;
    numeros=atof(cadena);
    cout<<"El numero es: "<<numeros<<endl;
    int numero;
    numero=atoi(cadena);
    cout<<"El numero es: "<<numero<<endl;
}


//programacion orientada a objetos..

//clases: Una clase es una plantilla para crear objetos, que define atributos y comportamientos comunes.
//Objetos: Un objeto es una instancia de una clase que encapsula datos y funcionalidades relacionadas.
//abstraccion: La abstraccion es el proceso de simplificar un sistema complejo al enfocarse en los aspectos esenciales y ocultar los detalles innecesarios.
//encapsulamiento: El encapsulamiento es el principio de ocultar los datos internos de un objeto y proporcionar acceso a ellos solo a traves de metodos publicos.
//herencia: La herencia es un mecanismo que permite a una clase derivada heredar atributos y metodos de una clase base, promoviendo la reutilizacion de codigo.
//polimorfismo: El polimorfismo es la capacidad de un objeto para tomar diferentes formas, permitiendo que una misma interfaz pueda ser utilizada para diferentes tipos de objetos.

//abstraccion: La abstraccion es el proceso de simplificar un sistema complejo al enfocarse en los aspectos esenciales y ocultar los detalles innecesarios.
//encapsulamiento: El encapsulamiento es el principio de ocultar los datos internos de un objeto y proporcionar acceso a ellos solo a traves de metodos publicos.
//herencia: La herencia es un mecanismo que permite a una clase derivada heredar atributos y metodos de una clase base, promoviendo la reutilizacion de codigo.
//polimorfismo: El polimorfismo es la capacidad de un objeto para tomar diferentes formas, permitiendo que una misma interfaz pueda ser utilizada para diferentes tipos de objetos.
//polimorfismo: El polimorfismo es la capacidad de un objeto para tomar diferentes formas, permitiendo que una misma interfaz pueda ser utilizada para diferentes tipos de objetos.
#include<iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
using namespace std;

class persona{
    private://atributos
        int edad;
        string nombre;
    public://metodos
    persona(int, string);//constructor
    void leer();
    void correr();

};
//definicion del constructor: nos sirve para inicializar los atributos de la clase
persona::persona(int _edad, string _nombre){
    edad=_edad;
    nombre=_nombre;
}

void persona::leer(){
    cout<<"La persona "<<nombre<<" esta leyendo"<<endl;
}
void persona::correr(){
    cout<<"La persona "<<nombre<<" esta corriendo"<<endl;
}
int main(){
persona p1= persona (20,"Alejandro");
p1.leer();

persona p2= persona (25,"Andres");
p2.correr();

persona p3= persona (30,"Maria");
p3.leer();
p3.correr();
getch();
    return 0;
}

#include <iostream>
#include<stdlib.h>

using namespace std;

class fecha{
    private:
        int dia;
        int mes;
        int anio;
    public:
        fecha(int, int, int);
        void mostrarFecha();
};

fecha::fecha(int _dia, int _mes, int _anio){
    dia=_dia;
    mes=_mes;
    anio=_anio;
}
fecha::mostrarfecha(){
    anio = int (fecha/10000);
    mes = int ((fecha%10000)/100);
    dia = int (fecha%100);
}
void fecha::mostrarfecha(){
    cout<<" la fecha es:"<<dia<<"/"<<mes<<"/"<<anio<<endl;
}
int main(){
    fecha hoy(9,6,2024);
    fecha ayer(8,6,2024);
    ayer.mostrarFecha();
    hoy.mostrarFecha();
}   

//destructores: es un metodo especial que se llama automaticamente cuando un objeto de una clase es destruido o sale de su ambito
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class perro{
    private:
        string nombre;
        string raza;
    public:
        perro(string, string);//constructor
        ~perro();   // aquí
        void ladrar();
        void mostrarDatos();
};
//definicion del constructor
perro::perro(string _nombre, string _raza){
    nombre=_nombre;
    raza=_raza;
}
//definicion del destructor: se utiliza para liberar recursos cuando un objeto ya no es necesario
perro::~perro() {  // y aquí
    cout << "El perro " << nombre << " se ha ido" << endl;
}
void perro::mostrarDatos(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Raza: "<<raza<<endl;
}
void perro::ladrar(){
    cout<<"Guau Guau"<<endl;
    cout<<"El perro "<<nombre<<" esta ladrando"<<endl;
}

int main(){
    perro p1("Firulais", "Labrador");
    p1.mostrarDatos();
    p1.ladrar();
    system("pause");  // espera a que pulses una tecla
    return 0;
}
//setters y getters: son metodos que permiten establecer y obtener los valores de los atributos privados de una clase
#include <iostream>
#include <stdlib.h>
using namespace std;

class punto{
    private://atributos
        int x;
        int y;
    public://metodos
        punto();//constructor
        void setPunto(int,int);
        int getpuntoX();  
        int getpuntoY();   
};
punto::punto(){
}
//establecer valores a los atributos: setter
void punto::setPunto(int _x, int _y){
    x=_x;
    y=_y;
}
int punto::getpuntoX(){//obtener valores de los atributos: getter
    return x;
}
int punto::getpuntoY(){
    return y;
}
int main(){
    punto punto1;
    punto1.setPunto(5,10);
    cout<<punto1.getpuntoX()<<endl;
    cout<<punto1.getpuntoY()<<endl;
}

//Herencia: es un mecanismo que permite a una clase derivada heredar atributos y metodos de una clase base, promoviendo la reutilizacion de codigo.
#include <iostream>
#include <stdlib.h>
using namespace std;
class persona{
    private:
        string nombre;
        int edad;
    public:
     persona(string,int);//constructor
        void mostrarDatos();
};
class estudiante: public persona{
    private:
        string carrera;
        float promedio;
    public:
    estudiante(string,int,string,float);
        void mostrarEstudiante();
};
void persona::mostrarDatos(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}
persona::persona(string _nombre, int _edad){
    nombre=_nombre;
    edad=_edad;
}
estudiante::estudiante(string _nombre, int _edad, string _carrera, float _promedio):persona(_nombre,_edad){
    carrera=_carrera;
    promedio=_promedio;
}
void estudiante::mostrarEstudiante(){
    mostrarDatos();
    cout<<"Carrera: "<<carrera<<endl;
    cout<<"Promedio: "<<promedio<<endl;
}

int main(){
    Estudiante est1("Alejandro",20,"Ingenieria de Sistemas",4.5);
    est1.mostrarEstudiante();
    system("pause");
}

//polimorfismo: es la capacidad de un objeto para tomar diferentes formas, permitiendo que una misma interfaz pueda ser utilizada para diferentes tipos de objetos.
#include <iostream>
#include <stdlib.h>
using namespace std;

class persona{
    private:
        string nombre;
        int edad;
    public:
        persona(string,int);//constructor
        virtual void mostrar();//metodo virtual
};
 class estudiante:public persona{
    private:
        float nota;
    public:
        estudiante(string,int,float);
        void mostrar();
 };  
 class profesor: public persona{
    provate:
        string asignatura;
    public:
        profesor(string,int,string);
        void mostrar();
 };
 profesor::profesor(string _nombre,int _edad,string _asignatura):persona(_nombre,_edad){
    asignatura=_asignatura;}

persona::persona(string _nombre,int _edad){
    nombre=_nombre;
    edad=_edad;
}
estudiante::estudiante(string _nombre,int _edad,float _nota):persona(_nombre,_edad){
    nota=_nota;
}
void estudiante::mostrar(){
    persona::mostrar();
    cout<<"Nota: "<<nota<<endl;
}
void persona::mostrar(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}
void profesor::mostrar(){
    persona::mostrar();
    cout<<"Asignatura: "<<asignatura<<endl;
}
int main(){
    persona *grupo[3];
    grupo[0]=new estudiante("Alejandro",20,4.5);
    grupo[1]=new profesor("Andres",35,"Matematicas");
    grupo[2]=new estudiante("Maria",22,4.8);

    for(int i=0;i<3;i++){
        grupo[i]->mostrar();
        cout<<endl;
    }
    system("pause");
    return 0;
}