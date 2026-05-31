import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Libreria {
    private ArrayList<Libro> catalogo;
    private ArrayList<Compra> compras;

    public Libreria() {
        catalogo = new ArrayList<>();
        compras = new ArrayList<>();
        cargarDatosPrueba(); // Carga datos para probar la funcionalidad
    }

    // --- MÉTODOS DEL PARCIAL ---

    public Libro buscarLibro(String titulo) {
        for (Libro libro : catalogo) {
            if (libro.getTitulo().equalsIgnoreCase(titulo)) {
                return libro;
            }
        }
        return null;
    }

    public ArrayList<Compra> comprasSuperanTope(double p_tope) {
        ArrayList<Compra> superanTope = new ArrayList<>();
        for (Compra compra : compras) {
            double sumaSubtotales = 0;
            for (Linea linea : compra.getLineas()) {
                sumaSubtotales += linea.getSubtotal();
            }
            if (sumaSubtotales > p_tope) {
                superanTope.add(compra);
            }
        }
        return superanTope;
    }

    public double totalizarValorLibros() {
        double valorTotal = 0;
        for (Libro libro : catalogo) {
            valorTotal += (libro.getCopiasLicenciadas() * libro.calcularPrecio());
        }
        return valorTotal;
    }

    public void generarReporteLibrosDigitales() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("librosDigitales.txt"))) {
            writer.println("--- REPORTE DE LIBROS DIGITALES ---");
            for (Libro libro : catalogo) {
                if (libro instanceof LibroDigital) {
                    writer.println("Código: " + libro.getCodigo() + 
                                   " | Título: " + libro.getTitulo() + 
                                   " | Copias: " + libro.getCopiasLicenciadas() + 
                                   " | Precio Calculado: $" + libro.calcularPrecio());
                }
            }
            System.out.println("-> Reporte generado en 'librosDigitales.txt'.");
        } catch (IOException e) {
            System.out.println("Error al generar reporte: " + e.getMessage());
        }
    }

    // --- MÉTODO PARA INICIALIZAR DATOS ---
    private void cargarDatosPrueba() {
        catalogo.add(new LibroFisico(101, "Java Basico", 50000, 10, 5000)); // Precio final 55000
        catalogo.add(new LibroDigital(102, "POO Avanzado", 40000, 20, 4000)); // Precio final 36000
        catalogo.add(new LibroFisico(103, "Estructuras de Datos", 70000, 5, 8000)); // Precio final 78000
    }

    // --- MENÚ Y EJECUCIÓN (MAIN) ---
    public static void main(String[] args) {
        Libreria sistema = new Libreria();
        Scanner sc = new Scanner(System.in);
        int opcion = -1;

        while (opcion != 0) {
            System.out.println("\n===== SISTEMA DE LIBRERÍA =====");
            System.out.println("1. Mostrar Catálogo");
            System.out.println("2. Buscar Libro");
            System.out.println("3. Realizar una Compra");
            System.out.println("4. Ver compras que superan un tope");
            System.out.println("5. Generar Reporte de Libros Digitales (.txt)");
            System.out.println("6. Totalizar Valor de Libros en Catálogo");
            System.out.println("0. Salir");
            System.out.print("Seleccione una opción: ");
            opcion = sc.nextInt();
            sc.nextLine(); // Limpiar buffer

            switch (opcion) {
                case 1:
                    System.out.println("\n--- CATÁLOGO ---");
                    for (Libro l : sistema.catalogo) {
                        String tipo = (l instanceof LibroFisico) ? "Físico" : "Digital";
                        System.out.println("- " + l.getTitulo() + " (" + tipo + ") | Disp: " + l.getCopiasLicenciadas() + " | Precio Total: $" + l.calcularPrecio());
                    }
                    break;
                case 2:
                    System.out.print("Ingrese el título del libro: ");
                    String tit = sc.nextLine();
                    Libro lib = sistema.buscarLibro(tit);
                    if (lib != null) {
                        System.out.println("Libro encontrado: " + lib.getTitulo() + " - Disp: " + lib.getCopiasLicenciadas());
                    } else {
                        System.out.println("Libro no encontrado.");
                    }
                    break;
                case 3:
                    System.out.print("Nombre del Cliente: ");
                    String nombre = sc.nextLine();
                    Compra nuevaCompra = new Compra(nombre, sistema);
                    
                    int opcCompra = -1;
                    while (opcCompra != 0) {
                        System.out.println("\n-- MENÚ DE COMPRA --");
                        System.out.println("1. Agregar Línea");
                        System.out.println("2. Remover Línea");
                        System.out.println("0. Finalizar Compra");
                        System.out.print("Seleccione: ");
                        opcCompra = sc.nextInt();
                        sc.nextLine(); // Limpiar buffer

                        if (opcCompra == 1) {
                            System.out.print("Título del libro: ");
                            String tituloCompra = sc.nextLine();
                            System.out.print("Cantidad: ");
                            int cant = sc.nextInt();
                            sc.nextLine();
                            try {
                                nuevaCompra.agregarLinea(tituloCompra, cant);
                                System.out.println("Línea agregada con éxito.");
                            } catch (Exception e) {
                                System.out.println("Error: " + e.getMessage());
                            }
                        } else if (opcCompra == 2) {
                            System.out.print("Título del libro a remover: ");
                            String tituloRemover = sc.nextLine();
                            nuevaCompra.removerLinea(tituloRemover);
                            System.out.println("Se removió la línea si existía.");
                        }
                    }
                    
                    double granTotal = nuevaCompra.totalizarCompra();
                    sistema.compras.add(nuevaCompra);
                    System.out.println("-> Compra finalizada. Total con IVA (19%): $" + granTotal);
                    break;
                case 4:
                    System.out.print("Ingrese el tope (subtotal sin IVA): ");
                    double tope = sc.nextDouble();
                    ArrayList<Compra> listaTope = sistema.comprasSuperanTope(tope);
                    System.out.println("Compras que superan $" + tope + ":");
                    for (Compra c : listaTope) {
                        System.out.println("- Cliente: " + c.getNombreCliente() + " | Total final: $" + c.getTotal());
                    }
                    break;
                case 5:
                    sistema.generarReporteLibrosDigitales();
                    break;
                case 6:
                    double valorTotal = sistema.totalizarValorLibros();
                    System.out.println("El valor total de todos los libros (Copias * Precio Final) es: $" + valorTotal);
                    break;
                case 0:
                    System.out.println("Saliendo del sistema...");
                    break;
                default:
                    System.out.println("Opción no válida.");
            }
        }
        sc.close();
    }
}