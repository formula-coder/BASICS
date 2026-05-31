// Archivo: Libreria.java
import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Libreria {
    private ArrayList<Libro> catalogo;
    private ArrayList<Compra> compras;

    public Libreria() {
        catalogo = new ArrayList<>();
        compras = new ArrayList<>();
        cargarDatosPrueba(); // Carga datos para poder probar el menú
    }

    public Libro buscarLibro(String titulo) {
        for (Libro l : catalogo) {
            if (l.getTitulo().equalsIgnoreCase(titulo)) {
                return l; // Retorna si existe [cite: 140]
            }
        }
        return null; // Retorna NULL si no existe [cite: 140]
    }

    public ArrayList<Compra> comprasSuperanTope(double p_tope) {
        ArrayList<Compra> superan = new ArrayList<>();
        for (Compra c : compras) {
            double sumaSubtotales = 0;
            for (Linea l : c.getLineas()) {
                sumaSubtotales += l.getSubtotal();
            }
            if (sumaSubtotales > p_tope) { // Mayor al parámetro que llega [cite: 102]
                superan.add(c);
            }
        }
        return superan;
    }

    public double totalizarValorLibros() {
        double valorTotal = 0;
        for (Libro l : catalogo) {
            // Producto de copias licenciadas por el precio total polimórfico [cite: 149]
            valorTotal += (l.getCopiasLicenciadas() * l.calcularPrecio());
        }
        return valorTotal;
    }

    public void GenerarReporteLibrosDigitales() {
        // Genera reporte en un archivo de texto [cite: 145]
        try (PrintWriter writer = new PrintWriter(new FileWriter("librosDigitales.txt"))) {
            writer.println("--- REPORTE DE LIBROS DIGITALES ---");
            for (Libro l : catalogo) {
                if (l instanceof LibroDigital) {
                    writer.println("Título: " + l.getTitulo() + " | Precio: $" + l.calcularPrecio());
                }
            }
            System.out.println("Reporte generado exitosamente en 'librosDigitales.txt'[cite: 146].");
        } catch (IOException e) {
            System.out.println("Error al generar el reporte: " + e.getMessage());
        }
    }

    // Método auxiliar para crear el recibo
    public void generarReciboCompra(Compra compra) {
        try (PrintWriter writer = new PrintWriter(new FileWriter("compraCliente.txt", true))) {
            writer.println("Cliente: " + compra.getNombreCliente());
            writer.println("Total (con 19% IVA): $" + compra.totalizarCompra());
            writer.println("-------------------------");
        } catch (IOException e) {
            System.out.println("Error guardando el recibo.");
        }
    }

    // Datos por defecto para evitar archivos vacíos en la prueba
    private void cargarDatosPrueba() {
        catalogo.add(new LibroFisico(1, "Java Basico", 50000, 10, 5000));
        catalogo.add(new LibroDigital(2, "Patrones Diseño", 60000, 50, 10000));
        catalogo.add(new LibroFisico(3, "Estructuras de Datos", 75000, 5, 8000));
    }

    public static void main(String[] args) {
        Libreria sistema = new Libreria();
        Scanner scanner = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n=== MENÚ LIBRERÍA JAVERIANA ===");
            System.out.println("1. Ver Catálogo y Totalizar Valor de Libros");
            System.out.println("2. Realizar una Compra (Agregar/Remover Líneas)");
            System.out.println("3. Buscar Libro por Título");
            System.out.println("4. Consultar Compras que Superan un Tope");
            System.out.println("5. Generar Reporte de Libros Digitales");
            System.out.println("0. Salir");
            System.out.print("Seleccione una opción: ");
            opcion = scanner.nextInt();
            scanner.nextLine(); 

            switch (opcion) {
                case 1:
                    System.out.println("\nCatálogo actual:");
                    for (Libro l : sistema.catalogo) {
                        System.out.println("- " + l.getTitulo() + " (Copias: " + l.getCopiasLicenciadas() + ")");
                    }
                    System.out.println("Valor total polimórfico del inventario: $" + sistema.totalizarValorLibros());
                    break;
                case 2:
                    System.out.print("Nombre del cliente: ");
                    String nombre = scanner.nextLine();
                    Compra nuevaCompra = new Compra(nombre);
                    
                    boolean comprando = true;
                    while (comprando) {
                        System.out.println("\n  a. Agregar libro");
                        System.out.println("  b. Remover libro");
                        System.out.println("  c. Finalizar compra");
                        System.out.print("  Opción: ");
                        String opcCompra = scanner.nextLine();
                        
                        if (opcCompra.equalsIgnoreCase("a")) {
                            System.out.print("Título del libro a comprar: ");
                            String tit = scanner.nextLine();
                            System.out.print("Cantidad: ");
                            int cant = scanner.nextInt();
                            scanner.nextLine();
                            try {
                                nuevaCompra.agregarLinea(tit, cant, sistema.catalogo);
                                System.out.println("Línea agregada. Subtotal actualizado.");
                            } catch (LibroException e) {
                                System.out.println("ERROR: " + e.getMessage());
                            }
                        } else if (opcCompra.equalsIgnoreCase("b")) {
                            System.out.print("Título del libro a remover: ");
                            String titRemover = scanner.nextLine();
                            nuevaCompra.removerLinea(titRemover);
                            System.out.println("Línea removida (si existía).");
                        } else if (opcCompra.equalsIgnoreCase("c")) {
                            double totalFinal = nuevaCompra.totalizarCompra();
                            sistema.compras.add(nuevaCompra);
                            sistema.generarReciboCompra(nuevaCompra);
                            System.out.println("Compra finalizada. Total a pagar (IVA inc): $" + totalFinal);
                            System.out.println("Recibo generado en compraCliente.txt[cite: 91].");
                            comprando = false;
                        }
                    }
                    break;
                case 3:
                    System.out.print("Ingrese título exacto a buscar: ");
                    String t = scanner.nextLine();
                    Libro encontrado = sistema.buscarLibro(t);
                    if (encontrado != null) {
                        System.out.println("¡Libro encontrado! Código: " + encontrado.codigo + " | Precio calculado: $" + encontrado.calcularPrecio());
                    } else {
                        System.out.println("Libro no encontrado.");
                    }
                    break;
                case 4:
                    System.out.print("Ingrese el valor tope a consultar: $");
                    double tope = scanner.nextDouble();
                    ArrayList<Compra> filtro = sistema.comprasSuperanTope(tope);
                    System.out.println("Compras que superan $" + tope + ": " + filtro.size());
                    for (Compra c : filtro) {
                        System.out.println("- Cliente: " + c.getNombreCliente() + " | Total: $" + c.getTotal());
                    }
                    break;
                case 5:
                    sistema.GenerarReporteLibrosDigitales();
                    break;
                case 0:
                    System.out.println("Saliendo del sistema...");
                    break;
                default:
                    System.out.println("Opción no válida.");
            }
        } while (opcion != 0);
        
        scanner.close();
    }
}