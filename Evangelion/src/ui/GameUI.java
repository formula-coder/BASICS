package ui;

import model.*;
import game.*;
import network.*;
import persistence.*;
import javax.swing.*;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.List;

public class GameUI extends JFrame {
    private JTextArea combatLogArea;
    private JLabel playerStatsLabel;
    private JLabel opponentStatsLabel;
    private JLabel turnLabel;
    private JButton attackButton;
    private JButton specialButton;
    private JButton dodgeButton;
    private JButton healButton;
    private JButton chargeButton;
    private JLabel playerCharacterLabel;
    private JLabel opponentCharacterLabel;

    private CombatSystem combatSystem;
    private GameClient client;
    private GameServer server;
    private boolean isServer;
    private List<String> strategyList;
    private int strategyIndex;
    private boolean useStrategyFile;

    public GameUI() {
        setTitle("Mecha Duel");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setLayout(new BorderLayout());

        showConnectionDialog();
    }

    private void showConnectionDialog() {
        JDialog dialog = new JDialog(this, "Configuración de Conexión", true);
        dialog.setLayout(new GridLayout(4, 2));

        JRadioButton serverButton = new JRadioButton("Crear Partida (Server)");
        JRadioButton clientButton = new JRadioButton("Unirse a Partida (Client)");
        ButtonGroup group = new ButtonGroup();
        group.add(serverButton);
        group.add(clientButton);

        JTextField ipField = new JTextField("localhost");
        JTextField portField = new JTextField("8080");

        dialog.add(new JLabel("Rol:"));
        dialog.add(serverButton);
        dialog.add(new JLabel(""));
        dialog.add(clientButton);
        dialog.add(new JLabel("IP:"));
        dialog.add(ipField);
        dialog.add(new JLabel("Puerto:"));
        dialog.add(portField);

        JButton connectButton = new JButton("Conectar");
        connectButton.addActionListener(e -> {
            if (!serverButton.isSelected() && !clientButton.isSelected()) {
                JOptionPane.showMessageDialog(dialog, "Selecciona un rol: crear partida o unirte a una partida.");
                return;
            }

            isServer = serverButton.isSelected();

            int port;
            try {
                port = Integer.parseInt(portField.getText().trim());
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(dialog, "El puerto debe ser un número válido.");
                return;
            }

            // Deshabilitar el botón para evitar clicks múltiples
            connectButton.setEnabled(false);

            if (isServer) {
                // Para SERVER: mostrar mensaje antes de intentar conectar
                JOptionPane.showMessageDialog(dialog, "Abriendo servidor en puerto " + port + "...\nEsperando conexión del cliente...");

                // Usar un hilo separado para no bloquear la UI
                new Thread(() -> {
                    try {
                        server = new GameServer();
                        server.start(port);

                        // Conectar exitoso
                        SwingUtilities.invokeLater(() -> {
                            JOptionPane.showMessageDialog(dialog, "¡Cliente conectado exitosamente!");
                            dialog.dispose();
                            showRobotAssembly();
                        });
                    } catch (IOException ex) {
                        SwingUtilities.invokeLater(() -> {
                            JOptionPane.showMessageDialog(dialog, "Error en servidor: " + ex.getMessage());
                            connectButton.setEnabled(true);
                        });
                    }
                }).start();
            } else {
                // Para CLIENT
                try {
                    client = new GameClient();
                    client.connect(ipField.getText().trim(), port);
                    JOptionPane.showMessageDialog(dialog, "¡Conectado al servidor!");
                    dialog.dispose();
                    showRobotAssembly();
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(dialog, "No se pudo conectar a " + ipField.getText().trim() + ":" + port +
                            "\nAsegúrate de haber abierto primero la partida en modo Server en esa IP y puerto.\n" +
                            "Detalle técnico: " + ex.getMessage());
                    connectButton.setEnabled(true);
                }
            }
        });

        dialog.add(connectButton);
        dialog.pack();
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    private void showRobotAssembly() {
        JDialog dialog = new JDialog(this, "Ensamble del Robot", true);
        dialog.setLayout(new GridLayout(6, 2));

        JTextField nameField = new JTextField();
        JSlider atkSlider = new JSlider(0, 100, 25);
        JSlider defSlider = new JSlider(0, 100, 25);
        JSlider spdSlider = new JSlider(0, 100, 25);
        JSlider nrgSlider = new JSlider(0, 100, 25);

        JLabel totalLabel = new JLabel("Total: 100");

        atkSlider.addChangeListener(e -> updateTotal(atkSlider, defSlider, spdSlider, nrgSlider, totalLabel));
        defSlider.addChangeListener(e -> updateTotal(atkSlider, defSlider, spdSlider, nrgSlider, totalLabel));
        spdSlider.addChangeListener(e -> updateTotal(atkSlider, defSlider, spdSlider, nrgSlider, totalLabel));
        nrgSlider.addChangeListener(e -> updateTotal(atkSlider, defSlider, spdSlider, nrgSlider, totalLabel));

        dialog.add(new JLabel("Nombre:"));
        dialog.add(nameField);
        dialog.add(new JLabel("Ataque (ATK):"));
        dialog.add(atkSlider);
        dialog.add(new JLabel("Defensa (DEF):"));
        dialog.add(defSlider);
        dialog.add(new JLabel("Velocidad (SPD):"));
        dialog.add(spdSlider);
        dialog.add(new JLabel("Energía (NRG):"));
        dialog.add(nrgSlider);
        dialog.add(new JLabel("Total puntos:"));
        dialog.add(totalLabel);

        JButton assembleButton = new JButton("Ensamble Robot");
        assembleButton.addActionListener(e -> {
            int atk = atkSlider.getValue();
            int def = defSlider.getValue();
            int spd = spdSlider.getValue();
            int nrg = nrgSlider.getValue();

            if (atk + def + spd + nrg != 100) {
                JOptionPane.showMessageDialog(dialog, "Los puntos deben sumar 100!");
                return;
            }

            if (nameField.getText().trim().isEmpty()) {
                JOptionPane.showMessageDialog(dialog, "Ingrese un nombre para el robot!");
                return;
            }

            Stats stats = new Stats(atk, def, spd, nrg);
            model.Robot robot = new model.Robot(nameField.getText(), stats);

            try {
                String statsStr = String.format("%d,%d,%d,%d,%s", atk, def, spd, nrg, nameField.getText());
                if (isServer) {
                    server.sendRobotStats(statsStr);
                    String opponentStats = server.receiveRobotStats();
                    parseAndStartGame(robot, opponentStats);
                } else {
                    client.sendRobotStats(statsStr);
                    String opponentStats = client.receiveRobotStats();
                    parseAndStartGame(robot, opponentStats);
                }
                dialog.dispose();
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(dialog, "Error enviando estadísticas: " + ex.getMessage());
            }
        });

        dialog.add(assembleButton);
        dialog.pack();
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    private void updateTotal(JSlider atk, JSlider def, JSlider spd, JSlider nrg, JLabel total) {
        int sum = atk.getValue() + def.getValue() + spd.getValue() + nrg.getValue();
        total.setText("Total: " + sum + " (debe ser 100)");
        if (sum != 100) {
            total.setForeground(Color.RED);
        } else {
            total.setForeground(Color.GREEN);
        }
    }

    private void parseAndStartGame(model.Robot player, String opponentStatsStr) {
        String[] parts = opponentStatsStr.split(",");
        int atk = Integer.parseInt(parts[0]);
        int def = Integer.parseInt(parts[1]);
        int spd = Integer.parseInt(parts[2]);
        int nrg = Integer.parseInt(parts[3]);
        String name = parts[4];

        Stats opponentStats = new Stats(atk, def, spd, nrg);
        model.Robot opponent = new model.Robot(name, opponentStats);

        combatSystem = new CombatSystem(player, opponent);
        setupUI();

        // Verificar archivo de estrategia solo para cargarlo, pero no activar combate automático por defecto.
        try {
            strategyList = CombatLogPersistence.loadStrategy("estrategia.txt");
            useStrategyFile = !strategyList.isEmpty();
        } catch (IOException e) {
            useStrategyFile = false;
        }
    }

    private void setupUI() {
        JPanel topPanel = new JPanel(new GridLayout(1, 2));
        playerStatsLabel = new JLabel("Jugador: " + combatSystem.getPlayer().getStats().toString());
        opponentStatsLabel = new JLabel("Rival: " + combatSystem.getOpponent().getStats().toString());
        topPanel.add(playerStatsLabel);
        topPanel.add(opponentStatsLabel);

        combatLogArea = new JTextArea();
        combatLogArea.setEditable(false);
        combatLogArea.setOpaque(false);
        combatLogArea.setForeground(Color.WHITE);
        combatLogArea.setFont(new Font("Consolas", Font.PLAIN, 14));
        JScrollPane scrollPane = new JScrollPane(combatLogArea);
        scrollPane.setOpaque(false);
        scrollPane.getViewport().setOpaque(false);

        turnLabel = new JLabel("Turno: Esperando...");
        turnLabel.setForeground(Color.WHITE);
        turnLabel.setHorizontalAlignment(SwingConstants.CENTER);

        JPanel buttonPanel = new JPanel(new GridLayout(1, 5));
        buttonPanel.setOpaque(false);
        attackButton = new JButton("ATTACK");
        specialButton = new JButton("SPECIAL");
        dodgeButton = new JButton("DODGE");
        healButton = new JButton("HEAL");
        chargeButton = new JButton("CHARGE");

        attackButton.addActionListener(e -> performMove(Move.ATTACK));
        specialButton.addActionListener(e -> performMove(Move.SPECIAL));
        dodgeButton.addActionListener(e -> performMove(Move.DODGE));
        healButton.addActionListener(e -> performMove(Move.HEAL));
        chargeButton.addActionListener(e -> performMove(Move.CHARGE));

        buttonPanel.add(attackButton);
        buttonPanel.add(specialButton);
        buttonPanel.add(dodgeButton);
        buttonPanel.add(healButton);
        buttonPanel.add(chargeButton);

        JPanel overlayPanel = new JPanel(new BorderLayout());
        overlayPanel.setOpaque(false);
        overlayPanel.add(topPanel, BorderLayout.NORTH);
        overlayPanel.add(scrollPane, BorderLayout.CENTER);
        overlayPanel.add(turnLabel, BorderLayout.SOUTH);

        BattleFieldPanel battleFieldPanel = new BattleFieldPanel();
        battleFieldPanel.setLayout(new BorderLayout());
        battleFieldPanel.add(overlayPanel, BorderLayout.CENTER);
        battleFieldPanel.add(createCharacterStrip(), BorderLayout.SOUTH);

        add(battleFieldPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.EAST);

        setVisible(true);

        enableButtons(true);
        startCombatLoop();
    }

    private void startCombatLoop() {
        Thread combatThread = new Thread(() -> {
            while (!combatSystem.isGameOver()) {
                model.Robot nextTurn = combatSystem.getTurnManager().getNextTurn();
                if (nextTurn != null) {
                    final model.Robot currentTurn = nextTurn;
                    SwingUtilities.invokeLater(() -> {
                        turnLabel.setText("Turno de: " + currentTurn.getName());
                        if (currentTurn == combatSystem.getOpponent()) {
                            simulateOpponentMove();
                        }
                    });
                }

                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    break;
                }
            }
        });
        combatThread.start();
    }

    private void simulateOpponentMove() {
        Move[] moves = {Move.ATTACK, Move.ATTACK, Move.ATTACK, Move.SPECIAL, Move.HEAL};
        Move randomMove = moves[(int)(Math.random() * moves.length)];
        performMove(randomMove);
    }

    private void performMove(Move move) {
        if (combatSystem.isGameOver()) {
            endGame();
            return;
        }

        String result = combatSystem.executeMove(combatSystem.getPlayer(), combatSystem.getOpponent(), move);

        // Enviar resultado al oponente
        try {
            if (isServer) {
                server.sendMove(result);
            } else {
                client.sendMove(result);
            }
        } catch (IOException e) {
            combatLogArea.append("Error enviando movimiento: " + e.getMessage() + "\n");
        }

        updateStatsDisplay();

        if (combatSystem.isGameOver()) {
            endGame();
        }
    }

    private void updateStatsDisplay() {
        playerStatsLabel.setText("Jugador: " + combatSystem.getPlayer().getStats().toString());
        opponentStatsLabel.setText("Rival: " + combatSystem.getOpponent().getStats().toString());
        combatLogArea.append(combatSystem.getCombatLog().get(combatSystem.getCombatLog().size() - 1) + "\n");
        combatLogArea.setCaretPosition(combatLogArea.getDocument().getLength());
        if (playerCharacterLabel != null) {
            playerCharacterLabel.setText(combatSystem.getPlayer().getName());
        }
        if (opponentCharacterLabel != null) {
            opponentCharacterLabel.setText(combatSystem.getOpponent().getName());
        }
    }

    private void endGame() {
        model.Robot winner = combatSystem.getWinner();
        JOptionPane.showMessageDialog(this, "¡Fin del juego! Ganador: " + winner.getName());

        // Guardar configuración del robot
        int option = JOptionPane.showConfirmDialog(this, "¿Guardar configuración del robot?", "Guardar Robot", JOptionPane.YES_NO_OPTION);
        if (option == JOptionPane.YES_OPTION) {
            try {
                RobotPersistence.saveRobot(combatSystem.getPlayer());
                JOptionPane.showMessageDialog(this, "Robot guardado en robots.bin");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Error guardando robot: " + ex.getMessage());
            }
        }

        // Guardar historial del combate
        option = JOptionPane.showConfirmDialog(this, "¿Guardar historial del combate?", "Guardar Historial", JOptionPane.YES_NO_OPTION);
        if (option == JOptionPane.YES_OPTION) {
            try {
                CombatLogPersistence.saveCombatLog(combatSystem.getCombatLog(), "combate.log");
                JOptionPane.showMessageDialog(this, "Historial guardado en combate.log");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Error guardando historial: " + ex.getMessage());
            }
        }

        System.exit(0);
    }

    private void enableButtons(boolean enable) {
        attackButton.setEnabled(enable);
        specialButton.setEnabled(enable);
        dodgeButton.setEnabled(enable);
        healButton.setEnabled(enable);
        chargeButton.setEnabled(enable);
    }

    private JPanel createCharacterStrip() {
        JPanel strip = new JPanel(new GridLayout(1, 2, 24, 0));
        strip.setOpaque(false);
        strip.setBorder(BorderFactory.createEmptyBorder(12, 24, 20, 24));

        playerCharacterLabel = createCharacterLabel("Jugador");
        opponentCharacterLabel = createCharacterLabel("Rival");

        strip.add(playerCharacterLabel);
        strip.add(opponentCharacterLabel);
        return strip;
    }

    private JLabel createCharacterLabel(String text) {
        JLabel label = new JLabel(text, SwingConstants.CENTER);
        label.setForeground(Color.WHITE);
        label.setFont(new Font("SansSerif", Font.BOLD, 20));
        label.setPreferredSize(new Dimension(200, 120));
        label.setOpaque(true);
        label.setBackground(new Color(0, 0, 0, 120));
        label.setBorder(BorderFactory.createLineBorder(new Color(255, 255, 255, 140), 2));
        return label;
    }

    private BufferedImage loadBackgroundImage() {
        File[] candidates = {
                new File("Evangelion/assets/battle-background.png"),
                new File("Evangelion/assets/battle-background.jpg"),
                new File("Evangelion/assets/background.png"),
                new File("Evangelion/assets/background.jpg")
        };

        for (File candidate : candidates) {
            if (candidate.exists()) {
                try {
                    return ImageIO.read(candidate);
                } catch (IOException ignored) {
                }
            }
        }
        return null;
    }

    private class BattleFieldPanel extends JPanel {
        private final BufferedImage backgroundImage = loadBackgroundImage();

        BattleFieldPanel() {
            setOpaque(true);
            setBackground(new Color(20, 20, 28));
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g.create();
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            if (backgroundImage != null) {
                g2.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), null);
            } else {
                GradientPaint gradient = new GradientPaint(0, 0, new Color(30, 34, 48), 0, getHeight(), new Color(82, 112, 75));
                g2.setPaint(gradient);
                g2.fillRect(0, 0, getWidth(), getHeight());

                g2.setColor(new Color(255, 255, 255, 35));
                for (int i = 0; i < 8; i++) {
                    int x = 40 + i * 90;
                    g2.fillRoundRect(x, 25 + (i % 2) * 12, 60, 30, 20, 20);
                }
            }

            g2.dispose();
        }
    }
}