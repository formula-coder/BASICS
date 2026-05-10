import java.util.Scanner;
public class Basesjavaejercicios{
    public static void main(String args[]){
        int filas=0;
        int columnas=0;
        int contador=1;
       Scanner sc= new Scanner(System.in);
System.out.println("ingrese el numero de filas");
filas= sc.nextInt();
System.out.println("ingrese el numero de columnas");
columnas= sc.nextInt();

int numeros [][] = new int [filas][columnas];
for(int i=0;i< filas;i++){
    for(int j=0;j<columnas;j++){
        numeros[i][j]= contador;
        contador++;
        System.out.print("["+numeros[i][j]+"]");
    }
    System.out.println("");
}
}
}