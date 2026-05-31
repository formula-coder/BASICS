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
                return l; // Retorna si existe
            }
        }
        return null; // Retorna NULL si no existe
    }

    public ArrayList<Compra> comprasSuperanTope(double p_tope) {
        ArrayList<Compra> superan = new ArrayList<>();
        for (Compra c : compras) {
            double sumaSubtotales = 0;
            for (Linea l : c.getLineas()) {
                sumaSubtotales += l.getSubtotal();
            }
            if (sumaSubtotales > p_tope) { // Mayor al parámetro que llega
                superan.add(c);
            }
        }
        return superan;
    }

    public double totalizarValorLibros() {
        double valorTotal = 0;
        for (Libro l : catalogo) {
            // Producto de copias licenciadas por el precio total polimórfico
            valorTotal += (l.getCopiasLicenciadas() * l.calcularPrecio());
        }
        return valorTotal;
    }

    public void GenerarReporteLibrosDigitales() {
        // Genera reporte en un archivo de texto
        try (PrintWriter writer = new PrintWriter(new FileWriter("librosDigitales.txt"))) {
            writer.println("--- REPORTE DE LIBROS DIGITALES ---");
            for (Libro l : catalogo) {
                if (l instanceof LibroDigital) {
                    writer.println("Título: " + l.getTitulo() + " | Precio: $" + l.calcularPrecio());
                }
            }
            System.out.println("Reporte generado exitosamente en 'librosDigitales.txt'.");
        } catch (IOException e) {
            System.out.println("Error al generar el reporte: " + e.getMessage());
        }
    }


    public void generarReciboCompra(Compra compra) {
        try (PrintWriter writer = new PrintWriter(new FileWriter("compraCliente.txt", true))) {
            writer.println("Cliente: " + compra.getNombreCliente());
            writer.println("Total (con 19% IVA): $" + compra.totalizarCompra());
            writer.println("-------------------------");
        } catch (IOException e) {
            System.out.println("Error guardando el recibo.");
        }
    }


    private void cargarDatosPrueba() {
        catalogo.add(new LibroFisico(1, "Java Basico", 50000, 10, 5000));
        catalogo.add(new LibroDigital(2, "Patrones Diseño", 60000, 50, 10000));
        catalogo.add(new LibroFisico(3, "Estructuras de Datos", 75000, 5, 8000));
    }

    public static void main(String[] args) {
        Libreria sistema = new Libreria();
        Scanner scanner = new Scanner(System.in);
        int opcion = -1;

        do {
            System.out.println("\n=== MENÚ LIBRERÍA JAVERIANA ===");
            System.out.println("1. Ver Catálogo y Totalizar Valor de Libros");
            System.out.println("2. Realizar una Compra (Agregar/Remover Líneas)");
            System.out.println("3. Buscar Libro por Título");
            System.out.println("4. Consultar Compras que Superan un Tope");
            System.out.println("5. Generar Reporte de Libros Digitales");
            System.out.println("0. Salir");
            
            while (true) {
                System.out.print("Seleccione una opción: ");
                String entradaOpcion = scanner.nextLine().trim();
                try {
                    opcion = Integer.parseInt(entradaOpcion);
                    if (opcion >= 0 && opcion <= 5) {
                        break; // Sale del bucle si la opción es válida
                    } else {
                        System.out.println("Error: Opción fuera de rango. Ingrese un número entre 0 y 5.");
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Error: Debe ingresar un número válido, no letras ni símbolos.");
                }
            }

            switch (opcion) {
                case 1:
                    System.out.println("\nCatálogo actual:");
                    for (Libro l : sistema.catalogo) {
                        System.out.println("- " + l.getTitulo() + " (Copias: " + l.getCopiasLicenciadas() + ")");
                    }
                    System.out.println("Valor total del inventario: $" + sistema.totalizarValorLibros());
                    break;
                case 2:
                    String nombre = "";
                    while (true) {
                        System.out.print("Nombre del cliente: ");
                        nombre = scanner.nextLine().trim();
                        if (!nombre.isEmpty()) {
                            break; // Sale del bucle si el nombre no está vacío
                        }
                        System.out.println("Error: El nombre no puede estar vacío. Intente de nuevo.");
                    }
                    
                    Compra nuevaCompra = new Compra(nombre);
                    boolean comprando = true;
                    
                    while (comprando) {
                        System.out.println("\n  a. Agregar libro");
                        System.out.println("  b. Remover libro");
                        System.out.println("  c. Finalizar compra");
                        System.out.print("  Opción: ");
                        String opcCompra = scanner.nextLine().trim();
                        
                        if (opcCompra.equalsIgnoreCase("a")) {
                            System.out.print("Título del libro a comprar: ");
                            String tit = scanner.nextLine().trim();
                            
                            int cant = 0;
                            while (true) {
                                System.out.print("Cantidad: ");
                                String entradaCant = scanner.nextLine().trim();
                                try {
                                    cant = Integer.parseInt(entradaCant);
                                    if (cant > 0) break;
                                    System.out.println("Error: La cantidad debe ser mayor a 0.");
                                } catch (NumberFormatException e) {
                                    System.out.println("Error: Ingrese un número válido para la cantidad.");
                                }
                            }

                            try {
                                nuevaCompra.agregarLinea(tit, cant, sistema.catalogo);
                                System.out.println("Línea agregada. Subtotal actualizado.");
                            } catch (LibroException e) {
                                System.out.println("ERROR: " + e.getMessage());
                            }
                            
                        } else if (opcCompra.equalsIgnoreCase("b")) {
                            System.out.print("Título del libro a remover: ");
                            String titRemover = scanner.nextLine().trim();
                            nuevaCompra.removerLinea(titRemover);
                            System.out.println("Línea removida (si existía).");
                            
                        } else if (opcCompra.equalsIgnoreCase("c")) {
                            double totalFinal = nuevaCompra.totalizarCompra();
                            sistema.compras.add(nuevaCompra);
                            sistema.generarReciboCompra(nuevaCompra);
                            System.out.println("Compra finalizada. Total a pagar (IVA inc): $" + totalFinal);
                            System.out.println("Recibo generado en compraCliente.txt.");
                            comprando = false;
                            
                        } else {
                            System.out.println("Opción incorrecta. Escoja entre a, b y c.");
                        }
                    }
                    break;
                case 3:
                    System.out.print("Ingrese título exacto a buscar: ");
                    String t = scanner.nextLine().trim();
                    Libro encontrado = sistema.buscarLibro(t);
                    if (encontrado != null) {
                        System.out.println("¡Libro encontrado! Código: " + encontrado.codigo + " | Precio calculado: $" + encontrado.calcularPrecio());
                    } else {
                        System.out.println("Libro no encontrado.");
                    }
                    break;
                case 4:

                    double tope = 0;
                    while (true) {
                        System.out.print("Ingrese el valor tope a consultar: $");
                        String entradaTope = scanner.nextLine().trim();
                        try {
                            tope = Double.parseDouble(entradaTope);
                            if (tope >= 0) break;
                            System.out.println("Error: El valor no puede ser negativo.");
                        } catch (NumberFormatException e) {
                            System.out.println("Error: Ingrese un número válido.");
                        }
                    }

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
            }

            if (opcion != 0) {
                System.out.print("\n¿Desea volver al menú principal? (si/no): ");
                String volver = scanner.nextLine().trim().toLowerCase();
                
                // Obliga al usuario a responder si o no
                while (!volver.equals("si") && !volver.equals("s") && !volver.equals("sí") && !volver.equals("no") && !volver.equals("n")) {
                    System.out.print("Error: Por favor ingrese 'si' o 'no': ");
                    volver = scanner.nextLine().trim().toLowerCase();
                }

                // Si responde que no, le asignamos 0 a la opción para que termine el programa
                if (volver.equals("no") || volver.equals("n")) {
                    opcion = 0; 
                    System.out.println("Saliendo del sistema...");
                }
            }

        } while (opcion != 0);
        
        scanner.close();
    }
}