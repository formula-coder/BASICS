import java.util.Scanner;

public class BaseBv{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("¿La ropa es blanca o de color? (1 para blanca, 2 para color)");
        int tiporopa = sc.nextInt();
        System.out.println("¿Cuántos kilos de ropa desea lavar?");
        int kilos = sc.nextInt();

        Basesjavaejercicios ciclo = new Basesjavaejercicios();
        ciclo.kilos = kilos;
        ciclo.tiporopa = tiporopa;
        ciclo.ciclofinal();
        sc.close();
    }
}