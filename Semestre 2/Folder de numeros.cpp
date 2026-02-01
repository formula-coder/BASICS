#include<iostream>
#include <stdlib.h> 
#include <string>

using namespace std;
struct contacto{
    string nombre;
    string telefono;
};
void agregarcontacto( contacto agenda[], int& total);
void mostrarcontactos(int total, contacto agenda[]);
void editarcontacto(contacto agenda[], int total);
void eliminarcontacto(contacto agenda[], int& total);
int  main(){
contacto agenda[100];
int total=0;
int opcion;
while(true){
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
  if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada invalida Intente de nuevo. Debe ingresar una opcion valida."<<endl;
            continue;
            }
switch (opcion){
case 1:{
    cout<<"se escogio agregar contactos"<<endl;
    agregarcontacto(agenda, total);
} 
break;
case 2:{
    cout<<"se escogio mostrar contactos"<<endl;
    mostrarcontactos(total, agenda);
    cout<<endl;
    if (total==0){
        cout<<"No hay contactos en la agenda"<<endl;
    }
    cout<<endl;
    break;
}
case 3:{
    cout<<"se escogio editar contactos"<<endl;
    editarcontacto(agenda, total);
    break;
}
case 4:{
    cout<<"se escogio eliminar contactos"<<endl;
    eliminarcontacto(agenda, total);
    break;
}
case 5:{
    cout<<"salir"<<endl;
    exit(0);
}

default:{
    cout<<"opcion no valida,intente de nuevo"<<endl;
}
    break;
}

}
return 0;
}

void agregarcontacto(contacto agenda[], int& total){
   int opcion2; 
    do{
    int n;  
    cout<<"Cuantos contactos desea agregar?( recuerde que solo puede agregar hasta 100 contactos en total): ";
    cin>>n;

     if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Entrada invalida Intente de nuevo. Debe ingresar una opcion valida."<<endl;
            continue;       
  }
    cin.ignore(1000,'\n');
    if(total + n > 100){
        cout<<"No puede agregar mas de 100 contactos, intente de nuevo"<<endl;
        continue;
    }
    for(int i=0;i<n;i++){
        cout<<"Ingrese el nombre del contacto: ";
        getline(cin, agenda[total].nombre);
        cout<<"Ingrese el telefono del contacto: ";
        getline(cin, agenda[total].telefono);
        total++;
    }
    cout<<endl;
    cout<<"Contactos agregados exitosamente"<<endl;
    cout<<endl;
    cout<<"Se han agregado "<<n<<" contactos a la agenda"<<endl;
    cout<<endl;
    cout<<"desea agregar mas contactos? 1.si 2.no: ";
    cin>>opcion2;
            if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            opcion2 = 2;
            cout<<"Entrada invalida Intente de nuevo. Debe ingresar una opcion valida."<<endl;
            }
}while(opcion2==1);
}
void mostrarcontactos(int total, contacto agenda[]){
    cout<<"Contactos en la agenda:"<<endl;
    for(int i=0;i<total;i++){
        cout<<"Contacto "<<i+1<<":"<<endl;
        cout<<"Nombre: "<<agenda[i].nombre<<endl;
        cout<<"Telefono: "<<agenda[i].telefono<<endl;
    }
}

void editarcontacto(contacto agenda[],int total){
    if(total==0){
    cout<<"No hay contactos para editar"<<endl;
    cout<<endl;
    cout<<"Agregue contactos primero"<<endl;
    cout<<endl;
    return;
    } else{
        cout<<"Contactos en la agenda:"<<endl;
    for(int i=0;i<total;i++){
        cout<<"Contacto "<<i+1<<":"<<endl;
        cout<<"Nombre: "<<agenda[i].nombre<<endl;
        cout<<"Telefono: "<<agenda[i].telefono<<endl;
    }
    int indice;
    cout<<"Ingrese el numero del contacto que desea editar (1 a "<<total<<"): ";
    cin>>indice;
    if(indice>total or indice<1){
        cout<<"Indice invalido"<<endl;
        return;
}
indice--;
cin.ignore();
cout<<"Ingrese el nuevo nombre del contacto: ";
getline(cin, agenda[indice].nombre);
cout<<"Ingrese el nuevo telefono del contacto: ";
getline(cin, agenda[indice].telefono);
cout<<"Contacto editado exitosamente"<<endl;
}
}

void eliminarcontacto(contacto agenda[], int& total){
int indice2;
    if (total==0){
    cout<<"No hay contactos para eliminar"<<endl;
    cout<<endl;
    cout<<"Agregue contactos primero"<<endl;
    cout<<endl;
    return;
    } else{
        cout<<"Contactos en la agenda:"<<endl;
    for(int i=0;i<total;i++){
        cout<<"Contacto "<<i+1<<":"<<endl;
        cout<<"Nombre: "<<agenda[i].nombre<<endl;
        cout<<"Telefono: "<<agenda[i].telefono<<endl;
    }
    cout<<"Ingrese el numero del contacto que desea eliminar (1 a "<<total<<"): ";
    cin>>indice2;

    if(indice2>total or indice2<1){
        cout<<"Indice invalido"<<endl;
        return;
    }
    indice2--;
    for(int i= indice2; i<total-1; i++){
      agenda[i]= agenda[i+1];
      
    }
    total--;
    cout<<"Contacto eliminado exitosamente"<<endl;
    cout<<endl;
    cout<<"Contactos restantes:"<<endl;
    for(int i=0;i<total;i++){
        cout<<"Contacto "<<i+1<<":"<<endl;
        cout<<"Nombre: "<<agenda[i].nombre<<endl;
        cout<<"Telefono: "<<agenda[i].telefono<<endl;
    }
}
}