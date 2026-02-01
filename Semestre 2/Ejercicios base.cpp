#include<iostream>
#include<stdio.h>
using namespace std;

int  main(){
int opcion;
cout<<"Programa de agenda telefonica"<<endl;
cout<<"------------------------------"<<endl;
cout <<"Menu de opciones"<<endl;
cout <<"1.Agregar contactos"<<endl;
cout <<"2.Mostrar contactos"<<endl;
cout<<"3.Editar contactos"<<endl;
cout<<"4.Eliminar contactos"<<endl;
cout<<"5.Salir"<<endl;
cout<<"------------------------------"<<endl;
cout<<"Ingrese una opcion: ";
cin>>opcion;

switch (opcion){
case 1:{
    cout<<"se escogio agregar contactos"<<endl;

    break;
}
case 2:{
    cout<<"se escogio mostrar contactos"<<endl;

    break;
}
case 3:{
    cout<<"se escogio editar contactos"<<endl;

    break;
}
case 4:{
    cout<<"se escogio eliminar contactos"<<endl;

    break;
}
case 5:{
    cout<<"salir"<<endl;

    break;
}

default:{
    cout<<"opcion no valida,intente de nuevo"<<endl;
}
    break;
}
system("pause");
return 0;
}
