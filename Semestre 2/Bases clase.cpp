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