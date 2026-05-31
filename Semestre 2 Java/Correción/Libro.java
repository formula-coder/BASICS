import java.io.Serializable;

public abstract class Libro implements Serializable {
    private int codigo;
    private String titulo;
    private double precioBase;
    private int copiasLicenciadas;

    public Libro(int codigo, String titulo, double precioBase, int copiasLicenciadas) {
        this.codigo = codigo;
        this.titulo = titulo;
        this.precioBase = precioBase;
        this.copiasLicenciadas = copiasLicenciadas;
    }

    public int getCodigo() { return codigo; }
    public String getTitulo() { return titulo; }
    public double getPrecioBase() { return precioBase; }
    
    public int getCopiasLicenciadas() { return copiasLicenciadas; }
    public void setCopiasLicenciadas(int copiasLicenciadas) { this.copiasLicenciadas = copiasLicenciadas; }

    // Método abstracto
    public abstract double calcularPrecio();
}