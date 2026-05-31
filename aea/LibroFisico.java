// Archivo: LibroFisico.java
public class LibroFisico extends Libro {
    private double costoEnvio;

    public LibroFisico(int codigo, String titulo, double precioBase, int copiasLicenciadas, double costoEnvio) {
        super(codigo, titulo, precioBase, copiasLicenciadas);
        this.costoEnvio = costoEnvio;
    }

    @Override
    public double calcularPrecio() {
        return precioBase + costoEnvio; // Precio base más costo de envío [cite: 151]
    }
}