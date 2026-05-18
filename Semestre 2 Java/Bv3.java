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
}