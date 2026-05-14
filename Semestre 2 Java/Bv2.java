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
}