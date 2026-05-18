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
   SENTENCIA SWITCH
   ============================================================ */
/*
// Uso: elegir entre varias opciones según el valor de una variable.
// Sintaxis básica:
switch(valor) {
    case 1:
        // acción para caso 1
        break; // evita "caer" al siguiente case
    case 2:
        // acción para caso 2
        break;
    default:
        // acción por defecto si ningún case coincide
}

// Ejemplo práctico:
int opcion = 2;
switch(opcion) {
    case 1:
        System.out.println("Elegiste 1");
        break;
    case 2:
        System.out.println("Elegiste 2");
        break;
    default:
        System.out.println("Opción no válida");
}

// Notas:
// - Desde Java 7 puedes usar strings en switch: switch("hola"){...}
// - Si omites "break" se ejecutan las instrucciones del siguiente case (fall-through).
// - Desde Java 14 existe la forma más moderna con "switch expression" (->, yield),
//   pero la forma clásica es la mostrada arriba y sirve para la mayoría de ejercicios.
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
// 1. Encapsulamiento:
//    - Proteger el estado interno de un objeto (atributos private).
//    - Permitir cambios SOLO por metodos que apliquen reglas.
//    - Evitar estados invalidos (por ejemplo, saldo negativo sin control).
//    Idea clave: no es "poner getters/setters a todo", sino exponer
//    comportamientos con sentido (depositar, retirar, transferir, etc.).
// 2. Herencia: una clase hija reutiliza atributos y métodos de una clase padre.
// 3. Polimorfismo: un mismo método puede comportarse distinto según el objeto.
// 4. Abstracción: mostrar lo esencial y ocultar detalles internos.

/*
// Encapsulamiento (ejemplo completo)
class Cuenta {
    private double saldo;

    public Cuenta(double saldoInicial) {
        if (saldoInicial < 0) {
            throw new IllegalArgumentException("El saldo inicial no puede ser negativo");
        }
        this.saldo = saldoInicial;
    }

    public void depositar(double cantidad) {
        if (cantidad <= 0) {
            throw new IllegalArgumentException("La cantidad a depositar debe ser mayor a 0");
        }
        saldo += cantidad;
    }

    public void retirar(double cantidad) {
        if (cantidad <= 0) {
            throw new IllegalArgumentException("La cantidad a retirar debe ser mayor a 0");
        }
        if (cantidad > saldo) {
            throw new IllegalArgumentException("Fondos insuficientes");
        }
        saldo -= cantidad;
    }

    public double getSaldo() {
        return saldo;
    }
}
 ........................................................................................................
public class Bv1 {
    
    private int kg=0, llenadocompleto=0 , tiporopa=0, lavadocompleto=0, secadocompleto=0, planchadocompleto=0, dobladocompleto=0, guardadocompleto=0;

    public Bv1(int kg, int tiporopa){
        this.kg = kg;
        this.tiporopa = tiporopa;
    }
private void llenado(){
    if(kg<=12){
        llenadocompleto = 1;
        System.out.println("Llenando...");
        System.out.println("Llenado completo");

    }else{
        System.out.println("La lavadora no soporta esa cantidad de ropa");
    }
}
 private void lavado(){
    llenado();
    if (llenadocompleto ==1){
        if(tiporopa==1){
            System.out.println("Ropa blanca/Lavado suave");
            System.out.println("Lavando...");
            lavadocompleto=1;
        
        }else if(tiporopa==2){
            System.out.println("Ropa de color/Lavado normal");
            System.out.println("Lavando...");
            lavadocompleto=1;
        }
    }
 }

 private void secado(){
    lavado();
    if(lavadocompleto==1){
        System.out.println("Secando...");
        secadocompleto=1;
    }
 }
 public void ciclofinalizado(){
    secado();
    if(secadocompleto==1){
        System.out.println("Ciclo finalizado");
    }
 }
}
import java.util.Scanner;

public class Bv2{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.println("Lavadora");
        System.out.println("Ingrese la cantidad de kg de ropa a lavar");
        int kg = sc.nextInt();

        System.out.println("Ingrese el tipo de ropa a lavar");
        System.out.println("1. Ropa blanca");
        System.out.println("2. Ropa de color");
        int tiporopa = sc.nextInt();

        Bv1 lavadora = new Bv1(kg, tiporopa);
        lavadora.ciclofinalizado();
    }
}.......................................................................................................
// Por que esto SI es encapsulamiento:
// - Nadie puede hacer: cuenta.saldo = -1000 (saldo es private).
// - Las reglas viven dentro de la clase, no repartidas por todo el programa.
// - El objeto siempre se mantiene en un estado valido.

// Error comun:
// Hacer setSaldo(double s) publico sin validacion rompe el encapsulamiento,
// porque cualquier parte del codigo podria dejar la cuenta en estado invalido.

// ============================================================
// HERENCIA Y POLIMORFISMO (explicación detallada)
// ============================================================
//
// HERENCIA: Una clase hija hereda atributos y métodos de una clase padre.
// Sintaxis: class Hijo extends Padre { ... }
// Palabras clave: extends, super, @Override
//
// POLIMORFISMO: "Muchas formas". Mismo método, diferentes comportamientos
// según el objeto que lo llama.
//
// ============================================================
// EJEMPLO PASO A PASO:
// ============================================================

// 1. CLASE PADRE - Define el comportamiento general
/*
class Animal {
    protected String nombre;  // protected = accesible en clases hijas
    
    public Animal(String nombre) {
        this.nombre = nombre;
    }
    
    // Método que será SOBRESCRITO (reemplazado) en clases hijas
    public void sonido() {
        System.out.println("Sonido genérico de animal");
    }
}
*/

// 2. CLASE HIJA 1 - Hereda de Animal y SOBRESCRIBE sonido()
/*
class Perro extends Animal {
    public Perro(String nombre) {
        super(nombre);  // super() llama al constructor de la clase padre
    }
    
    // @Override avisa al compilador que estamos reemplazando un método
    @Override
    public void sonido() {
        System.out.println(nombre + " dice: Guau guau!");
    }
}
*/

// 3. CLASE HIJA 2 - También hereda de Animal y sobrescribe sonido()
/*
class Gato extends Animal {
    public Gato(String nombre) {
        super(nombre);
    }
    
    @Override
    public void sonido() {
        System.out.println(nombre + " dice: Miau miau!");
    }
}
*/

// ============================================================
// CÓMO FUNCIONA EL POLIMORFISMO EN ACCIÓN
// ============================================================
/*
public static void main(String[] args) {
    // AQUÍ OCURRE EL POLIMORFISMO:
    // Declaramos referencias de tipo "Animal" (clase padre)
    // pero asignamos objetos de tipos "Perro" y "Gato" (clases hijas)
    
    Animal animal1 = new Perro("Rex");
    Animal animal2 = new Gato("Misi");
    Animal animal3 = new Animal("Genérico");
    
    // Cuando llamamos sonido(), Java elige CUÁL implementación ejecutar
    // según el tipo REAL del objeto, NO según el tipo de la referencia
    
    animal1.sonido();  // Imprime: Rex dice: Guau guau!
    animal2.sonido();  // Imprime: Misi dice: Miau miau!
    animal3.sonido();  // Imprime: Sonido genérico de animal
}
...................................................................................................................................................................................
public class Bv4 {
    public static void main (String[] args){

        Bv1 carro = new Bv2(); // Instanciar Bv2
        carro.Pedirdatos();
        carro.calcular();
        Bv1 moto = new Bv3(); // Instanciar Bv3
        moto.Pedirdatos();
        moto.calcular();
    }
}
    public class Bv3 extends Bv1{

    @Override
    public void calcular(){
        resultado = valor1 * valor2;
        System.out.println("El resultado de la multiplicacion es: " + resultado);
    }
}
    public class  Bv2 extends Bv1{

    @Override
    public void calcular(){
        resultado = valor1 + valor2;
        System.out.println("El resultado de la suma es: " + resultado);
    }
}
    import java.util.Scanner;

public abstract class Bv1{
    protected int valor1, valor2,resultado;
    Scanner sc = new Scanner(System.in);

    public void Pedirdatos(){
        System.out.println("calculadora Bv");
        System.out.println("Ingrese el primer valor");
        valor1 = sc.nextInt();
        System.out.println("Ingrese el segundo valor");
        valor2 = sc.nextInt();
    }

    public abstract void calcular();    
    public void mostrarresultado(){
        System.out.println("El resultado es: " + resultado);
    }
}
..............................................................................................................................................................
*/

// ============================================================
// POR QUÉ ES POLIMORFISMO:
// ============================================================
// - Usamos REFERENCIAS del tipo padre (Animal)
// - Pero almacenamos OBJETOS de tipos hijos (Perro, Gato)
// - Mismo método sonido() = COMPORTAMIENTOS DIFERENTES
// - El método correcto se elige EN TIEMPO DE EJECUCIÓN
//   (no en tiempo de compilación)
//
// Beneficio: Puedes escribir código genérico que funciona con 
// cualquier clase hija sin cambiar nada.

// ============================================================
// EN TUS ARCHIVOS DE EJERCICIO:
// ============================================================
// BaseBv.java = Clase padre
// Basesjavaejercicios.java extends BaseBv = Clase hija
// Si sobrescribis un método en Basesjavaejercicios con @Override,
// ese método nuevo reemplaza al de BaseBv.

// ============================================================
// TÉRMINOS IMPORTANTES:
// ============================================================
// - extends: establece herencia (clase hija)
// - super: referencia a la clase padre
// - @Override: anotación que indica que sobrescribimos un método
// - Polimorfismo: capacidad del mismo método de comportarse diferente

// ============================================================
// ABSTRACCIÓN (Explicación detallada)
// ============================================================
//
// ¿QUÉ ES?
// Mostrar SOLO lo esencial de un objeto/clase, ocultando 
// los detalles complejos de CÓMO lo hace internamente.
//
// ANALOGÍA:
// Un auto: Sabes que existe acelerar(), frenar(), girar()
// NO necesitas saber cómo funciona el motor por dentro.
// Eso es abstracción: expones interfaz simple, ocultas complejidad.
//
// ============================================================
// EN JAVA: ABSTRACT CLASS
// ============================================================
// Una clase abstract (abstracta) es una PLANTILLA que define
// qué métodos DEBEN tener las clases hijas, pero no los implementa.
//
// Palabras clave:
// - abstract class: clase que NO puede instanciarse directamente
// - abstract method: método sin implementación (solo firma)
//
// ============================================================
// EJEMPLO: Clase abstracta VEHICULO
// ============================================================
/*
abstract class Vehiculo {
    // Métodos abstract: las clases hijas DEBEN implementarlos
    abstract void arrancar();
    abstract void detener();
    abstract void acelerar();
    
    // Métodos concretos: todas las clases hijas los heredan igual
    public void hacerSonido() {
        System.out.println("Biiip!");
    }
}
*/

// CLASES HIJAS: Implementan métodos abstract
/*
class Auto extends Vehiculo {
    @Override
    void arrancar() {
        System.out.println("Auto: Prendiendo motor...");
    }
    
    @Override
    void detener() {
        System.out.println("Auto: Frenando...");
    }
    
    @Override
    void acelerar() {
        System.out.println("Auto: Acelerando a 100 km/h");
    }
}

class Bicicleta extends Vehiculo {
    @Override
    void arrancar() {
        System.out.println("Bicicleta: Empezando a pedalear...");
    }
    
    @Override
    void detener() {
        System.out.println("Bicicleta: Frenando con zapatas...");
    }
    
    @Override
    void acelerar() {
        System.out.println("Bicicleta: Acelerando a 30 km/h");
    }
}
*/

// ============================================================
// CÓMO USAR LA ABSTRACCIÓN
// ============================================================
/*
public static void main(String[] args) {
    // NO puedes hacer esto (es abstract):
    // Vehiculo v = new Vehiculo();  // ERROR!
    
    // Pero SÍ puedes usar referencias abstract:
    Vehiculo auto = new Auto();
    Vehiculo bici = new Bicicleta();
    
    // Llamas los métodos definidos en la clase abstract
    auto.arrancar();     // Auto: Prendiendo motor...
    auto.acelerar();     // Auto: Acelerando a 100 km/h
    auto.hacerSonido();  // Biiip!
    auto.detener();      // Auto: Frenando...
    
    bici.arrancar();     // Bicicleta: Empezando a pedalear...
    bici.acelerar();     // Bicicleta: Acelerando a 30 km/h
    bici.hacerSonido();  // Biiip!
    bici.detener();      // Bicicleta: Frenando con zapatas...
}

................................................................................................................................................................................................................................
import java.util.Scanner;

public class Bv1{

    public static void main(String[]args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Digite o valor do lado do quadrado: ");
        double lado = sc.nextDouble();
        Bv3 cuadrado = new Bv3(0, 0, lado);
        System.out.println("A area do quadrado e: " + cuadrado.area());
    }
}


public abstract class Bv2{

protected double x,y;
protected double lado;


protected Bv2(double x, double y, double lado){
    this.x = x;
    this.y = y;
    this.lado = lado;
}

public abstract double area();
    
}
public class Bv3 extends Bv2{

    
  public Bv3(double x, double y, double lado) {
        super(x, y, lado);
    }

    @Override
    public double area() {
      double answer = lado*lado;
      return answer;
    }
}...............................................................................................................................................................................................................................................................................
*/

// ============================================================
// DIFERENCIA: ABSTRACT CLASS vs INTERFACE
// ============================================================
//
// ABSTRACT CLASS:
// - Puede tener métodos abstract (sin implementación)
// - Puede tener métodos concretos (con implementación)
// - Puede tener atributos (variables)
// - Una clase solo puede extender UNA abstract class
// - Usa: extends
//
// INTERFACE:
// - TODOS los métodos son abstract (sin implementación)
// - NO puede tener atributos (solo constantes)
// - Una clase puede implementar VARIAS interfaces
// - Usa: implements
/*
//import java.util.Scanner;

public abstract class Bv1{
    protected int valor1, valor2,resultado;
    Scanner sc = new Scanner(System.in);

    public void Pedirdatos(){
        System.out.println("calculadora Bv");
        System.out.println("Ingrese el primer valor");
        valor1 = sc.nextInt();
        System.out.println("Ingrese el segundo valor");
        valor2 = sc.nextInt();
    }

    public abstract void calcular();    
    public void mostrarresultado(){
        System.out.println("El resultado es: " + resultado);
    }
}
public interface Bv1{

    public double calcularArea();
}
public class Bv2 implements Bv1, Bv4 {

    private double radio;
    public Bv2(){

    }
    public Bv2(double radio){
        this.radio=radio;
    }

    @Override
    public double calcularArea(){
        double pi=3.1416;
        double resultado = pi*radio*radio;
        return resultado;
    }

    @Override
    public double dibujar(){
        System.out.println("Dibujando un círculo...");
        return 0;
    }

}
public class Bv3 implements Bv1, Bv4 {
 
    protected double lado;
    public Bv3(){
}
public Bv3(double lado){
    this.lado=lado;
}
@Override
public double calcularArea(){
    double resultado = lado*lado;
    return resultado;
}

@Override
public double dibujar(){
    System.out.println("Dibujando un cuadrado...");
    return 0;
}
}
public interface Bv4{
    public double dibujar();
}
*/
// ============================================================
// PARA TUS ARCHIVOS:
// ============================================================
// BaseBv es una clase abstract que define:
// - public abstract void Operaciones(); (metodo sin implementacion)
// - public void ASK() (metodo concreto)
// - public void Show() (metodo concreto)



/*
............................................................................................................................................................................

import java.util.Scanner;
public class Bv2{
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Ingrese el contenido del archivo: ");
        String contenido = scanner.nextLine();
        Bv1.escribirArchivo("archivo.txt", contenido);
    }
}
import java.io.*;

public class Bv1{

    public static void crearArchivo(String nombreArchivo){
        File archivo = new File(nombreArchivo);
try{
        PrintWriter pw =  new PrintWriter(archivo);
   pw.close();
   System.out.println("Archivo creado exitosamente");
}catch(FileNotFoundException ex){
    ex.printStackTrace(System.out);
    }
}
 public static void escribirArchivo(String nombreArchivo, String contenido){
    File archivo = new File(nombreArchivo);

    try{
        PrintWriter pw = new PrintWriter(archivo);
        pw.println(contenido);
        pw.close();
        System.out.println("Archivo creado exitosamente");
    }catch(FileNotFoundException ex){
        ex.printStackTrace(System.out);
    }
}
}
............................................................................................................................................................................................................................................
 */

/* ..............................................................................................................................................................................................................................................................................................................
import java.io.Serializable;

public class Bv1 implements Bv2, Serializable {

    protected String name;
    protected int age;

    public Bv1(String name, int age){
        this.name = name;
        this.age = age;
    }

    @Override
    public void displayinfo(){
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
     
    }
}

import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.util.Scanner;

public interface Bv2 {
    public void displayinfo();

    public static void main(String[]args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Ingrese el nombre: ");
        String name = scanner.nextLine();
        System.out.print("Ingrese la edad: ");
        int age = scanner.nextInt();
        Bv1 holi=new Bv1(name, age);
        holi.displayinfo();

        java.io.File archivo = new java.io.File("hola.dat");
    try{
        FileOutputStream fos = new FileOutputStream(archivo);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(holi);
        oos.close();
        fos.close();
    } catch(Exception e){
        System.out.println("Error al crear el archivo: " + e.getMessage());
    }
}
}

import java.io.File;
import java.io.FileInputStream;
import java.io.ObjectInputStream;

public class Bv3{
    public static void main(String[] args){
        File archivo = new File("Hola.dat");
        try{
                FileInputStream fis = new FileInputStream(archivo);
                ObjectInputStream ois = new ObjectInputStream(fis);
                while(fis.available() > 0){
                    Bv1 hola = (Bv1) ois.readObject();
                    hola.displayinfo();
                }
        }catch(Exception e){
            System.out.println("Error al crear el archivo: " + e.getMessage());
                e.printStackTrace();
        }
    }
}..............................................................................................................................................................................................................................................................
 */
//
// Basesjavaejercicios (y Resta, Multiplicacion, Division)
// SON clases que IMPLEMENTAN el método abstract Operaciones()
// 
// La clase abstract fuerza que TODAS las hijas tengan Operaciones()
// Eso es ABSTRACCIÓN: defines interfaz, cada hija lo hace diferente

// ============================================================
// BENEFICIOS DE ABSTRACCIÓN:
// ============================================================
// 1. Fuerza consistencia: todas las hijas deben tener ciertos métodos
// 2. Oculta complejidad: quien usa la clase NO necesita saber detalles
// 3. Define contrato: establece qué debe tener cada clase hija
// 4. Facilita mantenimiento: cambios internos sin afectar usuarios
// 5. Código más limpio y organizado

// Abstracción
// abstract class Figura {
//     public abstract double area();
// }
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
*Excepciones:......................................................................................................................
import java.util.Scanner;

public class Bv1{
    public static void main(String[] args){
   
   
   try{  int valor1, valor2, resultado;
 
   Scanner sc= new Scanner(System.in);
   
   System.out.println("Ingrese el primer valor: ");
    valor1 = sc.nextInt();

    System.out.println("Ingrese el segundo valor: ");
    valor2 = sc.nextInt();

    resultado = valor1 / valor2;
    System.out.println("El resultado es: " + resultado);
   }catch(Exception e){
    System.out.println("Error: " + e.getMessage());
    }finally{
        System.out.println("Programa finalizado.");
    }
    }
}........................................................................................................................................................................




*Funciones:................................................................................................................................................................................
// Programa de un solo archivo que muestra funciones en Java (estilo C++)
public class Bv1 {

    private String name;
    private int age;

    public Bv1(String name, int age){
        this.name = name;
        this.age = age;
    }

    // Método de instancia: muestra la información del objeto
    public void displayinfo(){
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }

    // Ejercicio: métodos (funciones) en Java - muy sencillo
    // 1) Método estático que suma dos números y devuelve el resultado
    public static int sumar(int a, int b){
        return a + b;
    }

    // 2) Método de instancia que devuelve un saludo personalizado
    public String saludar(){
        return "Hola, " + name + "!";
    }

    // 3) Método que muestra cómo usar los anteriores (demostración)
    public static void ejercicioFunciones(){
        Bv1 ejemplo = new Bv1("Ana", 20);
        System.out.println("Ejemplo suma: 3 + 5 = " + sumar(3,5));
        System.out.println(ejemplo.saludar());
        ejemplo.displayinfo();
        System.out.println("También puedes crear tu propio objeto y llamar a sus métodos.");
    }

    // Main de prueba para ejecutar el ejercicio directamente (archivo único)
    public static void main(String[] args){
        ejercicioFunciones();
        // Ejemplo interactivo mínimo (opcional): crear objeto desde argumentos
        if(args.length >= 2){
            String n = args[0];
            int a = 0;
            try{ a = Integer.parseInt(args[1]); } catch(NumberFormatException ex){ }
            Bv1 usuario = new Bv1(n, a);
            System.out.println("--- Datos desde args ---");
            usuario.displayinfo();
        }
    }
}
............................................................................................................................................................
*/