package persistence;

import java.io.*;
import java.util.List;

public class CombatLogPersistence {

    public static void saveCombatLog(List<String> combatLog, String filename) throws IOException {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            for (String log : combatLog) {
                writer.println(log);
            }
        }
    }

    public static List<String> loadStrategy(String filename) throws IOException {
        List<String> strategies = new java.util.ArrayList<>();
        File file = new File(filename);

        if (file.exists()) {
            try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    strategies.add(line.trim().toUpperCase());
                }
            }
        }

        return strategies;
    }
}