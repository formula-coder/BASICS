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