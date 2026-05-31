// Archivo: Compra.java
import java.io.Serializable;
import java.util.ArrayList;

public class Compra implements Serializable {
    private String nombreCliente;
    private double total;
    private ArrayList<Linea> lineas;

    public Compra(String nombreCliente) {
        this.nombreCliente = nombreCliente;
        this.lineas = new ArrayList<>();
        this.total = 0.0;
    }

    public Linea agregarLinea(String titulo, int cantidad, ArrayList<Libro> catalogo) throws LibroException {
        Libro libroEncontrado = null;
        for (Libro l : catalogo) {
            if (l.getTitulo().equalsIgnoreCase(titulo)) {
                libroEncontrado = l;
                break;
            }
        }

        // Si no existe o no hay copias suficientes, lanza excepción 
        if (libroEncontrado == null || libroEncontrado.getCopiasLicenciadas() < cantidad) {
            throw new LibroException("El libro no existe o no hay suficientes copias licenciadas.");
        }

        // Desminuir número de copias [cite: 97]
        libroEncontrado.setCopiasLicenciadas(libroEncontrado.getCopiasLicenciadas() - cantidad);
        
        Linea nuevaLinea = new Linea(libroEncontrado, cantidad);
        lineas.add(nuevaLinea);
        
        // Actualizar total sumando subtotal [cite: 99]
        this.total += nuevaLinea.getSubtotal();
        
        return nuevaLinea;
    }

    public void removerLinea(String titulo) {
        Linea lineaARemover = null;
        for (Linea l : lineas) {
            if (l.getLibro().getTitulo().equalsIgnoreCase(titulo)) {
                lineaARemover = l; // Remueve la línea por título [cite: 104]
                break;
            }
        }

        if (lineaARemover != null) {
            Libro libro = lineaARemover.getLibro();
            // Actualizar copias licenciadas sumando la cantidad devuelta [cite: 105]
            libro.setCopiasLicenciadas(libro.getCopiasLicenciadas() + lineaARemover.getCantidad());
            lineas.remove(lineaARemover);
            
            // Actualizar total [cite: 106]
            this.total -= lineaARemover.getSubtotal();
        }
    }

    public double totalizarCompra() {
        double sumaSubtotales = 0;
        for (Linea l : lineas) {
            sumaSubtotales += l.getSubtotal();
        }
        // Incrementa en un 19% (IVA) y guarda en el total [cite: 142]
        this.total = sumaSubtotales * 1.19; 
        return this.total;
    }
    
    public double getTotal() { return total; }
    public String getNombreCliente() { return nombreCliente; }
    public ArrayList<Linea> getLineas() { return lineas; }
}