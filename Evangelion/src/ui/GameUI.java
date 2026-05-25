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
    private int strategyIndex = 0;
    private boolean useStrategyFile;
    private int turnCounter = 0;

    private boolean isMyTurn = false;
    private boolean combatActive = true;
    private boolean gameEnded = false;

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

        List<String> robotNames = new ArrayList<>();
        try {
            List<model.Robot> robots = RobotPersistence.loadAllRobots();
            for (model.Robot r : robots) {
                robotNames.add(r.getName());
            }
        } catch (Exception e) {
            robotNames = new ArrayList<>();
        }

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
            strategyIndex = 0;
            if (useStrategyFile) {
                turnDetailArea.append("📄 Archivo de estrategia cargado con " + strategyList.size() + " movimientos.\n");
                turnDetailArea.append("🔄 El archivo se repetirá en bucle hasta que termine el combate.\n");
            } else {
                turnDetailArea.append("⚠️ No se encontró archivo estrategia.txt. Usa los botones para jugar.\n");
            }
        } catch (IOException e) {
            useStrategyFile = false;
            turnDetailArea.append("⚠️ Error cargando estrategia.txt. Usa los botones para jugar.\n");
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

        startCombatLoop();
    }

    private void startCombatLoop() {
        model.Robot player = combatSystem.getPlayer();
        model.Robot opponent = combatSystem.getOpponent();

        boolean playerStarts = player.getStats().getSpd() >= opponent.getStats().getSpd();
        isMyTurn = playerStarts;

        turnDetailArea.append("\n");
        turnDetailArea.append("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        turnDetailArea.append("║                              INICIO DEL COMBATE                              ║\n");
        turnDetailArea.append("╠════════════════════════════════════════════════════════════════════════════════╣\n");
        if (playerStarts) {
            turnDetailArea.append("║  🎯 " + player.getName() + " comienza primero (Velocidad: " + player.getStats().getSpd() +
                    " > " + opponent.getStats().getSpd() + ")" +
                    " ".repeat(Math.max(0, 40)) + "║\n");
        } else {
            turnDetailArea.append("║  🎯 " + opponent.getName() + " comienza primero (Velocidad: " + opponent.getStats().getSpd() +
                    " > " + player.getStats().getSpd() + ")" +
                    " ".repeat(Math.max(0, 40)) + "║\n");
        }
        turnDetailArea.append("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");

        startOpponentListener();

        if (isMyTurn) {
            turnLabel.setText("Tu turno! (" + player.getName() + ")");
            enableButtons(true);

            if (useStrategyFile) {
                turnDetailArea.append("🎮 Modo automático: Ejecutando estrategia...\n");
                Timer startTimer = new Timer(1000, e -> {
                    if (isMyTurn && !combatSystem.isGameOver() && !gameEnded) {
                        executeNextStrategyMove();
                    }
                });
                startTimer.setRepeats(false);
                startTimer.start();
            } else {
                turnDetailArea.append("🎮 Modo manual: Haz clic en un botón para comenzar.\n");
            }
        } else {
            turnLabel.setText("Turno de " + opponent.getName());
            enableButtons(false);
            turnDetailArea.append("⏳ Esperando que " + opponent.getName() + " realice su primer movimiento...\n");
        }
    }

    private void executeNextStrategyMove() {
        if (!useStrategyFile || combatSystem.isGameOver() || gameEnded) {
            return;
        }

        if (!isMyTurn) {
            return;
        }

        if (strategyIndex >= strategyList.size()) {
            strategyIndex = 0;
            turnDetailArea.append("\n🔄 CICLO COMPLETO - Reiniciando estrategia desde el principio 🔄\n\n");
        }

        if (strategyIndex >= strategyList.size()) {
            return;
        }

        final int currentIndex = strategyIndex;
        String moveStr = strategyList.get(currentIndex);
        Move move = Move.fromString(moveStr);

        turnDetailArea.append("📜 [Estrategia] Movimiento: " + moveStr + " (línea " + (currentIndex + 1) + ")\n");

        strategyIndex++;

        Timer timer = new Timer(800, e -> {
            if (isMyTurn && !combatSystem.isGameOver() && !gameEnded) {
                performMove(move);
            }
        });
        timer.setRepeats(false);
        timer.start();
    }

    private void startOpponentListener() {
        Thread listenerThread = new Thread(() -> {
            while (combatActive && !combatSystem.isGameOver() && !gameEnded) {
                try {
                    String receivedData = isServer ? server.receiveMove() : client.receiveMove();

                    if (receivedData != null && !receivedData.isEmpty()) {
                        if (receivedData.equals("GAME_OVER")) {
                            SwingUtilities.invokeLater(() -> {
                                if (!gameEnded) {
                                    endGame();
                                }
                            });
                            break;
                        }

                        // Formato: MOVEMENT:RESULT:DAMAGE:HEAL:NRG_CHANGE:TARGET_HP:ACTOR_HP
                        String[] parts = receivedData.split(":");
                        String moveStr = parts[0];
                        String result = parts.length > 1 ? parts[1] : "";
                        int damage = parts.length > 2 ? Integer.parseInt(parts[2]) : 0;
                        int heal = parts.length > 3 ? Integer.parseInt(parts[3]) : 0;
                        int nrgChange = parts.length > 4 ? Integer.parseInt(parts[4]) : 0;
                        int targetHp = parts.length > 5 ? Integer.parseInt(parts[5]) : 0;
                        int actorHp = parts.length > 6 ? Integer.parseInt(parts[6]) : 0;

                        Move opponentMove = Move.fromString(moveStr);
                        model.Robot opponent = combatSystem.getOpponent();
                        model.Robot player = combatSystem.getPlayer();

                        SwingUtilities.invokeLater(() -> {
                            if (combatSystem.isGameOver() || gameEnded) return;

                            turnCounter++;

                            StringBuilder sb = new StringBuilder();
                            sb.append("\n");
                            sb.append("================================================================================\n");
                            sb.append("                               TURNO ").append(turnCounter).append("\n");
                            sb.append("================================================================================\n");
                            sb.append(" ").append(opponent.getName()).append(" realiza su movimiento...\n");
                            turnDetailArea.append(sb.toString());

                            String moveIcon = getMoveIcon(opponentMove);
                            String moveName = getMoveName(opponentMove);

                            turnDetailArea.append(" " + moveIcon + " " + opponent.getName() + " usa " + moveName + "\n");

                            // APLICAR LOS EFECTOS REALES (los que ya calculó el atacante)
                            if (opponentMove == Move.ATTACK || opponentMove == Move.SPECIAL) {
                                if (result.equals("DODGE")) {
                                    turnDetailArea.append("   └─ ¡" + player.getName() + " esquivó el ataque! (Sin daño)\n");
                                } else if (result.equals("FAIL")) {
                                    turnDetailArea.append("   └─ Falló: Energía insuficiente\n");
                                } else {
                                    turnDetailArea.append("   └─ Causó " + damage + " de daño a " + player.getName() + "\n");
                                    player.getStats().setHp(targetHp);
                                    turnDetailArea.append("   └─ ❤️ " + player.getName() + " HP: " + (targetHp + damage) + " → " + targetHp + "\n");
                                }
                                // Aplicar cambio de energía
                                if (nrgChange != 0) {
                                    opponent.getStats().setNrg(opponent.getStats().getNrg() + nrgChange);
                                    if (opponent.getStats().getNrg() < 0) opponent.getStats().setNrg(0);
                                    if (opponent.getStats().getNrg() > 100) opponent.getStats().setNrg(100);
                                }
                            } else if (opponentMove == Move.HEAL) {
                                turnDetailArea.append("   └─ Recuperó " + heal + " HP\n");
                                opponent.getStats().setHp(targetHp);
                                turnDetailArea.append("   └─ ❤️ " + opponent.getName() + " HP: " + (targetHp - heal) + " → " + targetHp + "\n");
                            } else if (opponentMove == Move.CHARGE) {
                                int oldNrg = opponent.getStats().getNrg();
                                opponent.getStats().setNrg(oldNrg + nrgChange);
                                if (opponent.getStats().getNrg() > 100) opponent.getStats().setNrg(100);
                                turnDetailArea.append("   └─ Cargó " + nrgChange + " de energía\n");
                                turnDetailArea.append("   └─ ⚡ " + opponent.getName() + " NRG: " + oldNrg + " → " + opponent.getStats().getNrg() + "\n");
                            } else if (opponentMove == Move.DODGE) {
                                double prob = opponent.getDodgeCount() >= 2 ? 75 : 50;
                                turnDetailArea.append("   └─ Preparado para esquivar (Prob: " + (int)prob + "%)\n");
                                opponent.incrementDodgeCount();
                            }

                            turnDetailArea.append("--------------------------------------------------------------------------------\n");

                            updateStatsDisplay();

                            if (player.getStats().getHp() <= 0 || opponent.getStats().getHp() <= 0) {
                                combatSystem.getPlayer().getStats().setHp(player.getStats().getHp());
                                combatSystem.getOpponent().getStats().setHp(opponent.getStats().getHp());
                                sendGameOver();
                                endGame();
                                return;
                            }

                            isMyTurn = true;
                            turnLabel.setText("Tu turno! (" + player.getName() + ")");
                            enableButtons(true);

                            if (useStrategyFile && !gameEnded) {
                                turnDetailArea.append("🎮 Ejecutando siguiente movimiento de la estrategia...\n");
                                Timer timer = new Timer(500, e -> {
                                    if (isMyTurn && !combatSystem.isGameOver() && !gameEnded) {
                                        executeNextStrategyMove();
                                    }
                                });
                                timer.setRepeats(false);
                                timer.start();
                            } else if (!useStrategyFile && !gameEnded) {
                                turnDetailArea.append("🎮 Tu turno - Haz clic en un botón.\n");
                            }
                        });
                    }
                } catch (IOException e) {
                    if (combatActive && !combatSystem.isGameOver() && !gameEnded) {
                        SwingUtilities.invokeLater(() -> {
                            JOptionPane.showMessageDialog(null, "Error de comunicación: " + e.getMessage());
                            endGame();
                        });
                    }
                    break;
                } catch (Exception e) {
                    break;
                }
            }
        });
        listenerThread.setDaemon(true);
        listenerThread.start();
    }

    private void sendGameOver() {
        try {
            if (isServer) {
                server.sendMove("GAME_OVER");
            } else {
                client.sendMove("GAME_OVER");
            }
        } catch (IOException e) {
            // Ignorar
        }
    }

    private void performMove(Move move) {
        if (combatSystem.isGameOver() || gameEnded) {
            endGame();
            return;
        }

        if (!isMyTurn) {
            turnDetailArea.append("⚠️ No es tu turno! Espera al oponente.\n");
            return;
        }

        model.Robot player = combatSystem.getPlayer();
        model.Robot opponent = combatSystem.getOpponent();

        turnCounter++;

        StringBuilder sb = new StringBuilder();
        sb.append("\n");
        sb.append("================================================================================\n");
        sb.append("                               TURNO ").append(turnCounter).append("\n");
        sb.append("================================================================================\n");
        turnDetailArea.append(sb.toString());

        // Guardar estado ANTES del movimiento
        int playerHpBefore = player.getStats().getHp();
        int opponentHpBefore = opponent.getStats().getHp();
        int playerNrgBefore = player.getStats().getNrg();
        int opponentNrgBefore = opponent.getStats().getNrg();

        // EJECUTAR movimiento (SOLO AQUÍ se calcula el daño)
        String result = combatSystem.executeMove(player, opponent, move);

        // Estado DESPUÉS del movimiento
        int playerHpAfter = player.getStats().getHp();
        int opponentHpAfter = opponent.getStats().getHp();
        int playerNrgAfter = player.getStats().getNrg();
        int opponentNrgAfter = opponent.getStats().getNrg();

        // Calcular cambios
        int damage = opponentHpBefore - opponentHpAfter;
        int heal = playerHpAfter - playerHpBefore;
        int nrgChange = 0;
        int targetHp = 0;
        int actorHp = 0;

        String moveIcon = getMoveIcon(move);
        String moveName = getMoveName(move);

        turnDetailArea.append(" " + moveIcon + " " + player.getName() + " usa " + moveName + "\n");

        // Preparar datos para enviar al oponente
        String moveData = move.name() + ":" + result + ":";

        if (move == Move.ATTACK || move == Move.SPECIAL) {
            if (result.equals("DODGE")) {
                turnDetailArea.append("   └─ ¡" + opponent.getName() + " esquivó el ataque! (Sin daño)\n");
                moveData += "0:0:0:" + opponentHpAfter + ":" + playerHpAfter;
            } else if (result.equals("FAIL")) {
                turnDetailArea.append("   └─ Falló: Energía insuficiente\n");
                moveData += "0:0:0:" + opponentHpAfter + ":" + playerHpAfter;
            } else {
                turnDetailArea.append("   └─ Causó " + damage + " de daño a " + opponent.getName() + "\n");
                turnDetailArea.append("   └─ ❤️ " + opponent.getName() + " HP: " + opponentHpBefore + " → " + opponentHpAfter + "\n");
                nrgChange = playerNrgAfter - playerNrgBefore;
                moveData += damage + ":0:" + nrgChange + ":" + opponentHpAfter + ":" + playerHpAfter;
            }
        } else if (move == Move.HEAL) {
            turnDetailArea.append("   └─ Recuperó " + heal + " HP\n");
            turnDetailArea.append("   └─ ❤️ " + player.getName() + " HP: " + playerHpBefore + " → " + playerHpAfter + "\n");
            moveData += "0:" + heal + ":0:" + playerHpAfter + ":" + opponentHpAfter;
        } else if (move == Move.CHARGE) {
            nrgChange = playerNrgAfter - playerNrgBefore;
            turnDetailArea.append("   └─ Cargó " + nrgChange + " de energía\n");
            turnDetailArea.append("   └─ ⚡ " + player.getName() + " NRG: " + playerNrgBefore + " → " + playerNrgAfter + "\n");
            moveData += "0:0:" + nrgChange + ":" + opponentHpAfter + ":" + playerHpAfter;
        } else if (move == Move.DODGE) {
            double prob = player.getDodgeCount() >= 2 ? 75 : 50;
            turnDetailArea.append("   └─ Preparado para esquivar (Prob: " + (int)prob + "%)\n");
            moveData += "0:0:0:" + opponentHpAfter + ":" + playerHpAfter;
        }

        turnDetailArea.append("--------------------------------------------------------------------------------\n");

        updateStatsDisplay();

        // Enviar datos COMPLETOS al oponente
        try {
            if (isServer) {
                server.sendMove(moveData);
            } else {
                client.sendMove(moveData);
            }
        } catch (IOException e) {
            turnDetailArea.append("❌ Error enviando movimiento: " + e.getMessage() + "\n");
        }

        // Verificar si el juego terminó
        if (combatSystem.isGameOver()) {
            sendGameOver();
            endGame();
            return;
        }

        // Cambiar turno
        isMyTurn = false;
        turnLabel.setText("Turno de " + opponent.getName());
        enableButtons(false);
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
        model.Robot player = combatSystem.getPlayer();
        model.Robot opponent = combatSystem.getOpponent();

        if (playerStatsLabel != null) {
            playerStatsLabel.setText("Jugador: " + player.getStats().toString());
        }
        if (opponentStatsLabel != null) {
            opponentStatsLabel.setText("Rival: " + opponent.getStats().toString());
        }
        if (combatLogArea != null && !combatSystem.getCombatLog().isEmpty()) {
            combatLogArea.append(combatSystem.getCombatLog().get(combatSystem.getCombatLog().size() - 1) + "\n");
            combatLogArea.setCaretPosition(combatLogArea.getDocument().getLength());
        }
        if (playerStatusCard != null) {
            playerStatusCard.updateFromRobot(player);
        }
        if (opponentStatusCard != null) {
            opponentStatusCard.updateFromRobot(opponent);
        }
        if (playerCharacterLabel != null) {
            playerCharacterLabel.setText(player.getName());
        }
        if (opponentCharacterLabel != null) {
            opponentCharacterLabel.setText(opponent.getName());
        }
    }

    private void endGame() {
        if (gameEnded) return;
        gameEnded = true;
        combatActive = false;

        model.Robot player = combatSystem.getPlayer();
        model.Robot opponent = combatSystem.getOpponent();

        // Asegurar que ambos tengan los mismos HP finales
        player.getStats().setHp(player.getStats().getHp());
        opponent.getStats().setHp(opponent.getStats().getHp());

        model.Robot winner = combatSystem.getWinner();

        StringBuilder finalMsg = new StringBuilder();
        finalMsg.append("\n");
        finalMsg.append("================================================================================\n");
        finalMsg.append("                              🏆 FIN DEL JUEGO 🏆\n");
        finalMsg.append("================================================================================\n");
        finalMsg.append("                    GANADOR: ").append(winner.getName()).append("\n");
        finalMsg.append("================================================================================\n\n");
        turnDetailArea.append(finalMsg.toString());

        JOptionPane.showMessageDialog(this, "¡Fin del juego!\nGanador: " + winner.getName());

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
        if (attackButton != null) attackButton.setEnabled(enable);
        if (specialButton != null) specialButton.setEnabled(enable);
        if (dodgeButton != null) dodgeButton.setEnabled(enable);
        if (healButton != null) healButton.setEnabled(enable);
        if (chargeButton != null) chargeButton.setEnabled(enable);
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

        // Cargar imagen del jugador
        BufferedImage playerImage = null;
        try {
            File playerFile = new File("assets/eva.png");
            if (playerFile.exists()) {
                playerImage = ImageIO.read(playerFile);
                System.out.println("Imagen del jugador cargada: " + playerFile.getAbsolutePath());
            } else {
                System.out.println("No se encontró: " + playerFile.getAbsolutePath());
            }
        } catch (IOException e) {
            System.out.println("Error cargando imagen del jugador: " + e.getMessage());
        }

        // Cargar imagen del rival
        BufferedImage opponentImage = null;
        try {
            File opponentFile = new File("assets/shinji.png");
            if (opponentFile.exists()) {
                opponentImage = ImageIO.read(opponentFile);
                System.out.println("Imagen del rival cargada: " + opponentFile.getAbsolutePath());
            } else {
                System.out.println("No se encontró: " + opponentFile.getAbsolutePath());
            }
        } catch (IOException e) {
            System.out.println("Error cargando imagen del rival: " + e.getMessage());
        }

        playerSpritePanel = new CharacterSpritePanel(
                combatSystem.getPlayer().getName(),
                playerImage,
                new Color(172, 58, 64)
        );

        opponentSpritePanel = new CharacterSpritePanel(
                combatSystem.getOpponent().getName(),
                opponentImage,
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