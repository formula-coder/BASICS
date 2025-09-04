
#include <iostream>
using namespace std;

int main(){

    int i[5]={1,2,3,4,5};
    string nombre[5];
    int edad[5];
    
    for(int j=0;j<5;j++){
        cout<<"Ingrese el nombre de la persona "<<j<<endl;
        cin>>nombre[j];
        cout<<"Ingrese la edad de la persona "<<j<<endl;
        cin>>edad[j];
        
        
        if(edad[j]>=18){
		
        cout<<"eres mayor de edad "<<nombre[j]<<endl;
		}
        else{ 
		cout<<"eres menor de edad "<<nombre[j]<<endl;
    
    }
}
}