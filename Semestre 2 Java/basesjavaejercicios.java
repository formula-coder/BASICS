import java.util.Scanner;

public class basesjavaejercicio{
    public static void main(String args[]){
        Scanner entrada = new Scanner (System.in);
        String nombre = "";
        int clave =0, antiguedad =0;
        system.out.println("%%%%%%%%%%%%%%%%%%%%%%");
        system.out.println("Bienvenido al sistema de registro de empleados");
        system.out.println("%%%%%%%%%%%%%%%%%%%%%%");
        system.out.println("");
        system.out.println("");

        system.out.println("cual es el nombre del trabajor?:");
        nombre = entrada. nextline();
        System.out.println("");

        system.out.println("cuanto tiempo de servicio tiene el trabajador");
        antiguedad = entrada.nextInt;
        System.out.println("");

        system.out.println("Ingrese la clave");
        clave = entrada.nextInt;
        System.out.println("");

if(clave==1){
    System.out.println("El trabajador tiene 10 días de vacaciones.");
}else if (clave ==2){
    System.out.println("El trabajador tiene 20 días de vacaciones.");
}else if(clave==3){    
    System.out.println("El trabajador tiene 30 días de vacaciones.");
} else{
    System.out.println("clave no valida");
        }
    }
}