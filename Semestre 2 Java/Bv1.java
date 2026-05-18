import java.io.Serializable;

public class Bv1 implements Bv2, Serializable {

    protected String name;
    protected int age;

    public Bv1(String name, int age){
        this.name = name;
        this.age = age;
    }

    @Override
    public void displayinfo(){
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
     
    }
}
