//Tipos de datos en c++

#include<iostream>
#include<stdio.h>

using namesapce std;

int main(){
    int entero = 15;
	cout<< entero << " entero "<<;
}
float flotante  = 10.45;
cout<< flotante << " flotante"<<endL;

double mayor  = 3.1415
cout<< mayor<<" double"<< endl;

printf("%f,"mayor); printf("\n%c","double\n");
cout.preccision(16);
cout<< mayor << " double con precision" << endl;

    char caracter = 'a';
    cout << caracter << " caracter" << endl;

    string letras = "probando";
    cout << letras << " letras" << endl;

    string probando = "probando";
    cout << probando << endl;

    // Variables
    int numero = 10;
    float decimal = 3.14;
    char letra = 'A';
    string texto = "Hola, C++";
    int a = 8, b = 3;
    cout << "El resultado de la suma es: " << a + b << endl;

    int  n1, n2;
    cout << "Ingrese el primer numero: ";
    cin >> n1;
    cout << "Ingrese el segundo numero: ";
    cin >> n2;
    cout << "La suma de " << n1 << " y " << n2 << " es: " << n1 + n2 << endl;
 
    int base, altura, area;
    cout << "Ingrese la base del triángulo: ";
    cin >> base;
    cout << "Ingrese la altura del triángulo: ";
    cin >> altura;
    area = (base * altura) / 2;
    cout << "El área del triángulo es: " << area << endl;

    //Condicionales
    int numero;
    cout << "Ingrese un numero: ";
    cin >> numero;
    if (numero > 0) {
        cout <<" El numero es positivo" << endl;
    else if(numero < 0) {
        cout << "El numero es negativo" << endl;
    } else(numero == 0) {
        cout << "El numero es cero" << endl;
    }

    //Modulo 

    int numero;
    cout << "Ingrese un numero: ";
    cin >> numero;
    if (numero % 2 == 0) {
        cout << "El numero es par" << endl;
    } else {
        cout << "El numero es impar" << endl;
    }

    int horas, minutos, segundos;
    cout << "Ingrese las horas: ";
    cin >> horas;
    cout << "Ingrese los minutos: ";
    cin >> minutos;
    cout << "Ingrese los segundos: ";
    cin >> segundos;

    if (minutos >0 )
    {
        horas = horas + 1;
    }
    total = horas *3.50;
    cout <<"el total a pagar es: " << total << endl;

    //ciclos
    int i, numero, factorial = 1;
    cout << "Ingrese un numero: ";
    cin >> numero;

    for (i = 1; i <= numero; i++) {
        factorial *= i;
    }
    cout << "El factorial de " << numero << " es: " << factorial << endl;
    return 0;
}
