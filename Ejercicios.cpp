#include <iostream>
#include <conio.h>
using namespace std;

 int n1, n2, resultado, numax, mayor, menor, nummin;

int suma(int a, int b);
int main(){
   int encontrarmayor(int a, int b);
   int encontrarmenor(int a, int b);
    cout<<"ingresa dos numeros: ";
    cin>>n1>>n2;

   mayor = encontrarmayor(n1,n2);
   cout<<"el numero mayor es: "<<mayor<<endl;
    getch();
    return 0;
    menor = encontrarmenor(n1,n2);
    cout<<"el numero menor es: "<<menor<<endl;
    getch();
    return 0;
}
int encontrarmayor(int a, int b){
int nummax;
int x;
    if(a>b){
        numax = a;
        return a;
    }else{
        numax=x;
        return b;
    }
}
int encontrarmenor(int a, int b){
    int nummin;
    int x;
    if(a<b){
        nummin = a;
        return a;
    }else{
        nummin=x;
        return b;
    }
}