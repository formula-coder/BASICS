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
cout<<"multiplicación de matrices"<<endl;
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
