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




