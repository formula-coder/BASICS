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

