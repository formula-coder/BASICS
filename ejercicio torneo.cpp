#include <iostream>
#include <stdio.h>
#include<string>
#include <iomanip>
using namespace std;

int buscar(string facultades[],string deportes[],int resultados[][100],int teams,int sport);
int deporte(string facultades[],string deportes[],int resultados[][100],int teams, int sport);
int campeones(string facultades[],string deportes[],int resultados[][100],int teams, int sport);
int search(string facultades[],string deportes[],int resultados[][100],int teams, int sport);

int main(){
int resultados[100][100];
int equipos,sports;
string facultades[100];
string deportes[100];
cout<<"digite cuantas facultades van a participar en la copa navideña:";
cin>>equipos;

cout<<"digite cuantos deportes se van a jugar:";
cin>>sports;

cin.ignore();
    for (int i = 0; i < equipos; i++) {
        cout << "Digite el nombre de la facultad " << i + 1 << ": ";
        getline(cin, facultades[i]);
        cout<<endl;
    }

    for (int j = 0; j < sports; j++) {
        cout << "Digite el nombre del deporte " << j + 1 << ": ";
        getline(cin, deportes[j]);
        cout<<endl;
    }
cout<<"\n--- Ingrese los puntajes obtenidos ---\n";
for(int i=0;i<equipos;i++){
	for(int j=0;j<sports;j++){
		cout<< facultades[i]<< " en "<<deportes[j]<<":";
		cin>> resultados[i][j];
	}
	cout<<"\n";
}

cout<<"\n---Tabla de resultados---\n";
cout<<left << setw(15) << "FACULTAD";
for(int j=0;j<sports;j++){
	cout<< setw(12)<<deportes[j];
}
  for (int i = 0; i < equipos; i++) {
        cout<< left << setw(15)<<facultades[i];
        for (int j = 0; j < sports; j++) {
            cout<< setw(12) <<resultados[i][j];
        }
        cout << endl;
    }
    buscar(facultades,deportes,resultados,equipos,sports);
    deporte(facultades,deportes,resultados,equipos,sports);
    campeones(facultades,deportes,resultados,equipos,sports);
    search(facultades,deportes,resultados,equipos,sports);
}

int buscar(string facultades[],string deportes[],int resultados[][100],int teams,int sport){
string name;
int pos=-1;
int mejor = resultados[pos][0];
int peor = resultados[pos][0];
string mejorDep = deportes[0];
string peorDep = deportes[0];
cout<<"ingrese el nombre de la facultad para saber sus resulatdos:";
cin>>name;


for(int k=0;k<teams;k++){
	if(facultades[k]==name){
		pos=k;
		break;
	}
}
	if(pos==-1){
		cout<<"la  facultad no ha sido encontrada :(";
	}
	cout<<"resultados de "<<facultades[pos]<<":\n";
	for (int j = 0; j < sport; j++) {
		        if (resultados[pos][j] > mejor) {
            mejor = resultados[pos][j];
            mejorDep = deportes[j];
        }
        if (resultados[pos][j] < peor) {
            peor = resultados[pos][j];
            peorDep = deportes[j];
        }
    }
    for (int o=0;o<sport;o++){
    	cout<<o <<". "<<deportes[o]<<" y su puntaje fue:"<<resultados[pos][o]<<endl;
	}
cout << "\n Mejor desempeño: " << mejorDep << " (" << mejor << " puntos)" << endl;
cout << "Peor desempeño: " << peorDep << " (" << peor << " puntos)" << endl;
}

int deporte(string facultades[],string deportes[],int resultados[][100],int teams, int sport){
	string game;
	int posx=-1;
	int mejorf=resultados[posx][0];
	int peorf=resultados[posx][0];
	string bestf;
	string worstf;
	cout<<"ingrese el nombre del deporte para saber las posiciones de la facultades en dicho deporte: "<<endl;
	cin>>game;
	
	for(int u=0;u<sport;u++){
		if(deportes[u]==game){
			posx=u;
			break;
		}
	}
	if(posx==-1){
		cout<<"el deporte no ha sido encontrado :("<<endl;
	}
	cout<<"resultados de las facultades en el deporte"<<deportes[posx]<<":\n";
		for (int j = 0; j <teams; j++) {
		        if (resultados[posx][j] > mejorf) {
            mejorf = resultados[posx][j];
            bestf = deportes[j];
        }
        if (resultados[posx][j] < peorf) {
            peorf= resultados[posx][j];
            worstf = deportes[j];
        }
    }
     for (int o=0;o<teams;o++){
    	cout<<o <<". "<<facultades[o]<<"y su puntaje en el deporte fue:"<<resultados[posx][o]<<endl;
cout << "\n Mejor desempeño: " << bestf<< " (" << mejorf << " puntos)" << endl;
cout << "Peor desempeño: " << worstf<< " (" << peorf << " puntos)" << endl;
}
}

int campeones(string facultades[],string deportes[],int resultados[][100],int teams, int sport){
int mayor;
string winner;

cout<<"campeonas en cada deporte:"<<endl;
for(int p=0;p<sport;p++){
	mayor=resultados[0][p];
 	winner = facultades[0];
	for(int g=0;g<teams;g++){
	if(resultados[g][p]>mayor){
		mayor= resultados[g][p];
		winner=facultades[g];
	}
	}
cout<<"la mejor facultad en el deporte: "<<deportes[p]<<" ha sido campeon con:"<<mayor<<" puntos."<<endl;
}	
}

int search(string facultades[],string deportes[],int resultados[][100],int teams, int sport){
	int posc=-1;
	string name;
	cout<<"ingrese un valor para saber si esta determinada psoición "<<endl;
	cin>>name;
	for(int f=0;f<teams;f++){
	if(facultades[f]==name){
		posc=f;
		break;
}
	}
	if(posc!=-1 ){
	cout<<facultades[posc]<<"esta en la posición: "<<posc<<endl;
}
else{
	cout<<"no se encontro nignuna posición :("<<endl;
}
}



