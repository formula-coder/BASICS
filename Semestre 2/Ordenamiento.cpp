#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;


void ordenar (int **arrPunteros){

    for (int i = 0; i < 9; i++) {
        int imin = i;
        for (int j = i + 1; j < 10; j++) {
            if (**(arrPunteros + j) < **(arrPunteros + imin)) {
                imin = j;
            }
        }
        if (imin != i) {
            int *aux = *(arrPunteros + imin);
            *(arrPunteros + imin) = *(arrPunteros + i);
            *(arrPunteros + i) = aux;
        }
    }

}

int main(){


    srand(time(NULL));

    int * arrOriginal = new int [10];

    cout<<"Arreglo original"<<endl;
    for(int i=0; i<10;i++){
       *(arrOriginal + i)= rand() %100 +1;
        cout<<*(arrOriginal + i)<<" | ";
    }
    cout<<endl;
   int **arrPunteros = new int* [10];

   for(int i=0; i<10; i++){

      *(arrPunteros + i)= arrOriginal + i;

   }
cout<<"Arreglo ordenado"<<endl;
cout<<"\n";
    ordenar(arrPunteros);
    for(int i=0; i<10;i++){
        cout<<**(arrPunteros + i)<<" | ";
    }

getch();
}