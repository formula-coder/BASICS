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
cout<<"en los meses:"<<endl;
 for (int i = 0; i < 12; i++) {
        if (mes[i] == mayor) {
		cout << (i + 1)<<" "<<endl;
		}
    }
cout<<"La minima cantidad de toneladas son: ";
min =minimo(mes,12);
cout<<min<<endl;
cout<<"en los meses:"<<endl;
for (int i = 0; i < 12; i++) {
        if (mes[i] == menor) {
		cout<<(i + 1)<<" "<<endl;
		}
    }

cout << "Meses con cosecha superior al promedio: ";
sup= superior(mes,12,media);
cout<<sup<<endl;

cout << "Mes con cosecha inferior al promedio: ";
inf=inferior(mes,12,media);
cout<<inf<<endl;
return 0;
}

float promedio(int mes2[],int n){
int suma=0;	
for(int i =0;i<n;i++){
	suma += mes2[i];
}
cout<<suma/n;
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
}
int inferior(int mes2[], int n,int medias){
int inf =0;
int media=0;
for (int i=0;i<n;i++){
	if(mes2[i]<media){
		inf++;
	}
}
}

