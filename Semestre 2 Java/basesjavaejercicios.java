import java.util.Scanner;

public class basesjavaejercicios {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num_uno = 0;
        int num_dos = 0;
        int resultado = 0;
        int parametro = 0;
        
        System.out.println("Ingrese el numero de la operacion que desea realizar: 1. Suma, 2. Resta, 3. Multiplicacion, 4. Division"); 
        parametro = scanner.nextInt();
        
        switch(parametro){
            case 1:
                System.out.println("Realizando la suma de dos numeros");
                System.out.println("ingrese el primer numero");
                num_uno = scanner.nextInt();
                System.out.println("ingrese el segundo numero");
                num_dos = scanner.nextInt();
                resultado = num_uno + num_dos;
                System.out.println("El resultado de la suma es: " + resultado);
                break;

            case 2:
                System.out.println("Realizando la resta de dos numeros");
                System.out.println("ingrese el primer numero");
                num_uno = scanner.nextInt();
                System.out.println("ingrese el segundo numero");
                num_dos = scanner.nextInt();
                resultado = num_uno - num_dos;
        
        
                System.out.println("El resultado de la resta es: " + resultado);
                break;

            case 3:
                System.out.println("Realizando la multiplicacion de dos numeros");
                System.out.println("ingrese el primer numero");
                num_uno = scanner.nextInt();
                System.out.println("ingrese el segundo numero");
                num_dos = scanner.nextInt();
                resultado = num_uno * num_dos;
                System.out.println("El resultado de la multiplicacion es: " + resultado);
                break;
            
            case 4:
                System.out.println("Realizando la division de dos numeros");
                System.out.println("ingrese el primer numero");
                num_uno = scanner.nextInt();
                System.out.println("ingrese el segundo numero");
                num_dos = scanner.nextInt();
                if(num_dos != 0){
                    resultado = num_uno / num_dos;
                    System.out.println("El resultado de la division es: " + resultado);
                } else {
                    System.out.println("Error: No se puede dividir por cero");
                }
                break;
            
            default:
                System.out.println("Opcion no valida");
        }
    }
}