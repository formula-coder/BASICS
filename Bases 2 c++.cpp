//Tipos de datos en c++

#include <iostream>
#include<stdio.h>

using namespace std;

int main(){
    int entero = 15;
	cout<< entero << " entero "<<;
}
float flotante  = 10.45;
cout<< flotante << " flotante"<<endL;

double mayor  = 3.1415
cout<< mayor<<" double"<< endl;

printf("%f,"mayor); printf("\n%c","double\n");
cout.preccision(16);
cout<< mayor << " double con precision" << endl;

    char caracter = 'a';
    cout << caracter << " caracter" << endl;

    string letras = "probando";
    cout << letras << " letras" << endl;

    string probando = "probando";
    cout << probando << endl;

    // Variables
    int numero = 10;
    float decimal = 3.14;
    char letra = 'A';
    string texto = "Hola, C++";
    int a = 8, b = 3;
    cout << "El resultado de la suma es: " << a + b << endl;

    int  n1, n2;
    cout << "Ingrese el primer numero: ";
    cin >> n1;
    cout << "Ingrese el segundo numero: ";
    cin >> n2;
    cout << "La suma de " << n1 << " y " << n2 << " es: " << n1 + n2 << endl;
 
    int base, altura, area;
    cout << "Ingrese la base del triángulo: ";
    cin >> base;
    cout << "Ingrese la altura del triángulo: ";
    cin >> altura;
    area = (base * altura) / 2;
    cout << "El área del triángulo es: " << area << endl;

    //Condicionales
    int numero;
    cout << "Ingrese un numero: ";
    cin >> numero;
    if (numero > 0) {
        cout <<" El numero es positivo" << endl;
    else if(numero < 0) {
        cout << "El numero es negativo" << endl;
    } else(numero == 0) {
        cout << "El numero es cero" << endl;
    }

    //Modulo 

    int numero;
    cout << "Ingrese un numero: ";
    cin >> numero;
    if (numero % 2 == 0) {
        cout << "El numero es par" << endl;
    } else {
        cout << "El numero es impar" << endl;
    }

    int horas, minutos, segundos;
    cout << "Ingrese las horas: ";
    cin >> horas;
    cout << "Ingrese los minutos: ";
    cin >> minutos;
    cout << "Ingrese los segundos: ";
    cin >> segundos;

    if (minutos >0 )
    {
        horas = horas + 1;
    }
    total = horas *3.50;
    cout <<"el total a pagar es: " << total << endl;

    //ciclos
    int i, numero, factorial = 1;
    cout << "Ingrese un numero: ";
    cin >> numero;

    for (i = 1; i <= numero; i++) {
        factorial *= i;
    }
    cout << "El factorial de " << numero << " es: " << factorial << endl;

    int main(){
        cout <<"los numeros impares son: "<< endl;
        for (int i = 1; i < 40; i += 2) {
            cout << i << ":numero "<<endl;

        }
    }
    int main(){
        cout << "los numeros pares son: " << endl;
        for (int i = 0; i < 40; i += 2) {
            cout << i << ":numero" << endl;
        }
    }
    int main(){
        for(int x = 1; x <= 10; x++)
        {
            if(numero % 2 == 0)
            {
                cout << x << ":numero" << endl;
            }
            else
            {
                cout << x << ":numero" << endl;
            }
            
        }
            
    }
//Operador de incremento
    a++;
    a = a + 1;
    a += 1;
    cout << "El valor de a incrementado es: " << a << endl;
// Operador de decremento
    a--;
    a = a - 1;
    a -= 1;
    cout << "El valor de a decrementado es: " << a << endl;

// Ciclo while
int main() {
    int contador = 1;
    while (contador <= 10) {
        cout << contador << ":numero" << endl;
        contador++;
    }
    return 0;
int main() {
Cout << "Ingrese un numero positivo: ";
cin >> numero;

while (numero >= 0)
{
    Suma += numero;
    cout << "Ingrese un numero positivo: ";
    cin >> numero;
}

//do while, es un ciclo que se ejecuta al menos una vez, y luego repite la ejecucion mientras una condicion sea verdadera.
int main() {
    int contador = 1;
    do {
        cout << contador << ":numero" << endl;
        contador++;
    } while (contador <= 10);
    return 0;
}

//Clase porgramacion Bv
    int prueba (){

    int m = 15
    cout << "El valor de m es: " << m << endl;
    int n = 20;
    cout << "El valor de n es: " << n << endl;
}
int main() {
    int m = 15;
    cout <<" El valor de m es: " << m << endl;
    int n = 20;
    cout << "El valor de n es: " << n << endl;

    //Operador de incremento
    a++;
    a = a + 1;
    a += 1;
    cout << "El valor de a incrementado es: " << a << endl;
// Operador de decremento
    a--;
    a = a - 1;
    a -= 1;
    cout << "El valor de a decrementado es: " << a << endl;
    return 0;
// Operadores logicos
    int x = 10;
    int y = 5;
    if (x > 0 && y > 0) {
        cout << "Ambos numeros son positivos" << endl;
    }
    if (x > 0 || y < 0) {
        cout << "Al menos uno de los numeros es positivo" << endl;
    }
    if (!(x < 0)) {
        cout << "x no es negativo" << endl;

// operadores  de bucle
    int i = 0;
    while (i < 5) {
        cout << "Iteracion: " << i << endl;
        i++;
        getch()
        return 0;

    int i = 10;
    while(i>=1)
    cout << i <<endl;
    i--;
    }
}

//switch (  alternativa multiple)
#include <iostream>
using namespace std;

int main()
{
	int op = 0;
	cout<<"Seleccione una opcion: ";
	cin>>op;
	
	cout<<"\n";
	switch (op)
	{
		case 1:
			cout<<"Resultado 1";
			break;
		case 2:
			cout<<"Resultado 2";
			break;
		case 3:
			cout<<"Resultado 3";
			break;
		case 4:
			cout<<"Resultado 4";
			break;
		case 5:
			cout<<"Resultado 5";
			break;
		default:
			cout<<"Resultado por defecto si no se elije nada de lo anterior";
	}
}
//arreglos
int main(){
#include<iostream>
using namespace std;
int i [5]={1,2,3,4,5};
int a=0;
float promedio=0;

int main(){
 for (int j=0;j<5;j++){
 cout<<"ingresa un numero: "<<j<<endl;
 cin>>i[j];
 a +=i[j];
}
promedio =a/5;
cout<<" el promedio de los valores son: "<<promedio;
}
}
#include <iostream>
using namespace std;

int main(){

    int i[5]={1,2,3,4,5};
    string nombre[5];
    int edad[5];
    
    for(int j=0;j<5;j++){
        cout<<"Ingrese el nombre de la persona "<<j<<endl;
        cin>>nombre[j];
        cout<<"Ingrese la edad de la persona "<<j<<endl;
        cin>>edad[j];
        
        
        if(edad[j]>=18){
		
        cout<<"eres mayor de edad "<<nombre[j]<<endl;
		}
        else{ 
		cout<<"eres menor de edad "<<nombre[j]<<endl;
    
    }
}
}
//ordenacion
// (burbuja)es un sencillo algoritmo de ordenacion que recorre un arreglo y compara elementos adyacentes, intercambiandolos si estan en el orden incorrecto. Este proceso se repite hasta que el arreglo este completamente ordenado.
#include <iostream>
using namespace std;

int main(){
    int numeros[] ={4,1,2,3,5};
    int i,j,aux;

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(numeros[j]>numeros[j+1]){
                aux=numeros[j];
                numeros[j]=numeros[j+1];
                numeros[j+1]=aux;
            }
        }
    }
    cout<<"orden ascendente: ";
    for(int i=0;i<5;i++){
        cout<<numeros[i]<<" ";
    }
    cout<<"orden descente: ";
    for(int i=4;i>=0;i--){
        cout<<numeros[i]<<" ";
    }
}

//(inserccion) es un algoritmo de ordenacion que construye una secuencia ordenada de elementos, tomando uno a uno los elementos del arreglo original y colocandolos en la posicion correcta dentro de la secuencia ordenada.
#include <iostream>
using namespace std;
int main(){
    int numeros[] ={4,2,3,1,5};
    int i,pos,aux;  

    for(int i=1;i<5;i++){
        aux=numeros[i];
        pos=i;
        while((pos>0)&&(numeros[pos-1]>aux)){
            numeros[pos]=numeros[pos-1];
            pos--;
        }
        numeros[pos]=aux;
    }
    cout<<"orden ascendente: ";
    for(int i=0;i<5;i++){
        cout<<numeros[i]<<" ";
    }
    cout<<"orden descente: ";
    for(int i=4;i>=0;i--){
        cout<<numeros[i]<<" ";
    }
}
//(seleccion) es un algoritmo de ordenacion que divide el arreglo en dos partes: una parte ordenada y otra desordenada. En cada iteracion, selecciona el elemento mas pequeño (o mas grande, dependiendo del orden deseado) de la parte desordenada y lo intercambia con el primer elemento de esa parte, expandiendo asi la parte ordenada.
#include <iostream>
using namespace std;
int main(){
    int numeros[]={3,2,1,5,4};
    int i,j,menor,aux;
    for(int i=0;i<5;i++){
        menor=i;
        for(int j=i+1;j<5;j++){
            if(numeros[j]<numeros[menor]){
                menor=j;
            }
        }
        aux=numeros[i];
        numeros[i]=numeros[menor];
        numeros[menor]=aux;
    }
    cout<<"orden ascendente: ";
    for(int i=0;i<5;i++){
        cout<<numeros[i]<<" ";
    }
    cout<<"orden descente: ";
    for(int i=4;i>=0;i--){
        cout<<numeros[i]<<" ";
    }
}
//(busqueda)
//(secuencial) es un algoritmo de busqueda que recorre un arreglo elemento por elemento, comparando cada elemento con el valor buscado hasta encontrar una coincidencia o llegar al final del arreglo.
#include <iostream>
using namespace std;
int main(){
    int numeros[]={1,2,3,4,5};
    int i,valor,bandera=0;
    cout<<"ingresa un numero a buscar: ";
    cin>>valor;
    for(int i=0;i<5;i++){
        if(numeros[i]==valor){
            bandera=1;
            break;
        }
    }
    if(bandera==1){
        cout<<"el numero fue encontrado"<<endl;
    }else{
        cout<<"el numero no fue encontrado"<<endl;
    }
}
//(binaria) es un algoritmo de busqueda que se utiliza en arreglos ordenados. Divide repetidamente el rango de busqueda a la mitad, comparando el valor buscado con el elemento central del rango. Si el valor buscado es igual al elemento central, la busqueda termina. Si es menor, la busqueda continua en la mitad inferior; si es mayor, en la mitad superior. Este proceso se repite hasta encontrar el valor o determinar que no esta presente en el arreglo.
#include <iostream>
using namespace std;
int main(){
    int numeros[]={1,2,3,4,5};
    int i,valor,inicio=0,fin=4,medio,bandera=0;
    cout<<"ingresa un numero a buscar: ";
    cin>>valor;
    while(inicio<=fin){
        medio=(inicio+fin)/2;
        if(numeros[medio]==valor){
            bandera=1;
            break;
        }else if(numeros[medio]<valor){
            inicio=medio+1;
        }else{
            fin=medio-1;
        }
    }
    if(bandera==1){
        cout<<"el numero fue encontrado"<<endl;
    }else{
        cout<<"el numero no fue encontrado"<<endl;
    }
}

// (funciones) es un bloque de codigo que realiza una tarea especifica y puede ser reutilizado en diferentes partes del programa. Las funciones pueden recibir parametros de entrada y devolver valores de salida.
int suma(int a, int b);
int main(){
    int n1, n2, resultado, numax, mayor;
    cout<<"ingresa dos numeros: ";
    cin>>n1>>n2;

   mayor = encontrarmayor(n1,n2);
   cout<<"el numero mayor es: "<<mayor<<endl;
    getch();
    return 0;
}
int encontrarmayor(int a, int b){
    if(a>b){
        numax = a;
        return a;
    }else{
        nummax=x;
        return b;
    }
}

int suma(){
/operacion
}
int main(){
suma= suma();

if(a > b){
    return a;
}
cout<<"el resultado de la suma es: "<<suma<<endl;
}
//sollicitando datos pero no indicando operaciones.
void saludar() {
    cout << "Hola!" << endl;
}



//ejemplo de fucion con vector
#include <iostream>
using namespace std;

void leervector(int vec[],int elementos);
int a[5];

int main(){
    leervector(a,5);
    return 0;
}
void leervector(int vec[],int elementos){
    for(int i=0;i<elementos;i++){
        cout<<"ingresa un numero: "<<i<<endl;
        cin>>vec[i];
    }
}

/*ejercicio: Desarrollar un programa que permita cargar 5nombres de personas y sus edades respectivas, luego de
realizar la carga por teclado de todos los datos, imprimir losnombres de las personas mayores de edad (mayores o iguales
a 18).Arreglos Paralelos*/

#include <iostream>
using namespace std;

int imprimir(string nombre[], int edad[]);
int main(){

	int i[3]={1,2,3};
	string nombre[3];
	int edad[3];
	cout<<"\n-- lista de personas --\n";
	for(int j=0;j<3;j++){
		cout<<"Ingresa tu nombre:"<<j<<endl;
		cin>>nombre[j];
		
		cout<<nombre[j]<<" Ingresa tu edad: "<<endl;
		cin>>edad[j];
		
		if(edad[j]>=18){
			cout<<"eres mayor de edad "<<nombre[j]<<endl;
		}else{ 
		cout<<"eres menor de edad "<<nombre[j]<<endl;
        }
	}
	imprimir(nombre,edad);
}
int imprimir(string nombre[], int edad[]){
	cout<< "\n--- Lista de personas---\n";
	for(int B=0;B<3;B++){
	cout<<"nombre de la persona: "<< nombre[B]<<" y su edad: "<<edad[B]<<endl;	
	}
	return 0;
}
	



