public class Bv2 implements Bv1, Bv4 {

    private double radio;
    public Bv2(){

    }
    public Bv2(double radio){
        this.radio=radio;
    }

    @Override
    public double calcularArea(){
        double pi=3.1416;
        double resultado = pi*radio*radio;
        return resultado;
    }

    @Override
    public double dibujar(){
        System.out.println("Dibujando un círculo...");
        return 0;
    }

}