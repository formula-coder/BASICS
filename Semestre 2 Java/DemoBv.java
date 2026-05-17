import java.util.Scanner;

public class DemoBv {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Ejemplo de interfaces con Bv1 y Bv4");
        System.out.println("1. Circulo (Bv2)");
        System.out.println("2. Cuadrado (Bv3)");
        System.out.print("Elige una opcion: ");

        int opcion = scanner.nextInt();

        switch (opcion) {
            case 1:
                System.out.print("Ingresa el radio: ");
                double radio = scanner.nextDouble();

                Bv2 circulo = new Bv2(radio);
                System.out.printf("Area del circulo: %.2f%n", circulo.calcularArea());
                circulo.dibujar();
                break;

            case 2:
                System.out.print("Ingresa el lado: ");
                double lado = scanner.nextDouble();

                Bv3 cuadrado = new Bv3(lado);
                System.out.printf("Area del cuadrado: %.2f%n", cuadrado.calcularArea());
                cuadrado.dibujar();
                break;

            default:
                System.out.println("Opcion invalida.");
                break;
        }

        scanner.close();
    }
}