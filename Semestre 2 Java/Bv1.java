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