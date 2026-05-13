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
    private static final Color PANEL_BG = new Color(10, 14, 24, 210);
    private static final Color PANEL_BORDER = new Color(255, 255, 255, 35);
    private static final Color TEXT_COLOR = new Color(232, 238, 255);
    private static final Color ACCENT = new Color(95, 178, 255);
    private static final Color DANGER = new Color(255, 99, 122);
    private static final Color SUCCESS = new Color(88, 214, 141);

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
        combatLogArea.setFont(new Font("Consolas", Font.PLAIN, 13));
        JScrollPane scrollPane = new JScrollPane(combatLogArea);
        scrollPane.setOpaque(false);
        scrollPane.getViewport().setOpaque(false);
        scrollPane.setBorder(BorderFactory.createEmptyBorder());
        scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

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

        BattleFieldPanel battleFieldPanel = new BattleFieldPanel();
        battleFieldPanel.setLayout(new BorderLayout(0, 12));
        battleFieldPanel.setBorder(BorderFactory.createEmptyBorder(8, 8, 8, 8));
        battleFieldPanel.add(overlayPanel, BorderLayout.NORTH);
        battleFieldPanel.add(consolePanel, BorderLayout.CENTER);
        battleFieldPanel.add(createCharacterStrip(), BorderLayout.SOUTH);

        JPanel actionBarShell = new JPanel(new BorderLayout());
        actionBarShell.setOpaque(true);
        actionBarShell.setBackground(PANEL_BG);
        actionBarShell.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createLineBorder(PANEL_BORDER, 1),
            BorderFactory.createEmptyBorder(10, 10, 10, 10)
        ));
        actionBarShell.add(buttonPanel, BorderLayout.CENTER);

        root.add(battleFieldPanel, BorderLayout.CENTER);
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