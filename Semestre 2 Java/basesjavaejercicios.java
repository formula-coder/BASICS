import java.util.Scanner;

public class Basesjavaejercicios{
    int kilos = 0, llenadocompleto = 0, tiporopa = 0, lavadocompleto = 0, secadocompleto = 0;
    
    public void llenado(){
        if(kilos < 5){
            llenadocompleto = 1;
            System.out.println("Llenado completo");
        } else {
            System.out.println("Llenado incompleto");
        }
    }
    
    public void lavado(){
        llenado();
        if(llenadocompleto == 1){
        if(tiporopa ==1){
            System.out.println("Ropa blanca/lavado suave ");
            System.out.println("Lavando....");
            lavadocompleto = 1;
        }else if(tiporopa ==2){
            System.out.println("Ropa de color/lavado normal");
            System.out.println("Lavando....");
            lavadocompleto = 1;
        }
    }
}
    public void secado(){
        lavado();
        if(lavadocompleto == 1){
            System.out.println("Secando....");
            secadocompleto = 1;
        } else {
            System.out.println("No se puede secar, lavado incompleto");
        }
    }
    
    public void ciclofinal(){
        secado();
        if(secadocompleto == 1){
            System.out.println("Ciclo de lavado completo");
        }
    }
    
    public static void main(String[] args){
        Basesjavaejercicios maquina = new Basesjavaejercicios();
        maquina.kilos = 3;
        maquina.tiporopa = 1;
        maquina.ciclofinal();
    }
}
