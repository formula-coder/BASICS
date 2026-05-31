import java.io.Serializable;
import java.util.ArrayList;

public class Compra implements Serializable {
    private String nombreCliente;
    private double total;
    private ArrayList<Linea> lineas;
    private Libreria libreria; // Asociación necesaria para acceder al catálogo

    public Compra(String nombreCliente, Libreria libreria) {
        this.nombreCliente = nombreCliente;
        this.libreria = libreria;
        this.lineas = new ArrayList<>();
        this.total = 0;
    }

    public String getNombreCliente() { return nombreCliente; }
    public double getTotal() { return total; }
    public ArrayList<Linea> getLineas() { return lineas; }

    public Linea agregarLinea(String titulo, int cantidad) throws Exception {
        Libro libro = libreria.buscarLibro(titulo);
        
        if (libro == null) {
            throw new Exception("El libro no existe en el catálogo.");
        }
        if (libro.getCopiasLicenciadas() < cantidad) {
            throw new Exception("No hay copias licenciadas suficientes.");
        }

        // Disminuir inventario
        libro.setCopiasLicenciadas(libro.getCopiasLicenciadas() - cantidad);
        
        // Crear y añadir la línea
        Linea nuevaLinea = new Linea(libro, cantidad);
        this.lineas.add(nuevaLinea);
        
        // Actualizar total parcial (sin IVA aún, el IVA se aplica al final)
        this.total += nuevaLinea.getSubtotal();
        
        return nuevaLinea;
    }

    public void removerLinea(String titulo) {
        Linea lineaRemover = null;
        for (Linea linea : lineas) {
            if (linea.getLibro().getTitulo().equalsIgnoreCase(titulo)) {
                lineaRemover = linea;
                break;
            }
        }
        
        if (lineaRemover != null) {
            Libro libro = lineaRemover.getLibro();
            // Restaurar inventario
            libro.setCopiasLicenciadas(libro.getCopiasLicenciadas() + lineaRemover.getCantidad());
            // Restar del total parcial
            this.total -= lineaRemover.getSubtotal();
            // Eliminar de la colección
            lineas.remove(lineaRemover);
        }
    }

    public double totalizarCompra() {
        double sumaSubtotales = 0;
        for (Linea linea : lineas) {
            sumaSubtotales += linea.getSubtotal();
        }
        // Aplicar el 19% de IVA
        this.total = sumaSubtotales * 1.19;
        return this.total;
    }
}