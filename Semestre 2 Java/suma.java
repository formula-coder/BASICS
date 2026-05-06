public class suma {
    public static void main(String args[]){
        int materia1 = 8;
        int materia2 = 9;
        int materia3 = 10;
        int suma = (materia1 + materia2 + materia3) / 3;
         System.out.println("El promedio de las materias es: " + suma);
        if( suma >= 6){
            System.out.println("El alumno aprobó "+ suma);
        }
        else{
            System.out.println("El alumno reprobó "+ suma);
        }
}
}
