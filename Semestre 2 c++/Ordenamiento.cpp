#include <iostream>
#include <time.h>
#include <conio.h>
#include"Ordenamiento parte 2.h"

using namespace std;

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