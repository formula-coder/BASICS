public class Basesjava{
    public static void main(String args[]){
        System.out.println("Hola Mundo");
    }
}

//tipos de datos: Enteros byte short int long
//decimales float double
//otros char boolean String

//librerias: java.util.Scanner
//sirve para leer datos por consola, se importa al inicio del codigo, se crea un objeto de la clase Scanner y se utiliza el metodo nextLine() para leer una linea de texto, nextInt() para leer un entero, nextDouble() para leer un decimal, etc.
//ciclos for:
for(int i=0; i<10; i++){
    System.out.println(i+"");
}

//ciclo while:
int i=0;
while(i<10){
    System.out.println(i+"");
    i++;
}

// ciclo do while:
do{
    System.out.println(i+"");
    i-=200;
}while (i>=0);

//tipos de variable 
 //variables tipo string.
 //declracion de variables.
 int numero=0;
 string nombre="Juan";
 //comparar valores de variables.
 numero== 9;
 nombre =="Juan";
 nombre.equals("Juan"); //para comparar strings se utiliza el metodo equals() en lugar del operador ==, ya que el operador == compara referencias de objetos y no su contenido.
 
 //arreglos: son estructuras de datos que permiten almacenar una colección de elementos del mismo tipo, se declaran con el tipo de dato seguido de corchetes [] y el nombre del arreglo, por ejemplo: int[] numeros; String[] nombres; para inicializar un arreglo se utiliza la palabra reservada new seguida del tipo de dato y el tamaño del arreglo entre corchetes, por ejemplo: numeros = new int[10]; nombres = new String[5]; para acceder a los elementos de un arreglo se utiliza el indice del elemento entre corchetes, por ejemplo: numeros[0] para acceder al primer elemento del arreglo numeros, nombres[1] para acceder al segundo elemento del arreglo nombres.
 int numeros []= new int[10];
 
 //matrices:
int numeros [][]= new int[3][3]; //matriz de 3 filas y 3 columnas

for(int j=0;j< filas;j++){
    for(int i=0;i<columnas;i++){
        System.out.println("ingrese el numero de a fila"+j " y el valor de la columna"+i);
        numeros[j][i]= sc.nextInt();
    }
}

for(int j=0;j< filas;j++){
    for(int i=0;i<columnas;i++){
        numeros[i][j]= contador;
        contador++;
        System.out.print("["+numeros[i][j]+"]");
    }