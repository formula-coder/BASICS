import java.util.Scanner;
public class Bv2{
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Ingrese el contenido del archivo: ");
        String contenido = scanner.nextLine();
        Bv1.escribirArchivo("archivo.txt", contenido);
    }
}


