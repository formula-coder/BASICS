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
