// Archivo: Linea.java
import java.io.Serializable;

public class Linea implements Serializable {
    private int cantidad;
    private double subtotal;
    private Libro libro;

    public Linea(Libro libro, int cantidad) {
        this.libro = libro;
        this.cantidad = cantidad;
        this.subtotal = cantidad * libro.calcularPrecio(); // Cantidad por el precio devuelto [cite: 98]
    }

    public double getSubtotal() { return subtotal; }
    public int getCantidad() { return cantidad; }
    public Libro getLibro() { return libro; }
}