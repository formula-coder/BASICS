// Programa de un solo archivo que muestra funciones en Java (estilo C++)
public class Bv1 {

    private String name;
    private int age;

    public Bv1(String name, int age){
        this.name = name;
        this.age = age;
    }

    // Método de instancia: muestra la información del objeto
    public void displayinfo(){
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }

    // Ejercicio: métodos (funciones) en Java - muy sencillo
    // 1) Método estático que suma dos números y devuelve el resultado
    public static int sumar(int a, int b){
        return a + b;
    }

    // 2) Método de instancia que devuelve un saludo personalizado
    public String saludar(){
        return "Hola, " + name + "!";
    }

    // 3) Método que muestra cómo usar los anteriores (demostración)
    public static void ejercicioFunciones(){
        Bv1 ejemplo = new Bv1("Ana", 20);
        System.out.println("Ejemplo suma: 3 + 5 = " + sumar(3,5));
        System.out.println(ejemplo.saludar());
        ejemplo.displayinfo();
        System.out.println("También puedes crear tu propio objeto y llamar a sus métodos.");
    }

    // Main de prueba para ejecutar el ejercicio directamente (archivo único)
    public static void main(String[] args){
        ejercicioFunciones();
        // Ejemplo interactivo mínimo (opcional): crear objeto desde argumentos
        if(args.length >= 2){
            String n = args[0];
            int a = 0;
            try{ a = Integer.parseInt(args[1]); } catch(NumberFormatException ex){ }
            Bv1 usuario = new Bv1(n, a);
            System.out.println("--- Datos desde args ---");
            usuario.displayinfo();
        }
    }
}
