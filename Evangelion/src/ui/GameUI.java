package ui;

import model.*;
import game.*;
import network.*;
import persistence.*;
import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class GameUI extends JFrame {
    private static final Color PANEL_BG = new Color(10, 14, 24, 210);
    private static final Color PANEL_BORDER = new Color(255, 255, 255, 35);
    private static final Color TEXT_COLOR = new Color(232, 238, 255);
    private static final Color ACCENT = new Color(95, 178, 255);
    private static final Color DANGER = new Color(255, 99, 122);
    private static final Color SUCCESS = new Color(88, 214, 141);

    private JTextArea combatLogArea;
    private JTextArea turnDetailArea;
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
    private CharacterSpritePanel playerSpritePanel;
    private CharacterSpritePanel opponentSpritePanel;
    private StatusCardPanel playerStatusCard;
    private StatusCardPanel opponentStatusCard;
    private BattleConsolePanel consolePanel;

    private CombatSystem combatSystem;
    private GameClient client;
    private GameServer server;
    private boolean isServer;
    private List<String> strategyList;
    private int strategyIndex;
    private boolean useStrategyFile;
    private int turnCounter = 0;

    public GameUI() {
        setTitle("Mecha Duel");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 750);
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

            connectButton.setEnabled(false);

            if (isServer) {
                JOptionPane.showMessageDialog(dialog, "Abriendo servidor en puerto " + port + "...\nEsperando conexión del cliente...");

                new Thread(() -> {
                    try {
                        server = new GameServer();
                        server.start(port);

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
        dialog.setLayout(new BorderLayout());
        dialog.getContentPane().setBackground(Color.WHITE);

        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.setBackground(Color.WHITE);
        
        JPanel optionPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        optionPanel.setBackground(Color.WHITE);
        optionPanel.setBorder(BorderFactory.createEmptyBorder(10, 20, 0, 20));
        
        JRadioButton newRobotRadio = new JRadioButton("Nuevo Robot", true);
        JRadioButton loadRobotRadio = new JRadioButton("Cargar Robot Guardado");
        ButtonGroup optionGroup = new ButtonGroup();
        optionGroup.add(newRobotRadio);
        optionGroup.add(loadRobotRadio);
        
        optionPanel.add(newRobotRadio);
        optionPanel.add(loadRobotRadio);
        
        JPanel loadPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        loadPanel.setBackground(Color.WHITE);
        loadPanel.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));
        loadPanel.setVisible(false);
        
        JLabel selectLabel = new JLabel("Seleccionar robot guardado:");
        JComboBox<String> savedRobotsCombo = new JComboBox<>();
        savedRobotsCombo.setPreferredSize(new Dimension(250, 30));
        loadPanel.add(selectLabel);
        loadPanel.add(savedRobotsCombo);
        
        JPanel inputPanel = new JPanel(new GridLayout(0, 2, 10, 12));
        inputPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        inputPanel.setBackground(Color.WHITE);

        JTextField nameField = new JTextField();
        JTextField atkField = new JTextField("25");
        JTextField defField = new JTextField("25");
        JTextField spdField = new JTextField("25");
        JTextField nrgField = new JTextField("25");
        
        inputPanel.add(createStyledLabel("Nombre del Robot:"));
        inputPanel.add(nameField);
        inputPanel.add(createStyledLabel("Ataque (ATK) [0-100]:"));
        inputPanel.add(atkField);
        inputPanel.add(createStyledLabel("Defensa (DEF) [0-100]:"));
        inputPanel.add(defField);
        inputPanel.add(createStyledLabel("Velocidad (SPD) [0-100]:"));
        inputPanel.add(spdField);
        inputPanel.add(createStyledLabel("Energía (NRG) [0-100]:"));
        inputPanel.add(nrgField);
        
        // Cargar lista de robots guardados
        List<String> robotNames = new ArrayList<>();
        try {
            List<model.Robot> robots = RobotPersistence.loadAllRobots();
            for (model.Robot r : robots) {
                robotNames.add(r.getName());
            }
        } catch (Exception e) {
            robotNames = new ArrayList<>();
        }
        
        // Variables finales para usar en lambdas
        final List<String> finalRobotNames = new ArrayList<>(robotNames);
        final JComboBox<String> finalCombo = savedRobotsCombo;
        final JTextField finalNameField = nameField;
        final JTextField finalAtkField = atkField;
        final JTextField finalDefField = defField;
        final JTextField finalSpdField = spdField;
        final JTextField finalNrgField = nrgField;
        
        savedRobotsCombo.removeAllItems();
        if (finalRobotNames.isEmpty()) {
            savedRobotsCombo.addItem("(No hay robots guardados)");
            savedRobotsCombo.setEnabled(false);
        } else {
            savedRobotsCombo.setEnabled(true);
            for (String name : finalRobotNames) {
                savedRobotsCombo.addItem(name);
            }
            savedRobotsCombo.setSelectedIndex(0);
            cargarRobotSeleccionado((String) savedRobotsCombo.getSelectedItem(), 
                finalNameField, finalAtkField, finalDefField, finalSpdField, finalNrgField);
        }
        
        savedRobotsCombo.addActionListener(e -> {
            String selected = (String) finalCombo.getSelectedItem();
            if (selected != null && !selected.isEmpty() && !selected.equals("(No hay robots guardados)")) {
                cargarRobotSeleccionado(selected, finalNameField, finalAtkField, 
                    finalDefField, finalSpdField, finalNrgField);
            }
        });
        
        newRobotRadio.addActionListener(e -> {
            loadPanel.setVisible(false);
            finalNameField.setText("");
            finalAtkField.setText("25");
            finalDefField.setText("25");
            finalSpdField.setText("25");
            finalNrgField.setText("25");
            dialog.pack();
        });
        
        loadRobotRadio.addActionListener(e -> {
            loadPanel.setVisible(true);
            if (!finalRobotNames.isEmpty()) {
                cargarRobotSeleccionado((String) finalCombo.getSelectedItem(), 
                    finalNameField, finalAtkField, finalDefField, finalSpdField, finalNrgField);
            }
            dialog.pack();
        });
        
        JPanel bottomPanel = new JPanel(new BorderLayout());
        bottomPanel.setBorder(BorderFactory.createEmptyBorder(0, 20, 20, 20));
        bottomPanel.setBackground(Color.WHITE);

        JLabel totalLabel = new JLabel("Total: 100 (debe ser 100)");
        totalLabel.setFont(new Font("SansSerif", Font.BOLD, 14));
        totalLabel.setForeground(new Color(88, 214, 141));
        totalLabel.setHorizontalAlignment(SwingConstants.CENTER);

        JButton assembleButton = new JButton("ENSAMBLAR ROBOT");
        assembleButton.setFont(new Font("SansSerif", Font.BOLD, 14));
        assembleButton.setBackground(new Color(95, 178, 255));
        assembleButton.setForeground(Color.WHITE);
        assembleButton.setFocusPainted(false);
        assembleButton.setBorder(BorderFactory.createEmptyBorder(12, 20, 12, 20));
        assembleButton.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));

        JPanel sumPanel = new JPanel(new FlowLayout());
        sumPanel.setBackground(Color.WHITE);
        JLabel sumValueLabel = new JLabel("Suma actual: 100");
        sumValueLabel.setFont(new Font("SansSerif", Font.PLAIN, 12));
        sumPanel.add(sumValueLabel);

        Runnable updateSum = () -> {
            try {
                int atk = Integer.parseInt(finalAtkField.getText().trim());
                int def = Integer.parseInt(finalDefField.getText().trim());
                int spd = Integer.parseInt(finalSpdField.getText().trim());
                int nrg = Integer.parseInt(finalNrgField.getText().trim());
                int sum = atk + def + spd + nrg;
                sumValueLabel.setText("Suma actual: " + sum);
                if (sum == 100) {
                    sumValueLabel.setForeground(new Color(88, 214, 141));
                    totalLabel.setForeground(new Color(88, 214, 141));
                    totalLabel.setText("Total: " + sum + " (CORRECTO)");
                } else {
                    sumValueLabel.setForeground(Color.RED);
                    totalLabel.setForeground(Color.RED);
                    totalLabel.setText("Total: " + sum + " (DEBE SER 100)");
                }
            } catch (NumberFormatException ex) {
                sumValueLabel.setText("Suma actual: ?");
                sumValueLabel.setForeground(Color.ORANGE);
            }
        };

        finalAtkField.addKeyListener(new KeyAdapter() {
            public void keyReleased(KeyEvent e) { updateSum.run(); }
        });
        finalDefField.addKeyListener(new KeyAdapter() {
            public void keyReleased(KeyEvent e) { updateSum.run(); }
        });
        finalSpdField.addKeyListener(new KeyAdapter() {
            public void keyReleased(KeyEvent e) { updateSum.run(); }
        });
        finalNrgField.addKeyListener(new KeyAdapter() {
            public void keyReleased(KeyEvent e) { updateSum.run(); }
        });

        bottomPanel.add(totalLabel, BorderLayout.NORTH);
        bottomPanel.add(sumPanel, BorderLayout.CENTER);
        bottomPanel.add(assembleButton, BorderLayout.SOUTH);
        
        JPanel northPanel = new JPanel(new BorderLayout());
        northPanel.add(optionPanel, BorderLayout.NORTH);
        northPanel.add(loadPanel, BorderLayout.CENTER);
        
        mainPanel.add(northPanel, BorderLayout.NORTH);
        mainPanel.add(inputPanel, BorderLayout.CENTER);
        mainPanel.add(bottomPanel, BorderLayout.SOUTH);
        
        dialog.add(mainPanel, BorderLayout.CENTER);
        
        assembleButton.addActionListener(e -> {
            String robotName = finalNameField.getText().trim();
            
            if (robotName.isEmpty()) {
                JOptionPane.showMessageDialog(dialog, "❌ Ingrese un nombre para el robot!");
                return;
            }

            int atk, def, spd, nrg;
            try {
                atk = Integer.parseInt(finalAtkField.getText().trim());
                def = Integer.parseInt(finalDefField.getText().trim());
                spd = Integer.parseInt(finalSpdField.getText().trim());
                nrg = Integer.parseInt(finalNrgField.getText().trim());
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(dialog, "❌ Todos los valores deben ser números enteros!");
                return;
            }

            if (atk < 0 || atk > 100 || def < 0 || def > 100 || spd < 0 || spd > 100 || nrg < 0 || nrg > 100) {
                JOptionPane.showMessageDialog(dialog, "❌ Las estadísticas deben estar entre 0 y 100!");
                return;
            }

            if (atk + def + spd + nrg != 100) {
                JOptionPane.showMessageDialog(dialog, "❌ La suma de las estadísticas debe ser 100!\n" +
                        "Actualmente suma: " + (atk + def + spd + nrg));
                return;
            }

            Stats stats = new Stats(atk, def, spd, nrg);
            model.Robot robot = new model.Robot(robotName, stats);

            try {
                String statsStr = String.format("%d,%d,%d,%d,%s", atk, def, spd, nrg, robotName);
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
        
        updateSum.run();
        
        dialog.pack();
        dialog.setMinimumSize(new Dimension(500, 400));
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    private void cargarRobotSeleccionado(String robotName, JTextField nameField, JTextField atkField, 
                                          JTextField defField, JTextField spdField, JTextField nrgField) {
        try {
            model.Robot loadedRobot = RobotPersistence.loadRobot(robotName);
            if (loadedRobot != null) {
                nameField.setText(loadedRobot.getName());
                atkField.setText(String.valueOf(loadedRobot.getStats().getAtk()));
                defField.setText(String.valueOf(loadedRobot.getStats().getDef()));
                spdField.setText(String.valueOf(loadedRobot.getStats().getSpd()));
                nrgField.setText(String.valueOf(loadedRobot.getStats().getNrg()));
            }
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, "Error al cargar el robot: " + ex.getMessage());
        }
    }

    private JLabel createStyledLabel(String text) {
        JLabel label = new JLabel(text);
        label.setFont(new Font("SansSerif", Font.BOLD, 13));
        label.setForeground(Color.BLACK);
        return label;
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

        try {
            strategyList = CombatLogPersistence.loadStrategy("estrategia.txt");
            useStrategyFile = !strategyList.isEmpty();
        } catch (IOException e) {
            useStrategyFile = false;
        }
    }

    private void setupUI() {
        getContentPane().removeAll();
        getContentPane().setBackground(new Color(4, 8, 15));

        JPanel root = new JPanel(new BorderLayout(14, 14));
        root.setBorder(BorderFactory.createEmptyBorder(14, 14, 14, 14));
        root.setOpaque(false);

        JPanel topPanel = createHudHeader();

        combatLogArea = new JTextArea();
        combatLogArea.setEditable(false);
        combatLogArea.setOpaque(false);
        combatLogArea.setForeground(TEXT_COLOR);
        combatLogArea.setFont(new Font("Consolas", Font.PLAIN, 12));
        JScrollPane scrollPane = new JScrollPane(combatLogArea);
        scrollPane.setOpaque(false);
        scrollPane.getViewport().setOpaque(false);
        scrollPane.setBorder(BorderFactory.createEmptyBorder());
        scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

        turnDetailArea = new JTextArea();
        turnDetailArea.setEditable(false);
        turnDetailArea.setOpaque(true);
        turnDetailArea.setBackground(new Color(10, 14, 24));
        turnDetailArea.setForeground(new Color(188, 195, 215));
        turnDetailArea.setFont(new Font("Consolas", Font.PLAIN, 12));
        turnDetailArea.setBorder(BorderFactory.createEmptyBorder(8, 12, 8, 12));
        JScrollPane turnDetailScroll = new JScrollPane(turnDetailArea);
        turnDetailScroll.setBorder(BorderFactory.createTitledBorder(
            BorderFactory.createLineBorder(ACCENT, 1),
            " DETALLE DE TURNOS",
            TitledBorder.LEFT,
            TitledBorder.TOP,
            new Font("SansSerif", Font.BOLD, 12),
            ACCENT
        ));
        turnDetailScroll.setPreferredSize(new Dimension(400, 250));

        turnLabel = new JLabel("Turno: Esperando...");
        turnLabel.setForeground(TEXT_COLOR);
        turnLabel.setFont(new Font("SansSerif", Font.BOLD, 15));
        turnLabel.setHorizontalAlignment(SwingConstants.CENTER);

        JPanel buttonPanel = createActionBar();
        attackButton = createGameButton("ATTACK", ACCENT);
        specialButton = createGameButton("SPECIAL", new Color(176, 110, 255));
        dodgeButton = createGameButton("DODGE", new Color(255, 186, 73));
        healButton = createGameButton("HEAL", SUCCESS);
        chargeButton = createGameButton("CHARGE", DANGER);

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

        consolePanel = new BattleConsolePanel(scrollPane);
        consolePanel.setLayout(new BorderLayout(0, 10));
        consolePanel.setBorder(BorderFactory.createEmptyBorder(12, 12, 12, 12));

        JPanel statusRow = new JPanel(new GridLayout(1, 2, 14, 0));
        statusRow.setOpaque(false);

        playerStatusCard = new StatusCardPanel("JUGADOR", ACCENT);
        opponentStatusCard = new StatusCardPanel("RIVAL", DANGER);
        statusRow.add(playerStatusCard);
        statusRow.add(opponentStatusCard);

        JPanel overlayPanel = new JPanel(new BorderLayout(0, 12));
        overlayPanel.setOpaque(false);
        overlayPanel.add(topPanel, BorderLayout.NORTH);
        overlayPanel.add(statusRow, BorderLayout.CENTER);
        overlayPanel.add(turnLabel, BorderLayout.SOUTH);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        splitPane.setOpaque(false);
        splitPane.setBorder(BorderFactory.createEmptyBorder());

        BattleFieldPanel battleFieldPanel = new BattleFieldPanel();
        battleFieldPanel.setLayout(new BorderLayout(0, 12));
        battleFieldPanel.setBorder(BorderFactory.createEmptyBorder(8, 8, 8, 8));
        battleFieldPanel.add(overlayPanel, BorderLayout.NORTH);
        battleFieldPanel.add(consolePanel, BorderLayout.CENTER);
        battleFieldPanel.add(createCharacterStrip(), BorderLayout.SOUTH);

        splitPane.setLeftComponent(battleFieldPanel);
        splitPane.setRightComponent(turnDetailScroll);
        splitPane.setResizeWeight(0.65);
        splitPane.setDividerLocation(620);

        JPanel actionBarShell = new JPanel(new BorderLayout());
        actionBarShell.setOpaque(true);
        actionBarShell.setBackground(PANEL_BG);
        actionBarShell.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(PANEL_BORDER, 1),
                BorderFactory.createEmptyBorder(10, 10, 10, 10)
        ));
        actionBarShell.add(buttonPanel, BorderLayout.CENTER);

        root.add(splitPane, BorderLayout.CENTER);
        root.add(actionBarShell, BorderLayout.SOUTH);

        setContentPane(root);

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

        turnCounter++;
        
        model.Robot player = combatSystem.getPlayer();
        model.Robot opponent = combatSystem.getOpponent();
        
        StringBuilder sb = new StringBuilder();
        sb.append("\n");
        sb.append("================================================================================\n");
        sb.append("                               TURNO ").append(turnCounter).append("\n");
        sb.append("================================================================================\n");
        turnDetailArea.append(sb.toString());
        
        String result = combatSystem.executeMove(player, opponent, move);
        
        String moveIcon = getMoveIcon(move);
        String moveName = getMoveName(move);
        
        turnDetailArea.append(" " + moveIcon + " " + player.getName() + " usa " + moveName + "\n");
        turnDetailArea.append(" Resultado: " + result + "\n");
        turnDetailArea.append("--------------------------------------------------------------------------------\n");
        
        Move opponentMove = simulateOpponentMoveLogic();
        String opponentResult = combatSystem.executeMove(opponent, player, opponentMove);
        
        String oppMoveIcon = getMoveIcon(opponentMove);
        String oppMoveName = getMoveName(opponentMove);
        
        turnDetailArea.append(" " + oppMoveIcon + " " + opponent.getName() + " usa " + oppMoveName + "\n");
        turnDetailArea.append(" Resultado: " + opponentResult + "\n");
        turnDetailArea.append("================================================================================\n\n");

        updateStatsDisplay();

        if (combatSystem.isGameOver()) {
            endGame();
        }
    }
    
    private Move simulateOpponentMoveLogic() {
        Move[] moves = {Move.ATTACK, Move.ATTACK, Move.ATTACK, Move.SPECIAL, Move.HEAL};
        return moves[(int)(Math.random() * moves.length)];
    }

    private String getMoveIcon(Move move) {
        switch (move) {
            case ATTACK: return "⚔️";
            case SPECIAL: return "✨";
            case DODGE: return "🛡️";
            case HEAL: return "💊";
            case CHARGE: return "⚡";
            default: return "❓";
        }
    }

    private String getMoveName(Move move) {
        switch (move) {
            case ATTACK: return "ATAQUE NORMAL";
            case SPECIAL: return "ATAQUE ESPECIAL";
            case DODGE: return "ESQUIVE";
            case HEAL: return "CURACIÓN";
            case CHARGE: return "CARGA";
            default: return "DESCONOCIDO";
        }
    }

    private void updateStatsDisplay() {
        playerStatsLabel.setText("Jugador: " + combatSystem.getPlayer().getStats().toString());
        opponentStatsLabel.setText("Rival: " + combatSystem.getOpponent().getStats().toString());
        combatLogArea.append(combatSystem.getCombatLog().get(combatSystem.getCombatLog().size() - 1) + "\n");
        combatLogArea.setCaretPosition(combatLogArea.getDocument().getLength());
        if (playerStatusCard != null) {
            playerStatusCard.updateFromRobot(combatSystem.getPlayer());
        }
        if (opponentStatusCard != null) {
            opponentStatusCard.updateFromRobot(combatSystem.getOpponent());
        }
        if (playerCharacterLabel != null) {
            playerCharacterLabel.setText(combatSystem.getPlayer().getName());
        }
        if (opponentCharacterLabel != null) {
            opponentCharacterLabel.setText(combatSystem.getOpponent().getName());
        }
    }

    private void endGame() {
        model.Robot winner = combatSystem.getWinner();
        
        StringBuilder finalMsg = new StringBuilder();
        finalMsg.append("\n");
        finalMsg.append("================================================================================\n");
        finalMsg.append("                              FIN DEL JUEGO\n");
        finalMsg.append("================================================================================\n");
        finalMsg.append("                    GANADOR: ").append(winner.getName()).append("\n");
        finalMsg.append("================================================================================\n\n");
        turnDetailArea.append(finalMsg.toString());
        
        JOptionPane.showMessageDialog(this, "¡Fin del juego! Ganador: " + winner.getName());

        int option = JOptionPane.showConfirmDialog(this, "¿Guardar configuración del robot?", "Guardar Robot", JOptionPane.YES_NO_OPTION);
        if (option == JOptionPane.YES_OPTION) {
            try {
                RobotPersistence.saveRobot(combatSystem.getPlayer());
                JOptionPane.showMessageDialog(this, "Robot guardado en robots.bin");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Error guardando robot: " + ex.getMessage());
            }
        }

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

    private JPanel createHudHeader() {
        JPanel header = new JPanel(new GridLayout(1, 2, 12, 0));
        header.setOpaque(false);
        header.setBorder(BorderFactory.createEmptyBorder(4, 4, 0, 4));

        playerStatsLabel = createHeaderStatLabel("Jugador: --");
        opponentStatsLabel = createHeaderStatLabel("Rival: --");

        header.add(wrapPanel(playerStatsLabel));
        header.add(wrapPanel(opponentStatsLabel));
        return header;
    }

    private JLabel createHeaderStatLabel(String text) {
        JLabel label = new JLabel(text);
        label.setForeground(TEXT_COLOR);
        label.setFont(new Font("SansSerif", Font.BOLD, 14));
        return label;
    }

    private JPanel wrapPanel(JComponent component) {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setOpaque(true);
        panel.setBackground(PANEL_BG);
        panel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(PANEL_BORDER, 1),
                BorderFactory.createEmptyBorder(10, 12, 10, 12)
        ));
        panel.add(component, BorderLayout.CENTER);
        return panel;
    }

    private JPanel createActionBar() {
        JPanel panel = new JPanel(new GridLayout(1, 5, 10, 0));
        panel.setOpaque(false);
        panel.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 0));
        return panel;
    }

    private JButton createGameButton(String text, Color baseColor) {
        JButton button = new JButton(text);
        button.setFont(new Font("SansSerif", Font.BOLD, 14));
        button.setForeground(Color.WHITE);
        button.setFocusPainted(false);
        button.setUI(new javax.swing.plaf.basic.BasicButtonUI());
        button.setContentAreaFilled(true);
        button.setBorderPainted(false);
        button.setBorder(BorderFactory.createEmptyBorder(14, 18, 14, 18));
        button.setBackground(baseColor.darker().darker());
        button.setOpaque(true);
        button.setRolloverEnabled(true);
        button.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                if (button.isEnabled()) {
                    button.setBackground(baseColor);
                }
            }

            @Override
            public void mouseExited(MouseEvent e) {
                button.setBackground(baseColor.darker().darker());
            }
        });
        return button;
    }

    private JPanel createCharacterStrip() {
        JPanel strip = new JPanel(new GridLayout(1, 2, 18, 0));
        strip.setOpaque(false);
        strip.setBorder(BorderFactory.createEmptyBorder(12, 12, 16, 12));

        playerSpritePanel = new CharacterSpritePanel(
                "Jugador",
                loadImage(
                        "Evangelion/assets/player.png",
                        "Evangelion/assets/player-character.png",
                        "Evangelion/assets/asuka.png",
                        "Evangelion/assets/eva.png"
                ),
                new Color(172, 58, 64)
        );
        opponentSpritePanel = new CharacterSpritePanel(
                "Rival",
                loadImage(
                        "Evangelion/assets/opponent.png",
                        "Evangelion/assets/opponent-character.png",
                        "Evangelion/assets/shinji.png",
                        "Evangelion/assets/kaworu.png"
                ),
                new Color(52, 92, 164)
        );

        playerCharacterLabel = playerSpritePanel.getLabel();
        opponentCharacterLabel = opponentSpritePanel.getLabel();

        strip.add(playerSpritePanel);
        strip.add(opponentSpritePanel);
        return strip;
    }

    private BufferedImage loadImage(String... paths) {
        for (String path : paths) {
            File file = new File(path);
            if (file.exists()) {
                try {
                    return ImageIO.read(file);
                } catch (IOException ignored) {
                }
            }
        }
        return null;
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

            g2.setPaint(new GradientPaint(0, 0, new Color(0, 0, 0, 30), 0, getHeight(), new Color(0, 0, 0, 140)));
            g2.fillRect(0, 0, getWidth(), getHeight());

            g2.setColor(new Color(255, 255, 255, 20));
            g2.drawRoundRect(10, 10, getWidth() - 20, getHeight() - 20, 26, 26);

            g2.dispose();
        }
    }

    private class BattleConsolePanel extends JPanel {
        private final JComponent content;

        BattleConsolePanel(JComponent content) {
            this.content = content;
            setOpaque(true);
            setBackground(PANEL_BG);
            setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(PANEL_BORDER, 1),
                    BorderFactory.createEmptyBorder(10, 10, 10, 10)
            ));
            setLayout(new BorderLayout());
            add(createConsoleHeader(), BorderLayout.NORTH);
            add(content, BorderLayout.CENTER);
        }

        private JComponent createConsoleHeader() {
            JLabel title = new JLabel("BATTLE LOG");
            title.setForeground(ACCENT);
            title.setFont(new Font("SansSerif", Font.BOLD, 13));
            title.setBorder(BorderFactory.createEmptyBorder(0, 2, 8, 2));
            return title;
        }
    }

    private class StatusCardPanel extends JPanel {
        private final JLabel nameLabel;
        private final JLabel hpLabel;
        private final JLabel nrgLabel;
        private final JProgressBar hpBar;
        private final JProgressBar nrgBar;
        private final Color accentColor;

        StatusCardPanel(String title, Color accentColor) {
            this.accentColor = accentColor;
            setLayout(new GridLayout(4, 1, 0, 6));
            setOpaque(true);
            setBackground(PANEL_BG);
            setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createMatteBorder(2, 2, 2, 2, accentColor),
                    BorderFactory.createEmptyBorder(10, 12, 10, 12)
            ));

            nameLabel = new JLabel(title);
            nameLabel.setForeground(TEXT_COLOR);
            nameLabel.setFont(new Font("SansSerif", Font.BOLD, 15));

            hpLabel = createMetricLabel("HP: 100 / 100");
            nrgLabel = createMetricLabel("NRG: 0 / 100");

            hpBar = createBar(new Color(255, 91, 91));
            nrgBar = createBar(accentColor);

            add(nameLabel);
            add(hpLabel);
            add(hpBar);
            add(nrgLabel);
            add(nrgBar);
        }

        void updateFromRobot(model.Robot robot) {
            int hp = robot.getStats().getHp();
            int nrg = robot.getStats().getNrg();
            hpLabel.setText("HP: " + hp + " / 100");
            nrgLabel.setText("NRG: " + nrg + " / 100");
            hpBar.setValue(hp);
            nrgBar.setValue(nrg);
            nameLabel.setText(robot.getName());
        }

        private JLabel createMetricLabel(String text) {
            JLabel label = new JLabel(text);
            label.setForeground(TEXT_COLOR);
            label.setFont(new Font("SansSerif", Font.PLAIN, 13));
            return label;
        }

        private JProgressBar createBar(Color fillColor) {
            JProgressBar bar = new JProgressBar(0, 100);
            bar.setValue(100);
            bar.setStringPainted(false);
            bar.setBorderPainted(false);
            bar.setForeground(fillColor);
            bar.setBackground(new Color(255, 255, 255, 35));
            bar.setUI(new javax.swing.plaf.basic.BasicProgressBarUI() {
                @Override
                protected Color getSelectionBackground() {
                    return Color.WHITE;
                }

                @Override
                protected Color getSelectionForeground() {
                    return Color.WHITE;
                }
            });
            return bar;
        }
    }

    private class CharacterSpritePanel extends JPanel {
        private final BufferedImage spriteImage;
        private final JLabel nameLabel;
        private float bobOffset = 0f;

        CharacterSpritePanel(String name, BufferedImage spriteImage, Color accentColor) {
            this.spriteImage = spriteImage;
            setOpaque(false);
            setPreferredSize(new Dimension(220, 210));
            setLayout(new BorderLayout());
            setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(new Color(255, 255, 255, 60), 1),
                    BorderFactory.createEmptyBorder(8, 8, 8, 8)
            ));

            nameLabel = new JLabel(name, SwingConstants.CENTER);
            nameLabel.setForeground(Color.WHITE);
            nameLabel.setFont(new Font("SansSerif", Font.BOLD, 16));
            nameLabel.setOpaque(true);
            nameLabel.setBackground(new Color(accentColor.getRed(), accentColor.getGreen(), accentColor.getBlue(), 180));
            nameLabel.setBorder(BorderFactory.createEmptyBorder(8, 10, 8, 10));
            add(nameLabel, BorderLayout.SOUTH);

            Timer animationTimer = new Timer(60, e -> {
                bobOffset += 0.12f;
                repaint();
            });
            animationTimer.start();
        }

        JLabel getLabel() {
            return nameLabel;
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g.create();
            g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int availableWidth = getWidth() - 16;
            int availableHeight = getHeight() - nameLabel.getPreferredSize().height - 20;
            int spriteY = 8 + Math.round((float) Math.sin(bobOffset) * 4f);

            if (spriteImage != null) {
                int imageWidth = spriteImage.getWidth();
                int imageHeight = spriteImage.getHeight();
                double scale = Math.min((double) availableWidth / imageWidth, (double) availableHeight / imageHeight);
                int drawWidth = (int) (imageWidth * scale);
                int drawHeight = (int) (imageHeight * scale);
                int drawX = (getWidth() - drawWidth) / 2;
                int drawY = spriteY + ((availableHeight - drawHeight) / 2);
                g2.drawImage(spriteImage, drawX, drawY, drawWidth, drawHeight, null);
            } else {
                g2.setColor(new Color(255, 255, 255, 18));
                g2.fillRoundRect(18, 18 + spriteY, getWidth() - 36, availableHeight - 20, 22, 22);
                g2.setColor(new Color(255, 255, 255, 90));
                g2.drawRoundRect(18, 18 + spriteY, getWidth() - 36, availableHeight - 20, 22, 22);
                g2.setColor(Color.WHITE);
                g2.drawString("Coloca el PNG aquí", 34, 60 + spriteY);
                g2.drawString("para ver el personaje", 34, 82 + spriteY);
            }

            g2.dispose();
        }
    }
}