// Archivo: LibroDigital.java
public class LibroDigital extends Libro {
    private double descuento;

    public LibroDigital(int codigo, String titulo, double precioBase, int copiasLicenciadas, double descuento) {
        super(codigo, titulo, precioBase, copiasLicenciadas);
        this.descuento = descuento;
    }

    @Override
    public double calcularPrecio() {
        return precioBase - descuento; // Precio base menos descuento [cite: 151]
    }
}