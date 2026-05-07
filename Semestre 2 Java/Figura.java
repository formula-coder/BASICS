import java.util.Scanner;

abstract class Figura {
    public abstract double calcularArea();
    public abstract double calcularPerimetro();
}

class Cuadrado extends Figura {
    private final double lado;

    public Cuadrado(double lado) {
        this.lado = lado;
    }

    @Override
    public double calcularArea() {
        return lado * lado;
    }

    @Override
    public double calcularPerimetro() {
        return 4 * lado;
    }
}

class Rectangulo extends Figura {
    private final double base;
    private final double altura;

    public Rectangulo(double base, double altura) {
        this.base = base;
        this.altura = altura;
    }

    @Override
    public double calcularArea() {
        return base * altura;
    }

    @Override
    public double calcularPerimetro() {
        return 2 * (base + altura);
    }
}

class Circulo extends Figura {
    private final double radio;

    public Circulo(double radio) {
        this.radio = radio;
    }

    @Override
    public double calcularArea() {
        return Math.PI * radio * radio;
    }

    @Override
    public double calcularPerimetro() {
        return 2 * Math.PI * radio;
    }
}

class Triangulo extends Figura {
    private final double base;
    private final double altura;

    public Triangulo(double base, double altura) {
        this.base = base;
        this.altura = altura;
    }

    @Override
    public double calcularArea() {
        return (base * altura) / 2;
    }

    @Override
    public double calcularPerimetro() {
        return 3 * base;
    }
}

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Menu de figuras");
        System.out.println("1. Cuadrado");
        System.out.println("2. Rectangulo");
        System.out.println("3. Circulo");
        System.out.println("4. Triangulo");
        System.out.print("Elige una opcion: ");

        int opcion = scanner.nextInt();
        Figura figura = null;

        if (opcion == 1) {
            System.out.print("Ingresa el lado: ");
            double lado = scanner.nextDouble();
            figura = new Cuadrado(lado);
        } else if (opcion == 2) {
            System.out.print("Ingresa la base: ");
            double base = scanner.nextDouble();
            System.out.print("Ingresa la altura: ");
            double altura = scanner.nextDouble();
            figura = new Rectangulo(base, altura);
        } else if (opcion == 3) {
            System.out.print("Ingresa el radio: ");
            double radio = scanner.nextDouble();
            figura = new Circulo(radio);
        } else if (opcion == 4) {
            System.out.print("Ingresa la base: ");
            double base = scanner.nextDouble();
            System.out.print("Ingresa la altura: ");
            double altura = scanner.nextDouble();
            figura = new Triangulo(base, altura);
        } else {
            System.out.println("Opcion invalida.");
        }

        if (figura != null) {
            System.out.println();
            System.out.println("Resultado: " + figura.getClass().getSimpleName());
            System.out.printf("Area: %.2f%n", figura.calcularArea());
            System.out.printf("Perimetro: %.2f%n", figura.calcularPerimetro());
        }

        scanner.close();
    }
}