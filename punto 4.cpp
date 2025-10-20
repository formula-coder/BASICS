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
int diferencia(int A[],int B[],int dif[]);
int main(){
	int a[5]={1,2,3,4,5};
	int valor1[5];
	int b[5]={1,2,3,4,5};
	int valor2[5];
	int rta[10];
	int rta2[5];
	int rta3[5];
	int total;
	int total2;
	int total3;
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
	
	cout<<"Resultado de la diferencia A - B:"<< endl;
	total3=diferencia(valor1, valor2, rta3);
	cout<<total3<<endl;
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
	if(A[a] == B[b]){
	inter[k]=A[a];
	k++;
	break;
	}
}
}	
for(int i = 0; i < 5; i++){
cout <<i + 1<<".- "<<inter[i]<<endl;
    }
    return k;
}

int diferencia(int A[],int B[],int dif[]){
int k=0;
for(int a=0;a<5;a++){
	 bool esta = false;
for(int b=0;b<5;b++){
	   if (A[a] == B[b]) {
         	esta = true; // si está en B, no lo agregamos
            break;
}
}
if (!esta) { 
            dif[k] = A[a]; // ? agregar solo si no está en B
            k++;
}
}
  for (int i = 0; i < 5; i++) {
        cout << i++ << ".- " << dif[i] << endl;
    }

    return k;
}


