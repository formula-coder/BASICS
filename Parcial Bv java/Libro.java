// Archivo: Libro.java
import java.io.Serializable;

public abstract class Libro implements Serializable {
    protected int codigo;
    protected String titulo;
    protected double precioBase;
    protected int copiasLicenciadas;

    public Libro(int codigo, String titulo, double precioBase, int copiasLicenciadas) {
        this.codigo = codigo;
        this.titulo = titulo;
        this.precioBase = precioBase;
        this.copiasLicenciadas = copiasLicenciadas;
    }

    public abstract double calcularPrecio();

    // Getters y Setters
    public String getTitulo() { return titulo; }
    public int getCopiasLicenciadas() { return copiasLicenciadas; }
    public void setCopiasLicenciadas(int copiasLicenciadas) { this.copiasLicenciadas = copiasLicenciadas; }
    public double getPrecioBase() { return precioBase; }
}