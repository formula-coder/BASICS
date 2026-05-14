public class Bv1 {
    
    private int kg=0, llenadocompleto=0 , tiporopa=0, lavadocompleto=0, secadocompleto=0, planchadocompleto=0, dobladocompleto=0, guardadocompleto=0;

    public Bv1(int kg, int tiporopa){
        this.kg = kg;
        this.tiporopa = tiporopa;
    }
private void llenado(){
    if(kg<=12){
        llenadocompleto = 1;
        System.out.println("Llenando...");
        System.out.println("Llenado completo");

    }else{
        System.out.println("La lavadora no soporta esa cantidad de ropa");
    }
}
 private void lavado(){
    llenado();
    if (llenadocompleto ==1){
        if(tiporopa==1){
            System.out.println("Ropa blanca/Lavado suave");
            System.out.println("Lavando...");
            lavadocompleto=1;
        
        }else if(tiporopa==2){
            System.out.println("Ropa de color/Lavado normal");
            System.out.println("Lavando...");
            lavadocompleto=1;
        }
    }
 }

 private void secado(){
    lavado();
    if(lavadocompleto==1){
        System.out.println("Secando...");
        secadocompleto=1;
    }
 }
 public void ciclofinalizado(){
    secado();
    if(secadocompleto==1){
        System.out.println("Ciclo finalizado");
    }
 }
}
