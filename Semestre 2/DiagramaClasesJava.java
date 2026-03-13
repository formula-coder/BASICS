import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

class Libro {
    public int id;
    public String titulo;
    public int stock;

    public Libro(int id, String titulo, int stock) {
        this.id = id;
        this.titulo = titulo;
        this.stock = stock;
    }

    public String serializar() {
        return id + "," + titulo + "," + stock;
    }

    public static Libro deserializar(String linea) {
        String[] partes = linea.split(",");
        int id = Integer.parseInt(partes[0]);
        String titulo = partes[1];
        int stock = Integer.parseInt(partes[2]);
        return new Libro(id, titulo, stock);
    }

    public void mostrar() {
        System.out.println("Id: " + id + " | Titulo: " + titulo + " | Stock: " + stock);
    }
}

class BibliotecaArchivo {
    private static final String ARCHIVO = "libros.txt";

    public static void crearArchivo() {
        try {
            File archivo = new File(ARCHIVO);
            if (!archivo.exists()) {
                archivo.createNewFile();
            }
        } catch (IOException e) {
            System.out.println("No se pudo crear el archivo.");
        }
    }

    public static void mostrarLibros() {
        crearArchivo();
        BufferedReader lector = null;

        try {
            lector = new BufferedReader(new FileReader(ARCHIVO));
            String linea = lector.readLine();

            if (linea == null) {
                System.out.println("No hay libros registrados.");
            }

            while (linea != null) {
                Libro libro = Libro.deserializar(linea);
                libro.mostrar();
                linea = lector.readLine();
            }
        } catch (IOException e) {
            System.out.println("No se pudo leer el archivo.");
        } finally {
            try {
                if (lector != null) {
                    lector.close();
                }
            } catch (IOException e) {
                System.out.println("No se pudo cerrar el archivo.");
            }
        }
    }

    public static void modificarStock(int idLibro, int cantidad) {
        crearArchivo();
        BufferedReader lector = null;
        PrintWriter escritor = null;

        try {
            List<Libro> libros = new ArrayList<Libro>();
            lector = new BufferedReader(new FileReader(ARCHIVO));
            String linea = lector.readLine();

            while (linea != null) {
                Libro libro = Libro.deserializar(linea);
                if (libro.id == idLibro) {
                    libro.stock = libro.stock + cantidad;
                    if (libro.stock < 0) {
                        libro.stock = 0;
                    }
                }
                libros.add(libro);
                linea = lector.readLine();
            }

            lector.close();
            lector = null;

            escritor = new PrintWriter(new FileWriter(ARCHIVO));
            for (int i = 0; i < libros.size(); i++) {
                escritor.println(libros.get(i).serializar());
            }
        } catch (IOException e) {
            System.out.println("No se pudo modificar el stock.");
        } finally {
            try {
                if (lector != null) {
                    lector.close();
                }
            } catch (IOException e) {
                System.out.println("No se pudo cerrar el lector.");
            }

            if (escritor != null) {
                escritor.close();
            }
        }
    }
}

class ListaDinamica {
    private String[] datos;
    private int capacidad;
    private int cantidad;

    public ListaDinamica() {
        this.capacidad = 2;
        this.cantidad = 0;
        this.datos = new String[capacidad];
    }

    private void redimensionar() {
        String[] nuevo = new String[capacidad * 2];

        for (int i = 0; i < cantidad; i++) {
            nuevo[i] = datos[i];
        }

        capacidad = capacidad * 2;
        datos = nuevo;
    }

    public void agregar(String valor) {
        if (cantidad == capacidad) {
            redimensionar();
        }
        datos[cantidad] = valor;
        cantidad = cantidad + 1;
    }

    public void mostrar() {
        for (int i = 0; i < cantidad; i++) {
            System.out.println(datos[i]);
        }
    }
}

class Nodo {
    public int dato;
    public Nodo siguiente;

    public Nodo(int dato) {
        this.dato = dato;
        this.siguiente = null;
    }
}

class ListaEnlazada {
    private Nodo cabeza;

    public ListaEnlazada() {
        this.cabeza = null;
    }

    public void insertar(int valor) {
        Nodo nuevo = new Nodo(valor);
        if (cabeza == null) {
            cabeza = nuevo;
            return;
        }

        Nodo actual = cabeza;
        while (actual.siguiente != null) {
            actual = actual.siguiente;
        }
        actual.siguiente = nuevo;
    }

    public void imprimir() {
        Nodo actual = cabeza;
        while (actual != null) {
            System.out.println(actual.dato);
            actual = actual.siguiente;
        }
    }
}

public class DiagramaClasesJava {
    public static void main(String[] args) {
        ListaDinamica listaDinamica = new ListaDinamica();
        listaDinamica.agregar("Uno");
        listaDinamica.agregar("Dos");
        listaDinamica.mostrar();

        ListaEnlazada listaEnlazada = new ListaEnlazada();
        listaEnlazada.insertar(10);
        listaEnlazada.insertar(20);
        listaEnlazada.imprimir();

        BibliotecaArchivo.crearArchivo();
        BibliotecaArchivo.mostrarLibros();
    }
}