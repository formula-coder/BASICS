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

//#include <ejemplo.h> // Incluir la libreria personalizada
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

//Clase 4: Punteros y creación de libreria personalizada.

#include<iostream>
#include "mi_libreria.h" // Incluir la libreria personalizada

using namespace std;

int main (){
    imprimirContactos(); // Llamar a la función de la libreria personalizada para imprimir contactos
    return 0;
}


#ifndef MI_LIBRERIA_H
#define MI_LIBRERIA_H

struct Contacto {
    string nombre;
    string telefono;
};

void imprimirContactos() {
    Contacto c1 = {"Juan Perez", "123456789"};
    Contacto c2 = {"Maria Gomez", "987654321"};
    
    cout << "Contacto 1: " << c1.nombre << ", " << c1.telefono << endl;
    cout << "Contacto 2: " << c2.nombre << ", " << c2.telefono << endl;
}
#endif

//punteros: Es una variable que almacena la direccion de memoria de otra variable, permitiendo acceder y manipular el valor almacenado en esa direccion. Se utilizan para gestionar memoria dinamica, crear estructuras de datos complejas y facilitar la comunicacion entre funciones.

#include <iostream>

using namespace std;

int main(){
    int a =10;
    int* ptr = &a; // ptr almacena la direccion de memoria de a
    cout << "Valor de a: " << a << endl; // Imprime el valor de a
    cout << "Direccion de memoria de a: " << &a << endl; // Imprime la direccion de memoria de a
    cout << "Valor almacenado en ptr: " << ptr << endl; // Imprime
    cout << "Valor al que apunta ptr: " << *ptr << endl; // Imprime el valor al que apunta ptr (valor de a)
    return 0;
}

//Paso por referencia: Es una tecnica de paso de parametros a funciones donde se pasa la direccion de memoria de una variable en lugar de su valor, permitiendo que la funcion modifique directamente el valor original de la variable.
//paso por valor: Es una tecnica de paso de parametros a funciones donde se pasa una copia del valor de la variable, lo que significa que cualquier modificacion realizada dentro de la funcion no afectara el valor original de la variable fuera de la funcion.

#include <iostream>
using namespace std;
void func(int a)(a++); // Paso por valor, se modifica solo dentro de la funcion
void funcRef(int* a){(*a)++;} // Paso por referencia, se modifica el valor

int main(){
    int a =10;
    func(a); // Llama a la funcion con paso por valor
    cout << "Valor de a despues de paso por valor: " << a << endl; // Imprime el valor de a (10)
    int* ptr = &a; // Crea un puntero que apunta a a
    funcRef(ptr); // Llama a la funcion con paso por referencia
    cout << "Valor de a despues de paso por referencia: " << a << endl;
    return 0;
}

//Stack vs heap
//Stack: Es una region de memoria utilizada para almacenar variables locales y datos de funciones. Las variables en el stack se crean y destruyen automaticamente a medida que las funciones se llaman y retornan. El acceso a las variables en el stack es rapido, pero el tamaño del stack es limitado.
//Heap: Es una region de memoria utilizada para almacenar datos dinamicos que pueden crecer o reducir
//Variables:Se puede definir un apuntador y directamente  asignar una posición aleatoria de memoria, pero esto puede causar errores si esa posición ya esta siendo utilizada por otra variable o si no se tiene permiso para acceder a esa dirección. Es importante utilizar funciones de asignación de memoria dinámica (como new en C++) para asegurarse de que se asigna memoria de manera segura y controlada.

#include <iostream>
using namespace std;

int main(){
    int* ptr = new int(10);
    cout << "Valor al que apunta ptr: " << *ptr << endl; // Imprime el valor al que apunta ptr (10)
    delete ptr; // Libera la memoria asignada a ptr
    return 0;
}

//Arreglos:El compilador de c++ asigna los arreglos de forma eficiente por medio de apuntadore, pero estos pueden ser definidios directamente en el heap para almacenar una mayor información.

#include <iostream>
using namespace std;

int main(){
    //definición normal
    int arr[5] = {1, 2, 3, 4, 5};
    //definición en el heap
    cout<<arr<<endl;
    //definicion por puntero
int*arr2 = new int[5];
return 0;
}

//aritmetica de apuntadores:Se hace referencia a las posiciones de los arreglos a traves de un desplazamiento del apuntador sobre los bytes de la estructura de datos.

#include <iostream>

using namespace std;

int main(){
    int arreglo[5];
    arreglo[1]-123;
    cout << "Valor del segundo elemento: " << arreglo[1] << endl; // Imprime el valor del segundo elemento (123)
    
    int* arreglo = new int[5]; // Asignación dinámica de un arreglo de 5 enteros
    *(arreglo +1)=123; // Asignación utilizando aritmética de punteros
    cout << "Valor del segundo elemento: " << *(arreglo + 1) << endl; // Imprime el valor del segundo elemento (123)
    delete[] arreglo; // Liberar la memoria asignada al arreglo
}

//Arreglos n -dimensionales:Se almacenan como arreglos cuyp contenido son apuntadores, de los  cuales cada uno de ellos puede ser asignado como un arreglo en si mismo.
#include <iostream>

using namespace std;

int main (){
    int **arreglo = new int*[3]; // Crear un arreglo de punteros para 3 filas
    for(int i=0; i<3; i++){
        arreglo[i] = new int[4]; // Asignar un arreglo de 4 enteros para cada fila
    }
    return 0;
}

//matrices: Se pueden definir como arreglos bidimensionales, donde cada elemento es un arreglo unidimensional. Pueden ser almacenados de manera estática o dinámica dependiendo de las necesidades del programa.
#include <iostream>
using namespace std;
int main(){
    int matriz[3][4]; // Declaración de una matriz de 3 filas y 4 columnas
    int** matrizDinamica = new int*[3]; // Crear un arreglo de punteros para 3 filas
    for(int i=0; i<3; i++){
        matrizDinamica[i] = new int[4]; // Asignar un arreglo de 4 enteros para cada fila
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            matriz[i][j] = i + j; // Asignar valores a la matriz estática
            matrizDinamica[i][j] = i + j; // Asignar valores a la matriz dinámica
        }
    }
    return 0;
}
//Estructuras:
// Las estructuras pueden ser almacendads de manera completa en el heap utilizando su constructor para asignar memoria dinamica a cada uno de sus atributos, o pueden ser almacenados como un apuntador a la estructura, lo que permite una mayor flexibilidad en la manipulación de los datos.
//El operador de flecha (->) se utiliza para hacer alusión a la estructura directamente desde su posición en memoria.
#include <iostream>

using namespace std;

struct persona {
    string nombre;
    int edad;
    persona( string nombre, int edad){}
};

int main(){
    Persona *p= new Persona("Juan", 30); // Crear una instancia de persona en el heap
    cout << "Nombre: " << p->nombre << endl; // Acceder al nombre utilizando el operador de flecha
    cout << "Edad: " << p->edad << endl; // Acceder a la edad utilizando el operador de flecha
    delete p; // Liberar la memoria asignada a la persona
    return 0; 
}
//metodo de organización nuevo:Selection Sort

#include<iostream>
using namespace std;
int main(){
    int arr[5]= {1,0,4,2,3};
    for (int i=0; i <n-1;i++){
        int imin =i;
        for (int j=i+1; j<n;j++){
            if(arr[j]<arr[imin]){
                imin =j;
            }
            if(imin !=i){
                int aux = arr[imin];
                arr[imin] = arr[i];
                arr[i] = aux;
            }
        }
    }
    return 0;
}

//clase 5: Memoria Dinamica 
//memoria estatica: Es la memoria asignada en tiempo de compilacion, donde se almacenan variables globales, locales y constantes. El tamaño de la memoria estatica es fijo y se determina durante la compilacion del programa.
#include "ejemplo.h";
#define valor 10; // Definición de una constante utilizando #define
//memoria dinamica: Es la memoria asignada en tiempo de ejecucion, donde se pueden crear y destruir variables de manera flexible. La memoria dinamica se gestiona a traves de funciones de asignacion y liberacion de memoria, como new y delete en C++.

//memoria automatica: Es la memoria asignada para variables locales dentro de funciones, donde se crean y destruyen automaticamente a medida que las funciones se llaman y retornan. La memoria automatica se gestiona en el stack del programa.


//Asignar memoria dinamica: Se utiliza la palabra clave new para asignar memoria en el heap, permitiendo crear variables o estructuras de datos que pueden crecer o reducir su tamaño durante la ejecucion del programa.

#include <iostream>
using namespace std;
int main(){
    int* ptr = new int(10); // Asignar memoria para un entero y asignar el valor 10
    cout << "Valor al que apunta ptr: " << *ptr << endl; // Imprime el valor al que apunta ptr (10)
    delete ptr; // Liberar la memoria asignada a ptr
    return 0;
}

//Liberar memoria dinamica: Se utiliza la palabra clave delete para liberar la memoria asignada en el heap, evitando fugas de memoria y asegurando un uso eficiente de los recursos del sistema.    
#include <iostream>
using namespace std;
int main(){
    int* ptr = new int(10); // Asignar memoria para un entero y asignar el valor 10
    cout << "Valor al que apunta ptr: " << *ptr << endl; // Imprime el valor al que apunta ptr (10)
    delete ptr; // Liberar la memoria asignada a ptr
    return 0;
}
//Destructor: Es una función miembro especial de una clase que se llama automáticamente cuando un objeto de esa clase es destruido. El destructor se utiliza para liberar recursos, como memoria dinámica, archivos abiertos o conexiones de red, asegurando que el programa no tenga fugas de memoria ni otros problemas relacionados con la gestión de recursos.

#include <iostream>
using namespace std;

struct contacto{
    string nombre;
    string telefono;
    ~contacto(){ // Destructor para liberar recursos
        this->telefono.clear(); // Limpiar el número de teléfono
    }
};

int main(){
    contacto c;
    c.nombre = "Juan";
    c.telefono = "123456789";   
    return 0;
}
//Libreria memoria:
<memory> es una libreria de C++ que proporciona herramientas para la gestión de memoria dinámica, incluyendo punteros inteligentes como std::unique_ptr, std::shared_ptr y std::weak_ptr, que ayudan a prevenir fugas de memoria y facilitan la gestión de recursos en programas complejos.
#include<memory>
int main(){
    unique_ptr<int> uptr = make_unique<int>(10); // Crear un puntero inteligente único que apunta a un entero con valor 10
    cout << "Valor al que apunta uptr: " << *uptr << endl; // Imprime el valor al que apunta uptr (10)
    unique_ptr<int> uptr2 = move(uptr); // Transferir la propiedad del puntero inteligente a uptr2
    cout << "Valor al que apunta uptr2: " << *uptr2 << endl; // Imprime el valor al que apunta uptr2 (10)
    shared_ptr<int> sptr1 = make_shared<int>(20); // Crear un puntero inteligente compartido que apunta a un entero con valor 20
    shared_ptr<int> sptr2 = sptr1; // Compartir la propiedad del puntero inteligente entre sptr1 y sptr2
    cout << "Valor al que apunta sptr1: " << *sptr1 << endl; // Imprime el valor al que apunta sptr1 (20)
    cout << "Valor al que apunta sptr2: " << *sptr2 << endl;
    weak_ptr<int>wptr =sptr1; // Crear un puntero inteligente débil que observa el mismo objeto que sptr1
    cout << "Valor al que apunta wptr: " << *wptr.lock() << endl; // Imprime el valor al que apunta wptr (20)
    return 0;
}

//clase 6: Cadena de caracteres 

//Cadena de caracteres: Las cadenas de caracteres se representan en memoria como un arreglo de caracteres con el delimitador  ('\0') al final para indicar el final de la cadena. Se pueden manipular utilizando funciones de la biblioteca estándar de C++ como strlen, strcpy, strcat, entre otras, o utilizando la clase std::string que proporciona una interfaz más fácil de usar para trabajar con cadenas de caracteres.

char cadena[]= "Hola, mundo!"; // Declaración de una cadena de caracteres como un arreglo de caracteres
char arreglo[] ={'H', 'o', 'l', 'a', '\0'}; // Declaración de una cadena de caracteres utilizando un arreglo de caracteres con el delimitador '\0' al final
cout << "Cadena: " << cadena << endl; // Imprime la cadena de caracteres
cout << "Arreglo: " << arreglo << endl; // Imprime el arreglo de caracteres como una cadena de caracteres


//string: Tipo de dato particular para representar cadenas de caracteres en el sistema de c++, dispone de componentes, operadores y funciones especiales para manipular cadenas de manera implicita.
#include <iostream>
using namespace std;

int main (){
    string nombre = "Juan"; // Declaración de una variable de tipo string
    string apellido = "Perez"; // Declaración de otra variable de tipo string
    string nombreCompleto = nombre + " " + apellido; // Concatenación de strings utilizando el operador +
    cout << "Nombre completo: " << nombreCompleto << endl; // Imprime el nombre completo
    return 0;
}

//leer cadenas:Se utiliza la función getline()para leer cadenas de caracteres con un delimitado especifico, si no se determina el delimitador es el salto de linea, lo que permite leer cadenas con espacios sin problemas.

#include <iostream>
using namespace std;

int main(){
    char* cadena = new char[10];
    cin.getline(cadena, 10, 'a'); // Leer una cadena de caracteres con un límite de 10 caracteres
cout << "Cadena leída: " << cadena << endl; // Imprime la cadena leída
delete[] cadena; // Liberar la memoria asignada a la cadena
}

//libreria <string.h>: Libreria encargada de proveer laas funciones y cosntantes especializadas para el tratamiento de cadenas de caracteres.

//strlen(cadena): Devuelve la longitud de una cadena de caracteres, excluyendo el delimitador '\0' al final.
#include <iostream>
#include <string.h>
using namespace std;

int main (){
    char cadena[] = "Hola, mundo!"; // Declaración de una cadena de caracteres
    cout << "Longitud de la cadena: " << strlen(cadena) << endl; // Imprime la longitud de la cadena
    return 0;
}

//strcpy(destino, origen): Copia una cadena de caracteres desde la variable origen a la variable destino, asegurándose de incluir el delimitador '\0' al final.
#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char cadena[] = "Hola, mundo!"; // Declaración de una cadena de caracteres
    char* copia = new char[strlen(cadena)];
    strcpy(copia, cadena); // Copia la cadena original a la nueva variable
    cout << "Cadena original: " << cadena << endl; // Imprime la cadena original
    cout << "Copia de la cadena: " << copia << endl; // Imprime la copia de la cadena
    delete[] copia; // Liberar la memoria asignada a la copia
    return 0;
}

//strtok(cadena, delimitadores): Divide una cadena de caracteres en tokens utilizando los delimitadores especificados, devolviendo un puntero al siguiente token cada vez que se llama a la función.
#include <iostream>
#include <string.h>

using namespace std;

int main(){
char cadena[] = "Hola, mundo!"; // Declaración de una cadena de caracteres
char* ptr = strtok(cadena, ""); // Dividir la cadena en tokens utilizando los delimitadores ',' y ' '
cout<< cadena <<endl;
cout << "Tokens: " << endl;
cout << ptr << endl; // Imprime el primer token    
return 0;
}

//leer archvio. CSV
//Los archivos separados por comas(CSV)se pueden leer como archivos planos y separar sus datos, para luego transformarlos a los tipos de datos esperados.
//41, marco antonio, estrada, 38.

//strcat(destino, origen):Concatenar cadenas, crear una unica cadena a artir de dos o mas cadenas diferentes.

#include <iostream>
#include <string.h>

using namespace std;

int main(){
    cahr c1[]=" Jimmy";
    char c2[]=" Hendrix";
    cout<< c1 << endl;
    strcat(c1, c2); // Concatenar c2 al final de c1
    cout << "Cadena concatenada: " << c1 << endl; // Imprime la cadena concatenada
    return 0;
}
//strcmp(cadena 1, cadena 2): Comparar dos cadenas de caracteres, devolviendo un valor entero que indica la relación entre las cadenas (0 si son iguales, un valor negativo si la primera cadena es menor que la segunda, y un valor positivo si la primera cadena es mayor que la segunda).
#include <iostream>
#include <string.h>

using namespace std;
int main(){
    char c1[] = "Hola";
    char c2[] = "hola";
cout<< strcmp(c1, c2) << endl; // Imprime el resultado de la comparación (0 si son iguales, un valor negativo si c1 es menor que c2, y un valor positivo si c1 es mayor que c2)
cout<<strcmp(c2, c1) << endl; // Imprime el resultado de la comparación (0 si son iguales, un valor negativo si c2 es menor que c1, y un valor positivo si c2 es mayor que c1)
cout<<strcmp(c1, c1) << endl; // Imprime el resultado de la comparación (0 si son iguales, un valor negativo si c1 es menor que c1, y un valor positivo si c1 es mayor que c1) 
return 0;
}
