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