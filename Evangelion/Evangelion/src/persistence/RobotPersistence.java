package persistence;

import model.Robot;
import java.io.*;
import java.util.*;

public class RobotPersistence {
    private static final String FILE_NAME = "robots.bin";

    public static void saveRobot(Robot robot) throws IOException {
        List<Robot> robots = loadAllRobots();

        // Reemplazar si ya existe
        boolean replaced = false;
        for (int i = 0; i < robots.size(); i++) {
            if (robots.get(i).getName().equals(robot.getName())) {
                robots.set(i, robot);
                replaced = true;
                break;
            }
        }
        if (!replaced) {
            robots.add(robot);
        }

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
            oos.writeObject(robots);
        }
    }

    @SuppressWarnings("unchecked")
    public static List<Robot> loadAllRobots() {
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            return new ArrayList<>();
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_NAME))) {
            return (List<Robot>) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            // Si hay error, retornar lista vacía
            System.err.println("Error cargando robots: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public static Robot loadRobot(String name) {
        try {
            List<Robot> robots = loadAllRobots();
            for (Robot robot : robots) {
                if (robot.getName().equals(name)) {
                    return robot;
                }
            }
        } catch (Exception e) {
            System.err.println("Error cargando robot específico: " + e.getMessage());
        }
        return null;
    }
}