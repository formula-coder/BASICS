public class Basesjava{
    public static void main(String args[]){
        System.out.println("Hola Mundo");
    }
}

/* ============================================================
   TIPOS DE DATOS EN JAVA
   ============================================================ */
// Enteros: byte, short, int, long
// Decimales: float, double
// Otros: char, boolean, String

/* ============================================================
   LIBRERIAS COMUNES
   ============================================================ */
// java.util.Scanner - Lee datos por consola
// Uso: Scanner sc = new Scanner(System.in);
// Métodos: nextLine() (texto), nextInt() (entero), nextDouble() (decimal)

/* ============================================================
   CICLOS
   ============================================================ */
/* 
// CICLO FOR
for(int i=0; i<10; i++){
    System.out.println(i);
}

// CICLO WHILE
int i=0;
while(i<10){
    System.out.println(i);
    i++;
}

// CICLO DO-WHILE
int i = 0;
do{
    System.out.println(i);
    i--;
}while (i>=0);
*/

/* ============================================================
   VARIABLES Y TIPOS
   ============================================================ */
/*
// Declaración de variables
int numero = 0;
String nombre = "Juan"; // Nota: String con S mayúscula, no string

// Comparación de valores
numero == 9;              // Compara números
nombre.equals("Juan");    // Compara strings (NO usar == para strings)
// Importante: == compara referencias de objetos, equals() compara contenido
*/

/* ============================================================
   ARREGLOS
   ============================================================ */
/*
// Arreglo unidimensional
int[] numeros = new int[10];  // Array de 10 enteros

// Ejemplo de uso
numeros[0] = 5;               // Acceder por índice
numeros[1] = 10;

// Recorrer arreglo
for(int i=0; i < numeros.length; i++){
    System.out.println(numeros[i]);
}
*/

/* ============================================================
   MATRICES (Arreglos 2D)
   ============================================================ */
/*
// Declaración
int[][] numeros = new int[3][3];  // Matriz 3x3

// Llenar matriz con valores
int contador = 1;
for(int j=0; j < 3; j++){
    for(int i=0; i < 3; i++){
        numeros[j][i] = contador;
        contador++;
        System.out.print("[" + numeros[j][i] + "]");
    }
    System.out.println();  // Nueva línea después de cada fila
}
*/

/* ============================================================
   CLASES Y OBJETOS
   ============================================================ */
// Clase: plantilla para crear objetos.
// Objeto: instancia de una clase.
// Atributo: variable dentro de la clase.
// Método: función dentro de la clase.
// Constructor: método especial que se usa al crear el objeto.
// Visibilidad:
// - public: accesible desde cualquier clase.
// - private: accesible solo dentro de la misma clase.
// - protected: accesible en la misma clase, mismo paquete y clases hijas.
// - package/default: accesible solo dentro del mismo paquete.

/*
class Persona {
    private String nombre;
    private int edad;

    public Persona(String nombre, int edad) {
        this.nombre = nombre;
        this.edad = edad;
    }

    public void mostrarDatos() {
        System.out.println(nombre + " tiene " + edad + " años");
    }
}

Persona p1 = new Persona("Ana", 20);
p1.mostrarDatos();
*/

/* ============================================================
   TIPOS DE DATOS: STRING, DATE, CALENDAR Y LOCAL
   ============================================================ */
// String: texto.
// Date: fecha antigua de java.util.
// Calendar: permite trabajar con fechas y cambiar sus partes.
// LocalDate / LocalTime / LocalDateTime: fechas y horas modernas de java.time.

// String ejemplo:
// String nombre = "Juan";

// Date ejemplo:
/*
import java.util.Date;
Date fecha = new Date();
System.out.println(fecha);
*/

// Calendar ejemplo:
/*
import java.util.Calendar;
Calendar calendario = Calendar.getInstance();
int anio = calendario.get(Calendar.YEAR);
int mes = calendario.get(Calendar.MONTH) + 1; // MONTH empieza en 0
int dia = calendario.get(Calendar.DAY_OF_MONTH);
System.out.println(dia + "/" + mes + "/" + anio);
*/

// LocalDate ejemplo:
/*
import java.time.LocalDate;
LocalDate hoy = LocalDate.now();
System.out.println(hoy);
*/

// Explicación rápida:
// Date = clase vieja, simple para fechas.
// Calendar = más flexible que Date, pero también antigua.
// Local = clases modernas de java.time, más limpias y recomendadas hoy.
// Si solo quieres fecha usa LocalDate, si quieres hora usa LocalTime, si quieres ambas usa LocalDateTime.

/* ============================================================
   LOS 4 PILARES DE LA POO
   ============================================================ */
// 1. Encapsulamiento: proteger los datos con private y acceder con métodos.
// 2. Herencia: una clase hija reutiliza atributos y métodos de una clase padre.
// 3. Polimorfismo: un mismo método puede comportarse distinto según el objeto.
// 4. Abstracción: mostrar lo esencial y ocultar detalles internos.

/*
// Encapsulamiento
class Cuenta {
    private double saldo;

    public void depositar(double cantidad) {
        saldo += cantidad;
    }

    public double getSaldo() {
        return saldo;
    }
}

// Herencia y polimorfismo
class Animal {
    public void sonido() {
        System.out.println("Sonido de animal");
    }
}

class Perro extends Animal {
    @Override
    public void sonido() {
        System.out.println("Guau");
    }
}

// Abstracción
abstract class Figura {
    public abstract double area();
}
*/

/* ============================================================
   ARREGLOS Y LISTAS
   ============================================================ */
// Arrays: tamaño fijo.
// List / ArrayList: tamaño dinámico, permite agregar y quitar elementos.

/*
int[] numeros = new int[5];

import java.util.ArrayList;
ArrayList<String> nombres = new ArrayList<>();
nombres.add("Ana");
nombres.add("Luis");
System.out.println(nombres.get(0));
*/

/* ============================================================
   ARCHIVOS
   ============================================================ */
// Un archivo permite guardar o leer información desde el disco.
// Ejemplos comunes: lectura con Scanner, escritura con FileWriter o BufferedWriter.

/*
import java.io.FileWriter;
import java.io.IOException;

try {
    FileWriter escritor = new FileWriter("datos.txt");
    escritor.write("Hola archivo");
    escritor.close();
} catch (IOException e) {
    System.out.println("Error al escribir el archivo");
}
*/

/* ============================================================
   PACKAGE Y PROTECTED
   ============================================================ */
// package: sirve para organizar clases dentro de una carpeta lógica.
// protected: permite acceso dentro de la misma clase, el mismo paquete y clases hijas.

/*
package animales;

class Animal {
    protected String nombre;

    public Animal(String nombre) {
        this.nombre = nombre;
    }

    protected void mostrarNombre() {
        System.out.println("Nombre: " + nombre);
    }
}

package animales;

public class Perro extends Animal {
    public Perro(String nombre) {
        super(nombre);
    }

    public void ladrar() {
        mostrarNombre();
        System.out.println("El perro ladra");
    }
}

// Resumen:
// package = organiza el código.
// protected = deja usar atributos o métodos en clases hijas y dentro del mismo paquete.
*/

/* POO


import java.util.Scanner;
public class Basesjavaejercicios{
    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

        System.out.println("Ingrese el primer numero:");
        int valor1 = sc.nextInt();
        System.out.println("Ingrese el segundo numero:");
        int valor2 = sc.nextInt();

        BaseBv suma = new BaseBv(valor1, valor2);
        suma.operacion();
    }
}
    public class BaseBv{
    private int v1, v2,resultado;

    public BaseBv(int valor1, int valor2){
        this.v1 = valor1;
        this.v2 = valor2;
    }
    public void operacion(){
        resultado = v1 + v2;
        System.out.println("El resultado de la suma es: " + resultado);
    }
}

*/