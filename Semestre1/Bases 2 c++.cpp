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

/*2. En un arreglo unidimensional se ha almacenado el número total de toneladas de
cereales cosechadas durante cada mes del año. Elabore un programa que
proporcione la siguiente información:
a.- Promedio anual de toneladas cosechadas.
b.- Cuántos meses tuvieron una cosecha superior al promedio anual?
c.- Cuántos meses tuvieron una cosecha inferior al promedio anual?
d.- Cuál fue el mes en el que se produjeron mayor número de toneladas?*/

#include<iostream>
#include<stdio.h>

using namespace std;

float promedio(int mes2[], int n);
int maximo(int mes2[],int n);
int minimo(int mes2[], int n);
int superior(int mes2[], int n, int medias);
int inferior(int mes2[], int n, int medias);
int main(){
	int media=0;
	int max=0;
	int min=0;
	int mes[12];
	int sup=0;
	int inf=0;
	int mayor=0;
	int menor=0;
	cout<<"========================================"<<endl;
	cout<<"Toneladas de cereales anuales cosechadas"<<endl;
	cout<<"========================================"<<endl;
	
for(int a=0;a<12;a++){
	cout<<"ingresa  la cantidad de toneladas en el mes "<<a<<":"<<endl;
	cin>>mes[a];
}	
cout<<"El promedio de anual de las toneladas cosechas es: ";
media=promedio(mes,12);
cout<<media<<endl;

cout<<"La maxima cantidad de toneladas son: ";
max= maximo(mes,12);
cout<<max<<endl;

cout<<"La minima cantidad de toneladas son: ";
min =minimo(mes,12);
cout<<min<<endl;

sup= superior(mes,12,media);
cout << "Meses con cosecha superior al promedio: "<<endl;
    for (int i = 0; i < 12; i++) {
        if (mes[i]>media) cout << (i + 1) << " ";
    }
    cout<<endl;
inf=inferior(mes,12,media);
cout << "Meses con cosecha inferior al promedio: "<<endl;
    for (int i = 0; i < 12; i++) {
        if (mes[i]<media) cout << (i + 1) << " ";
    }
return 0;
}

float promedio(int mes2[],int n){
int suma=0;	
for(int i =0;i<n;i++){
	suma += mes2[i];
}
cout<<suma/n;
return (float)suma / n;
}

int maximo(int mes2[],int n){
	int valormax=0;
	valormax=mes2[0];
	for(int i=0;i<n;i++){
		if (valormax<mes2[i]){
			valormax=mes2[i];
		}
	}
	return valormax;
}
int minimo(int mes2[],int n){
	int valormin=0;
		valormin=mes2[0];
	for(int i=0;i<n;i++){
		if (valormin>mes2[i]){
			valormin=mes2[i];
}
}
return valormin;
}

int superior(int mes2[], int n, int medias){
int sup =0;
int media=0;
for(int i=0;i<n;i++){
	if (mes2[i]>media){
		sup++;
	}
	}
	return sup;
}
int inferior(int mes2[], int n,int medias){
int inf =0;
int media=0;
for (int i=0;i<n;i++){
	if(mes2[i]<media){
		inf++;
	}
}
	return inf;
}
/*1. Elabore un programa, que lea un vector ordenado con números enteros
(posiblemente repetidos) y dé como resultado un nuevo vector con números enteros,
pero sin repeticiones. */

#include<iostream>
#include<stdio.h>

using namespace std;
int duplicado1(int a[],int c[],int n);
int main(){
	int op1=0;
	int n=0;
cout<<"Ingresa el tamaño del arreglo: "<<endl;
cin>>n;
int*n3= new int [n];
int*n1= new int [n];

for(int a=0;a<n;a++){
	cout<<"Ingrese el valor "<<a<<" del primer arreglo:"<<endl;
	cin>>n1[a];
}

op1=duplicado1(n1,n3,n);
cout<<"El vector arrreglado :) "<<endl;
for(int i=0;i<op1;i++){
	cout<<n3[i];
}
cout<<endl;
}

int duplicado1(int a[],int c[],int n){
	int j=0;
	c[j]=a[0];
	for(int i =1;i<n;i++){
		if(a[i]!=c[j]) {
			j++;
			c[j]=a[i];
		}
	}
	return j+1;
}
/*3. Elaborar un programa que lea dos arreglos de igual tamaño y forme un tercer
arreglo mediante el producto de los elementos de los dos arreglos, tomados en orden
inverso, es decir, productos del primer elemento del primer arreglo con el último del
segundo; del segundo del primer arreglo con el penúltimo del segundo arreglo; hasta
llegar al último del primer arreglo con el primero del segundo arreglo. Imprimir el
arreglo creado. Cree una función para capturar los arreglos y otra función para formar
el tercer arreglo. El tercer arreglo formado debe imprimirse en el programa principal.*/

#include<iostream>
#include<stdio.h>

using namespace std;

int tercero(int a[], int b[],int c[],int n);
int captura(int a[],int b[],int n);

int main(){
	int n=0;
	int inverso=0;
	int fijado=0;
	cout<<"Ingresa el tamaño del arreglo: ";
	cin>> n;
	int*vector1= new int[n];
	int*vector2= new int[n];
	int*vector3= new int[n];
	fijado=captura(vector1,vector2,n);
	cout<<fijado;
	
	cout<<"el inverso de estos arreglos es: ";
 	tercero(vector1,vector2,vector3,n);
    for (int i = 0; i < n; i++) {
        cout << vector3[i]<<endl;
    }
	return 0;
} 

int tercero(int a[],int b[],int c[],int n){
	for	(int i=0;i<n/2;i++){
		c[i] = a[i] * b[n - 1 - i];
	}
}

int captura(int a[],int b[],int n){
	for (int i =0;i<n;i++){
		cout<<"Ingresa el numero "<<i<<" del primer arreglo: ";
		cin>>a[i];
	}
	for (int i=0;i<n;i++){
		cout<<"Ingresa el numero "<<i<<" del segundo arreglo: ";
		cin>>b[i];
	}
}
/*4. Se tienen dos arreglos A y B de m elementos. Partiendo de los dos arreglos,
elaborar un programa que debe imprimir el arreglo creado para cada caso.
1. Debe crear un arreglo con la unión de los elementos de los dos arreglos
2. Debe crear un arreglo con la intersección de los dos arreglos
3. Debe crear un arreglo con la diferencia A-B. */

#include<iostream>
#include<stdio.h>
using namespace std;

int unionarreglo(int A[], int B[], int anion[]);
int interseccion(int A[],int B[],int inter[]);

int main(){
	int a[5]={1,2,3,4,5};
	int valor1[5];
	int b[5]={1,2,3,4,5};
	int valor2[5];
	int rta[10];
	int rta2[5];
	int total;
	int total2;
	cout<<"ingrese el primer arreglo"<<endl;
	for(int a=0;a<5;a++){
		cout<<"Ingrese el valor "<<a<<":"<<endl;
		cin>>valor1[a];
	}
	cout<<"ingrese el segundo arreglo"<<endl;
	for(int b=0;b<5;b++){
		cout<<"ingresa el valor "<<b<<":"<<endl;
		cin>>valor2[b];
	}
	cout<<"el resultado de la union fue:"<<endl;
	total= unionarreglo(valor1,valor2,rta);
	cout<<total<<endl;
	cout<<"El resultado de la interseccion fue:"<<endl;
	total2=interseccion(valor1,valor2,rta2);
	cout<<total2<<endl;
}

int unionarreglo(int A[], int B[], int anion[]){


for(int i =0; i < 10;i++){
	if(i<5){
		anion[i]=A[i];
	}
	else if(i>=5){
		anion[i] =B[i-5];
	}
}
for(int i=0; i < 10;i++){
	cout<<i+1<<".-"<<anion[i]<<endl;
}
}

int interseccion(int A[], int B[],int inter[]){
int k=0;
for(int a=0; a < 5;a++){
for(int b=0;b < 5;b++){
	if(A[a]==B[b]){
	inter[k]=A[a];
	k++;
	break;
	}
}
}	
for(int i = 0; i < 5; i++){
cout <<i + 1<<".- "<<inter[i]<<endl;
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
//matrices es un arreglo bidimensional que se utiliza para almacenar datos en filas y columnas.
#include <iostream>
using namespace std;
int main(){
    int matriz[3][3];
    //llenar la matriz
    cout<<"ingresa los valores de la matriz: "<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<"valor para la posicion ["<<i<<"]["<<j<<"]: ";
            cin>>matriz[i][j];
        }
    }
    //imprimir la matriz
    cout<<"\nLa matriz ingresada es: "<<endl;
    for(int u=0;u<3;u++){
        for(int e=0;e<3;e++){
           cout<<matriz[u][e]<<" ";
        }
        cout<<endl;
    }
}
//multiplicacion de matrices.
#include <iostream>
#include <vector>
using namespace std;
int calculo(int matriz[][100],int matriz2[][100],int columna, int fila, int columna2, int fila2,int resultado[][100]);
int main() {
    int fila;
    int columna;
    int fila2;
    int columna2;
    int resultado[100][100];
cout<<"multiplicaci�n de matrices"<<endl;
	cout << "Ingresa el valor de la fila: " <<endl;
    cin >> fila;
    cout <<"Ingresa el valor de la columna: " <<endl;
    cin >> columna;

  	cout << "Ingresa el valor de la fila 2: " <<endl;
    cin >> fila2;
    cout << "Ingresa el valor de la columna 2: " <<endl;
    cin >> columna2;

int matriz[100][100];
int matriz2[100][100];
    // Llenar la matriz
    cout << "\nIngresa los valores de la matriz:" <<endl;
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            cout << "Valor para la posicion [" << i << "][" << j << "]: ";
            cin >> matriz[i][j]; // Usamos cin para enteros
        }
    }
       cout << "\nIngresa los valores de la matriz 2:" <<endl;
    for (int z= 0; z < fila2; z++) {
        for (int x = 0; x < columna2; x++) {
            cout << "Valor para la posicion [" << z << "][" << x<< "]: ";
            cin >> matriz2[z][x]; // Usamos cin para enteros
        }
    }


    // Imprimir la matriz
    cout << "\nLa matriz ingresada es:" << endl;
    for (int u = 0; u < fila; u++) {
        for (int e= 0; e< columna; e++) {
           cout << matriz[u][e] << " ";
        }
        cout<<endl;
    }
        cout << "\nLa matriz 2 ingresada es:" << endl;
    for (int q= 0; q < fila2; q++) {
        for (int k= 0; k< columna2; k++) {
           cout << matriz2[q][k] << " ";
        }
        cout<<endl;
    }
calculo(matriz,matriz2,columna,fila, columna2,fila2,resultado);

    return 0;
}
int calculo(int matriz[][100],int matriz2[][100],int columna, int fila, int columna2, int fila2,int resultado[][100]){
	if (columna!=fila2){
		cout<<"la matriz no se puede multiplicar :("<<endl;
	}
	else{
		cout<<"la matriz se puede multiplicar :)"<<endl;
	for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna2; j++) {
            for (int k = 0; k < columna; k++) {
                resultado[i][j] += matriz[i][k] * matriz2[k][j];
		}
}
	}
		for(int o=0;o<fila;o++){
			for(int r=0;r<columna2;r++){
				cout << resultado[o][r] << " ";
        }
        cout << endl;
			}
}
}

//estructuras

#include <iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;
struct Persona {
char nombre[20];
int edad;

}
persona1;
persona2;

int main(){
   cout<<"Ingresa el nombre de la primera persona: "<<endl;
    cin.getline(persona1.nombre,20);
    cout<<"Ingresa la edad de la primera persona: "<<endl;
    cin>>persona1.edad;

    cout<<"Ingresa el nombre de la segunda persona: "<<endl;
    cin.getline(persona2.nombre,20);
    cout<<"Ingresa la edad de la segunda persona: "<<endl;
    cin>>persona2.edad;

    cout<<"Datos de la primera persona: "<<endl;
    cout<<"Nombre: "<<persona1.nombre<<endl;
    cout<<"Edad: "<<persona1.edad<<endl;
    cout<<"Datos de la segunda persona: "<<endl;
    cout<<"Nombre: "<<persona2.nombre<<endl;
    cout<<"Edad: "<<persona2.edad<<endl;

    getch();

    return 0;
}


#include <iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;

struct libro {
    char titulo[30];
    char autor[20];
    char editorial[20];
    int anio[20];
} libro;
int main(){
    cout << "Ingresa la ccantidad de libros a registrar: ";
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        fflsuh(stdin);
    cout<<"Ingresa el titulo del libro: "<<endl;
    cin.getline(libro.titulo,30);
    cout<<"Ingresa el autor del libro: "<<endl;
    cin.getline(libro.autor,20);
    cout<<"Ingresa la editorial del libro: "<<endl;
    cin.getline(libro.editorial,20);
    cout<<"Ingresa el anio de publicacion del libro: "<<endl;
    cin.getline(libro.anio,20);
    cout<<"\nDatos del libro registrado: "<<endl;
    cout<<"Titulo: "<<libro.titulo<<endl;
    cout<<"Autor: "<<libro.autor<<endl;
    cout<<"Editorial: "<<libro.editorial<<endl;
    cout<<"Anio de publicacion: "<<libro.anio<<endl;
    break;
    }
}

#include<iostream>
#include<stdio.h>

using namespace std;

struct number{
	string nombre;
	string numero;	
};
void captura(number contactos[], int n);
void impresion(number contactos[],int n);
int main (){
	int n=0;
cout<<"ingresa la cantidad de personas que se van a capturar:"<<endl;
cin>>n;
	number contactos[n];
captura(contactos,n);
impresion(contactos,n);
}

void captura(number contactos[], int n){
	for(int i=0;i<n;i++){
		cout<<"Contacto"<<i<<endl;
		cout<<"ingresa tu nombre: "<<endl;
		getline(cin,contactos[i].nombre);
		cout<<"ingresa tu numero de celular: "<<endl;
		getline(cin,contactos[i].numero);
	}
}

void impresion(number contactos[],int n){
	cout<<"Contactos registrados"<<endl;
	for(int i=0;i<n;i++){
		cout<<"nombres registrados: "<<contactos[i].nombre<<endl;
	}
	for (int j=0;j<n;j++){
		cout<<"numeros registrados: "<<contactos[i].numero<<endl;
	}
}

//estructuras anidadas
#include <iostream>
#include<stdio.h>
using namespace std;

struct direccion{
    char calle[30],numero[10],colonia[20],municipio[20];

};
struct persona{
    char nombre[20],apellido[20];
    int edad;
    struct direccion direccionPersona;
}persona[2];

main(){
    for(int i=0;i<2;i++){
        cout<<"Ingresa el nombre: "<<endl;
        cin.getline(persona[i].nombre,20);
        cout<<"Ingresa el apellido: "<<endl;
        cin.getline(persona[i].apellido,20);
        cout<<"Ingresa la edad: "<<endl;
        cin>>persona[i].edad;
        fflush(stdin);
        cout<<"Ingresa la calle: "<<endl;
        cin.getline(persona[i].direccionPersona.calle,30);
        cout<<"Ingresa el numero: "<<endl;
        cin.getline(persona[i].direccionPersona.numero,10);
        cout<<"Ingresa la colonia: "<<endl;
        cin.getline(persona[i].direccionPersona.colonia,20);
        cout<<"Ingresa el municipio: "<<endl;
        cin.getline(persona[i].direccionPersona.municipio,20);
    }
    for(int i=0;i<2;i++){
        cout<<"\nDatos de la persona "<<i+1<<endl;
        cout<<"Nombre: "<<persona[i].nombre<<endl;
        cout<<"Apellido: "<<persona[i].apellido<<endl;
        cout<<"Edad: "<<persona[i].edad<<endl;
        cout<<"Calle: "<<persona[i].direccionPersona.calle<<endl;
        cout<<"Numero: "<<persona[i].direccionPersona.numero<<endl;
        cout<<"Colonia: "<<persona[i].direccionPersona.colonia<<endl;
        cout<<"Municipio: "<<persona[i].direccionPersona.municipio<<endl;
    }
}
//archivos
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void escribirArchivo();
void leerArchivo();

int main(){
    escribirArchivo();
    leerArchivo();
    return 0;
}
void escribirArchivo(){
   string texto;
   string texto2;
    ofstream archivo;
cout <<"Escribiendo el nombre del archivo..."<<endl;
getline(cin, texto);
    archivo.open(texto.c_str(), ios::out);// Darle un nombre al archivo escribiendolo
    
    /*archivo.open("d://prueba//datos.txt",ios::out);*/// darle un nombre al archivo ya puesto en una direccion fija
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }

    archivo<<"Hola, este es un archivo de texto creado con C++."<<endl;
    archivo<<"Esta es la segunda linea del archivo."<<endl;//contenido del archivo ya puesto 
    archivo.close();// cerrar el archivo

    cout <<"Digite el texto del archivo: "<<endl;
    getline(cin,texto2);
    archivo<<texto2;//contenido del archivo escrito por el usuario

    archivo.close();// cerrar el archivo
}

void leerArchivo(){
    ifstream archivo;
    string texto;
Archivo.open("d://prueba//datos.txt", ios::in);//abrir el archivo para leerlo
if (archivo.fail()){
    cout<< "No se pudo abrir el archivo"<<endl;
    exit (1);
}
while(!archivo.eof()){//mientras no sea el final del archivo que lo siga  leyendo 
    getline(archivo,texto);
    cout<<texto<<endl;
}
archivo. close();//cerrar el archivo
}

//ejercicio de el juego 

void guardarTorneo(const vector<jugador>& jugadores, const string & nombreArchivo){
    string guardado;
    ofstream archivo(guardado, ios::out);
    int players = jugadores.size();
    cout<<"Ingrese el nombre del archivo donde se va a guardar el torneo"<<endl;
    cin.ignore();
    getline(cin, guardado);
    archivo.open(guardado.c_str(), ios::out);
    if (guardado.find(".txt")==string::npos){
        guardado += ".txt";
    }
    if (archivo.fail()){
        cout<<"No se puedo abrir el archivo del torneo"<<endl;
        exit(1);
    }
    archivo<<"Estadisticas del torneo"<<endl;
    archivo<<"Jugador     Jugados  Ganados  Empates  Perdidos  Puntos" << endl;
    archivo << "-------------------------------------------------------" << endl;
        for(int k = 0; k< players; k++) {
                            archivo << jugadores[k].nombre << "\t" 
                                 << jugadores[k].jugados << "\t" 
                                 << jugadores[k].ganados << "\t" 
                                 << jugadores[k].empates << "\t" 
                                 << jugadores[k].perdidos << "\t" 
                                 << jugadores[k].puntos << endl;
                                
}
archivo.close();
cout<<"Torneo guardado exitosamente!"<<endl;
}

void cargarTorneo(const vector<jugador>& jugadores, const string & nombreArchivo){
    ifstream archivo;
    string guardado;
    string texto;
    cout<<"Ingrese el nombre del archivo donde se va a cargar el torneo: "<<endl;
    cin.ignore();
    getline(cin, guardado);
    if (guardado.find(".txt") == string::npos){
        guardado += ".txt";
    }
    archivo.open(guardado.c_str(), ios::in);

    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo del juego."<<endl;
        exit(1);
    }
    cout<<"Contenido del torneo"<<guardado<<endl;
    while (getline(archivo, texto)){
        cout<<texto<<endl;
    }
    archivo.close();
cout<<"Torneo cargado exitosamente!"<<endl;
}
