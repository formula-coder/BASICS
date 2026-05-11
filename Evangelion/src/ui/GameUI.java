package ui;

import model.*;
import game.*;
import network.*;
import persistence.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
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

    private CombatSystem combatSystem;
    private GameClient client;
    private GameServer server;
    private boolean isServer;
    private List<String> strategyList;
    private int strategyIndex;
    private boolean useStrategyFile;
    private Timer autoMoveTimer;

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
            isServer = serverButton.isSelected();
            int port = Integer.parseInt(portField.getText());

            try {
                if (isServer) {
                    server = new GameServer();
                    server.start(port);
                    JOptionPane.showMessageDialog(dialog, "Esperando conexión...");
                } else {
                    client = new GameClient();
                    client.connect(ipField.getText(), port);
                    JOptionPane.showMessageDialog(dialog, "Conectado!");
                }
                dialog.dispose();
                showRobotAssembly();
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(dialog, "Error de conexión: " + ex.getMessage());
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

        // Verificar archivo de estrategia
        try {
            strategyList = CombatLogPersistence.loadStrategy("estrategia.txt");
            useStrategyFile = !strategyList.isEmpty();
            if (useStrategyFile) {
                strategyIndex = 0;
                startAutoCombat();
            }
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
        JScrollPane scrollPane = new JScrollPane(combatLogArea);

        turnLabel = new JLabel("Turno: Esperando...");

        JPanel buttonPanel = new JPanel(new GridLayout(1, 5));
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

        add(topPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(turnLabel, BorderLayout.SOUTH);
        add(buttonPanel, BorderLayout.EAST);

        setVisible(true);

        if (!useStrategyFile) {
            enableButtons(true);
        }

        startCombatLoop();
    }

    private void startAutoCombat() {
        enableButtons(false);
        autoMoveTimer = new Timer(1000, e -> {
            if (!combatSystem.isGameOver() && strategyIndex < strategyList.size()) {
                String moveStr = strategyList.get(strategyIndex % strategyList.size());
                Move move = Move.fromString(moveStr);
                performMove(move);
                strategyIndex++;
            } else if (combatSystem.isGameOver()) {
                autoMoveTimer.stop();
                endGame();
            }
        });
        autoMoveTimer.start();
    }

    private void startCombatLoop() {
        Thread combatThread = new Thread(() -> {
            while (!combatSystem.isGameOver()) {
                model.Robot nextTurn = combatSystem.getTurnManager().getNextTurn();
                if (nextTurn != null) {
                    final model.Robot currentTurn = nextTurn;
                    SwingUtilities.invokeLater(() -> {
                        turnLabel.setText("Turno de: " + currentTurn.getName());
                        if (useStrategyFile) {
                            // Ya manejado por el timer
                        } else if (currentTurn == combatSystem.getOpponent()) {
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

        if (autoMoveTimer != null) {
            autoMoveTimer.stop();
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
}