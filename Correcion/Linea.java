import java.io.Serializable;

public class Linea implements Serializable {
    private int cantidad;
    private double subtotal;
    private Libro libro;

    public Linea(Libro libro, int cantidad) {
        this.libro = libro;
        this.cantidad = cantidad;
        this.subtotal = libro.calcularPrecio() * cantidad;
    }

    public int getCantidad() { return cantidad; }
    public double getSubtotal() { return subtotal; }
    public void setSubtotal(double subtotal) { this.subtotal = subtotal; }
    public Libro getLibro() { return libro; }
}