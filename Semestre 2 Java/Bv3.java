public class Bv3 implements Bv1, Bv4 {
 
    protected double lado;
    public Bv3(){
}
public Bv3(double lado){
    this.lado=lado;
}
@Override
public double calcularArea(){
    double resultado = lado*lado;
    return resultado;
}

@Override
public double dibujar(){
    System.out.println("Dibujando un cuadrado...");
    return 0;
}
}