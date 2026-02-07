//clase 1 = estructuras y constructores / tipos de datos
#include <iostream>
using namespace std;

struct alumno{
    string nombre;
    int edad;
    Alumno (){
        this->nombre = "sin nombre"; // this se usa para referirse a los atributos de la clase 
        this->edad = 0;
    }
};
int main(){
    alumno a1;
    cout<<"Nombre: "<<a1.nombre<<endl;
    cout<<"Edad: "<<a1.edad<<endl;
    return 0;
}
//unsigned
#include <iostream>
using namespace std;

int maxInt = ( 1 << 32)-1;// desplazamiento de bits a la izquierda 
unsigned int maxUInt = ( 1 << 32)-1;

cout << "Max int: " << maxInt << endl;
cout << "Max unsigned int: " << maxUInt << endl;

//auto

#include <iostream>
using namespace std;

int main(){
    auto numero = 42; // El compilador infiere que 'numero' es de tipo int
    auto texto = "Hola, mundo!"; // El compilador infiere que 'texto
    auto decimal = 3.14; // El compilador infiere que 'decimal' es de tipo double
    auto char = 'A'; // El compilador infiere que 'char' es de tipo char   

    cout << "Numero: " << numero << endl;
    cout << "Texto: " << texto << endl;
    cout << "Decimal: " << decimal << endl;
    cout << "Char: " << char << endl;
    return 0;
}

//conversion de tipos de datos

#include <iostream>
using namespace std;

int main() {
    int entero = 42;
    double decimal = 3.14;

    // Conversión implícita
    double resultado1 = entero + decimal; // entero se convierte automáticamente a double
    cout << "Resultado de la suma (implícita): " << resultado1 << endl;

    // Conversión explícita (casting)
    int resultado2 = static_cast<int>(decimal); // decimal se convierte a int
    cout << "Resultado de la conversión explícita: " << resultado2 << endl;

    return 0;
}

//clase 2 :
//Operadores: Al crear estructuras de datos nuevas no existe una definicion para los operadores basicos, por lo que es necesario definir un proceso para cada uno de ellos.

struct contact{
    string name;
    string phone;
};

int main(){
    contact c;
    cout<<"Nombre: "; cin>>c.name;
    cout<<"Telefono: "; cin>>c.phone;
    cout<<"Contacto guardado: "<<c.name<<", "<<c.phone<<endl;
    return 0;
}

//Operadores de asignacion: Se define el comportamiento del operador como una funcion dentro de la estructura con el retorno esperado depues de aplicar el operador en esta.

struct contact{
    string name;
    string phone;
    //constructor
    contact(){
        this->name;
        this->phone;
    }
    friend ostream& operator<<(ostream& os, const contact& c){
        os << "Nombre: " << c.name << ", Telefono: " << c.phone;
        return os;
    }
};
//Escritura: 1. Libreria fstream 2. declaracion de la variable 3. validar archivo 4. operador de escritura(<<) 5. cerrar archivo.

#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream archivo("contactos.txt", ios::out);
    int valor =100;
    if(archivo.is_open()){
        archivo << "Valor: " << valor << endl;
        archivo.close();

}
return 0;
}

//Lectura de archivos: 1. Libreria fstream 2. declaracion de la variable 3. validar archivo 4. operador de lectura(>>) 5. cerrar archivo.

#include <iostream>
#include <fstream>

using namespace std;

int main(){
    fstream archivo ("archivo.txt", ios::in);
    int valor;
    if(archivo){
        archivo >> valor;
        cout<<"Valor leido: "<<valor<<endl;
        archivo.close();
    }
    return 0;
}

// archivos binarios
// Formato de archivo basado en bits para almacenar de manera eficiente valores, almacenandolo de la manera exacta en la que se encuentran en memoria.
//Extensiones: .bin, .dat, .jpg, .png, .mp3, .mp4

//Escritura en archivos binarios: Se alamcenan los elementos en memoria con la funcion write(), se recibe la posicion en memoria del valor a guardar y el tamaño en bytes del valor.

#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream archivo("archivo.bin",ios::out | ios::binary);
    int valor=12345;
    if(archivo){
        archivo.write(reinterpret_cast<char*>(&valor), sizeof(valor));
        archivo.close();
    }
}

//flags de apertura:
 //ios::in -> lectura
 //ios::out -> escritura
 //ios::app -> agregar al final del archivo
 //ios::ate -> mover el puntero al final del archivo
 //ios::trunc -> borrar el contenido del archivo
 //ios::binary -> abrir en modo binario

 //Funciones de acceso a archivos binarios:Especializados en la manipulacion de archivos binarios.
//seek: Navegar una cantidad de bytes en especifica direccion (inicio, actual, final).
//ios::beg -> inicio del archivo
//ios::cur -> posicion actual del puntero
//ios::end -> final del archivo
//seekg: Mover el puntero de lectura
//seekp: Mover el puntero de escritura

#include <iostream>
#include <fstream>
using namespace std;

archivo.seekg(0, ios::beg); // Mover al inicio del archivo
archivo.seekg(10, ios::cur); // Mover 10 bytes desde la posicion actual
archivo.seekg(-5, ios::end); // Mover 5 bytes antes del final del archivo

//tell: Obtener la posicion actual del puntero de lectura o escritura
//tellg(): para lectura
//tellp(): para escritura

int pos = archivo.tellg(); // Obtener la posicion actual del puntero de lectura
cout << "Posicion actual del puntero de lectura: " << pos << endl;

//clase 3: Librerias

//stdlib.h: Proporciona funciones para gestionar memoria dinamica, conversion de tipos, generacion de numeros aleatorios, entre otras utilidades generales.

//Conversion de cadenas a numeros
//atof(): Convierte una cadena a un numero de punto flotante (float).
//atoi(): Convierte una cadena a un numero entero (int).
//rand(): Genera un numero aleatorio entero entre 0 y RAND_MAX.
//rand(int n): Genera un numero aleatorio entre 0 y n-1.
//exit(int status): Termina la ejecucion del programa con un estado especifico.

//libreria time
//Proporciona funciones para manipular y formatear fechas y horas.
//time(): Obtiene la hora actual en segundos desde el 1 de enero de 1970.
//localtime(): Convierte un valor de tiempo en una estructura tm con la hora local.
//time_t: Tipo de dato para representar tiempo en segundos desde el 1 de enero de 1970.
//tm: Estructura que contiene componentes de fecha y hora (año, mes, dia, hora, minuto, segundo, etc.).
//ctime(): Convierte una estructura tm en una cadena de caracteres con formato legible.

#include <iostream>
#include <ctime>
using namespace std;

int main(){
    time_t ahora = time(0);
    cout <<ctime(&ahora);
    tm *ltm = localtime(&ahora);
    cout << "Año: " << 1900 + ltm->tm_year << endl;
    cout << "Mes: " << 1 + ltm->tm_mon << endl;
    cout << "Dia: " << ltm->tm_mday << endl;
    return 0;
}

//libreria math.h
//Proporciona funciones matematicas comunes para operaciones aritmeticas y trigonométricas.
//sqrt(double x): Calcula la raiz cuadrada de x.
//pow(double base, double exponente): Calcula la potencia de base elevado a exponente.
//sin(double x): Calcula el seno de x (en radianes).
//cos(double x): Calcula el coseno de x (en radianes).
//exp(double x): Calcula e elevado a la x.
//log(double x): Calcula el logaritmo natural (base e) de x.

//estructuras de datos: Permiten organizar y almacenar datos de manera eficiente, facilitando su manipulación y acceso. Ejemplos comunes incluyen listas, pilas, colas, árboles y grafos. Cada estructura tiene sus propias ventajas y desventajas dependiendo del tipo de datos y las operaciones que se necesiten realizar.
//vector: Es una estructura de datos que almacena elementos de manera contigua en memoria, permitiendo acceso aleatorio y redimensionamiento dinámico. Es parte de la biblioteca estándar de C++ (STL) y ofrece funciones para agregar, eliminar y acceder a elementos de manera eficiente.
//set: Es una estructura de datos que almacena elementos únicos en un orden específico. No permite elementos duplicados y se utiliza comúnmente para realizar operaciones de conjunto como unión, intersección y diferencia.
//map: Es una estructura de datos que almacena pares clave-valor, donde cada clave es única. Permite acceder a los valores asociados a las claves de manera eficiente y se utiliza comúnmente para realizar búsquedas rápidas y almacenar datos relacionados.
//stack: Es una estructura de datos que sigue el principio LIFO (Last In, First Out), donde el último elemento agregado es el primero en ser eliminado. Se utiliza comúnmente para almacenar datos temporales y realizar operaciones de retroceso.
//queue: Es una estructura de datos que sigue el principio FIFO (First In, First Out), donde el primer elemento agregado es el primero en ser eliminado. Se utiliza comúnmente para almacenar datos en orden de llegada y realizar operaciones de procesamiento en secuencia.
//deque: Es una estructura de datos que permite agregar y eliminar elementos tanto al inicio como al final de la secuencia. Es una combinación de stack y queue, ofreciendo flexibilidad en la manipulación de datos.
//list: Es una estructura de datos que almacena elementos de manera no contigua en memoria, permitiendo inserciones y eliminaciones eficientes en cualquier posición. Es parte de la biblioteca estándar de C++ (STL) y se utiliza comúnmente para almacenar datos que requieren modificaciones frecuentes.


//libreria personalizada: Es una libreria creada por el usuario para contener funciones, clases o estructuras que pueden ser reutilizadas en diferentes partes del programa o en diferentes proyectos. Permite organizar el código de manera modular y facilita su mantenimiento y reutilización.

#include <ejemplo.h> // Incluir la libreria personalizada
#include <iostream>
using namespace std;

int main(){
    // Utilizar funciones o clases de la libreria personalizada
    saludar(); // Llamar a una función definida en ejemplo.h
    return 0;
}

void saludar(){
    cout<<"Hola desde la libreria personalizada!"<<endl;
}
