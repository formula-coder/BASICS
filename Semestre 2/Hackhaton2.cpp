#include <iostream>
using namespace std;

int sumaMaxima(int *arreglo, int t, int n);

int main()
{
    int n, t;
    cout<<"Sumas sucesivas"<<endl;
    cout<<"hola, este programa calcula la suma maxima de t elementos consecutivos en un arreglo de n elementos"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"digite el numero de elementos del arreglo:"<<endl;
    cin>>n;
    cout<<"---------------------------------------------------"<<endl;
    
    int arreglo[n];
    
    for(int i=0; i<n; i++){
        cin>>arreglo[i];
    }
    cout <<"---------------------------------------------------"<<endl;
    cout<<"digite la cantidad de sumas que desea hacer: "<<endl;
    cin>>t;
    cout<<"---------------------------------------------------"<<endl;
    
    int resultado = sumaMaxima(arreglo, t, n);
    
    cout<<"el resultado es: "<<resultado;
    return 0;
}

int sumaMaxima(int *arreglo, int t, int n){
    int valor = 0;
    int *ptr = arreglo;
    
    if (n<=0 || t<=0)
        return 0;
    if (n==1 && t==1){
        for(int i=0; i<n; i++){
            valor = *ptr;
            ptr++;
        }
        return valor;
    }
    
    if (t>n)
        return -1;
    
    if (t < n){
        int sumaActual = 0;
        int maxSuma = 0;
        
        // Calculamos la suma de los primeros t elementos
        ptr = arreglo;
        for(int i=0; i<t; i++){
            sumaActual += *ptr;
            ptr++;
        }
        maxSuma = sumaActual;
        

        ptr = arreglo;
        for(int i=0; i<=n-t; i++){

            sumaActual = 0;
            for(int j=0; j<t; j++){
                sumaActual += *(ptr + i + j);
            }
            
            if(sumaActual > maxSuma){
                maxSuma = sumaActual;
            }
        }
        
        return maxSuma;
    }
    
    return 0;
}