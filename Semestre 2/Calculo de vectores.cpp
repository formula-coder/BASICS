#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Punto{
    
      int x;
      int y;
};

void cargarPuntos(Punto punto[], int &cantidadPuntos);
void mostrarPuntos(Punto punto[], int &cantidadPuntos);
void agregarPunto(Punto punto[], int &cantidadPuntos);
void eliminarPunto(Punto punto[], int &cantidadPuntos);
float calcularDistancia(int x1, int y1, int x2, int y2);
int main()
{
    
    Punto punto[50];
    int opcion;
    int cantidadPuntos=0;
    do {
        //menu 
        cout << "MENU" << endl;
        cout << "1. Cargar un punto." << endl;
        cout << "2. Mostrar todos los puntos." << endl;
        cout << "3. Agregar un punto." << endl;
        cout << "4. Eliminar un punto." << endl;
        cout << "5. Calcular distancia entre dos puntos" << endl;
        cout << "6. Salir del programa." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:{
                     cargarPuntos(punto,cantidadPuntos);
              
                break;
            }
            case 2:{
                     mostrarPuntos(punto, cantidadPuntos);
                    
                break;
            }
            case 3:{
                    agregarPunto(punto,cantidadPuntos);
                    
                break;
            }
            case 4:{
                    eliminarPunto(punto, cantidadPuntos);
                break;
            }
            case 5: {
                    int n, z;
                    cout<<"total de puntos: "<<cantidadPuntos<<endl;

                    for (int i=0; i<cantidadPuntos;i++){
                        cout<<"punto numero "<<i+1<<endl;
                        cout<<"coordenada x: "<<punto[i].x<<endl;
                        cout<<"coordenada y: "<<punto[i].y<<endl;
                        cout << "------------------------" << endl;
                    }
                    
                    cout<<"digite el numero de los puntos que desea calcular la distancia (1-"<<cantidadPuntos<<"): "<<endl;
                    cin>>n;
                    cin>>z;

                    // Convertir a indice basado en 0
                    n--; z--;
                    if(n < 0 || n >= cantidadPuntos || z < 0 || z >= cantidadPuntos){
                        cout << "Indices invalidos." << endl;
                        break;
                    }
                    
                    float res = calcularDistancia(punto[n].x, punto[n].y, punto[z].x, punto[z].y);
                    cout<<"la distancia entre los puntos es de "<<res<<" unidades."<<endl;
                break;
            }
            case 6:{
                     cout<<"salio del programaa.";
                break;
            }
            default:{
                cout << "Opcion no valida." << endl;
                break;
            }
        }
        
    } while(opcion != 6);  

    return 0;
}

void cargarPuntos(Punto punto[], int &cantidadPuntos){
    
    cout<<"digite la cantidad de puntos que quiere agregar: ";
    cin>>cantidadPuntos;
    
    if(cantidadPuntos < 0) cantidadPuntos = 0;
    if(cantidadPuntos > 50){
        cout << "Se ajusto a 50 puntos como maximo." << endl;
        cantidadPuntos = 50;
    }
     for( int i=0; i<cantidadPuntos;i++){
         cout<<"punto "<<i+1<<endl;
         cout<<" coordenada x: ";
         cin>>punto[i].x;
         cout<<"coordenada y: ";
         cin>>punto[i].y;
     }
}

void mostrarPuntos(Punto punto[], int &cantidadPuntos){
    
    cout<<"total de puntos: "<<cantidadPuntos<<endl;
    
    for (int i=0; i<cantidadPuntos;i++){
        
        cout<<"punto numero "<<i+1<<endl;
                cout<<"coordenada x: "<<punto[i].x<<endl;         //funcion para mostrar el vector de estructuras 
                cout<<"coordenada y: "<<punto[i].y<<endl;
        cout << "------------------------" << endl;
    }
}
void agregarPunto(Punto punto[], int &cantidadPuntos){
    
      int n;
      cout<<"actualmente tiene "<<cantidadPuntos<<" puntos"<<endl;
      cout<<"cuantos puntos desea agregar: ";
      cin>>n;
      
            if(cantidadPuntos + n > 50){
                    cout << "Se pueden agregar como maximo " << (50 - cantidadPuntos) << " puntos." << endl;
                    n = 50 - cantidadPuntos;
            }
            for (int i=cantidadPuntos; i<(cantidadPuntos+n);i++){
                cout<<"punto numero "<<i+1<<endl;
                cout<<"coordenada x: ";
                cin>>punto[i].x;                              //funcion para añadir un numero n de puntos
                cout<<"coordenada y: ";
                cin>>punto[i].y;
            }
            cantidadPuntos+=n;
    
}
void eliminarPunto(Punto punto[], int &cantidadPuntos){
    
    int posicion;      //el punto que se va a eliminar
    string opcion;
    
    if (cantidadPuntos == 0) {
        cout << "No hay puntos para eliminar." << endl;           //verificar que si hay puntos      
        return;
    }
    
    cout << "De los siguientes puntos, cual desea eliminar" << endl;
    
    for (int i = 0; i < cantidadPuntos; i++) {
        cout << "punto numero " <<i+1<< endl;
        cout << "coordenada x: " << punto[i].x << endl;
        cout << "coordenada y: " << punto[i].y << endl;            //mostrar en pantalla los puntos 
        cout << "------------------------" << endl;
    }
    
    cout << "Digite el numero del punto que desea eliminar (1-" << cantidadPuntos << "): ";
    cin >> posicion;                
    
    // Ver si la posicion es valida
    if (posicion < 1 || posicion > cantidadPuntos) {
        cout << "Posicion invalida." << endl;
        return;
    }
    
    // Preguntar si de verdad lo quiere eliminar 
    cout << "Esta seguro que desea eliminar el punto numero " << posicion<<"?"<<endl;
    cin >> opcion;
    
    if (opcion == "si" || opcion == "SI"|| opcion=="Si") {
        // Desplazar todos los puntos después de la posición eliminada
        int idx = posicion - 1;
        for (int i = idx; i < cantidadPuntos - 1; i++) {
            punto[i] = punto[i + 1];
        }
        
        cantidadPuntos--;
        cout << "El punto fue eliminado" << endl;
        cout << "Total de puntos actual: " << cantidadPuntos << endl;
    } else {
        cout << "Eliminacion cancelada." << endl;
    }
    

}

float calcularDistancia(int x1, int y1, int x2, int y2){
    float resultado;
    resultado = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return resultado;
}