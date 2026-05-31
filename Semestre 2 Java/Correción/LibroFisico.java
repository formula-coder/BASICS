public class LibroFisico extends Libro {
    private double costoEnvio;

    public LibroFisico(int codigo, String titulo, double precioBase, int copiasLicenciadas, double costoEnvio) {
        super(codigo, titulo, precioBase, copiasLicenciadas);
        this.costoEnvio = costoEnvio;
    }

    @Override
    public double calcularPrecio() {
        return getPrecioBase() + costoEnvio;
    }
}