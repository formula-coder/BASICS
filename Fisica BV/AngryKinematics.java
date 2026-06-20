import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.geom.Path2D;
import java.util.ArrayList;

public class AngryKinematics extends JFrame {
    private SimulationPanel simPanel;
    private double A = 2.0, alpha = 2.0, beta = 15.0;
    private double time = 0;
    private Timer timer;
    private boolean isFlying = false;
    private JLabel lblValA, lblValAlpha, lblValBeta;
    private JComboBox<String> cmbModo;

    public AngryKinematics() {
        setTitle("Angry Birds Physics - Final Horizon Edition");
        setSize(1280, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        simPanel = new SimulationPanel();
        add(simPanel, BorderLayout.CENTER);
        JPanel controls = createAdvancedControls();
        add(controls, BorderLayout.SOUTH);
        timer = new Timer(16, e -> {
            if (isFlying) {
                time += 0.05;
                simPanel.updatePhysics(time);
                if (time > 25) stopFlight();
            }
        });
    }

    private JPanel createAdvancedControls() {
        JPanel p = new JPanel(new BorderLayout());
        p.setBackground(Color.WHITE);
        p.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));
        JPanel sliderPanel = new JPanel(new GridLayout(1, 3, 30, 0));
        sliderPanel.setBackground(Color.WHITE);
        sliderPanel.add(createSliderWithLabel("Variable A", 1, 10, 2, v -> { A = v; simPanel.repaint(); lblValA.setText(""+v); }));
        sliderPanel.add(createSliderWithLabel("Variable \u03B1", 1, 5, 2, v -> { alpha = v; simPanel.repaint(); lblValAlpha.setText(""+v); }));
        sliderPanel.add(createSliderWithLabel("Variable \u03B2", 5, 30, 15, v -> { beta = v; simPanel.repaint(); lblValBeta.setText(""+v); }));
        JPanel actionPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 10));
        actionPanel.setBackground(Color.WHITE);
        cmbModo = new JComboBox<>(new String[]{"Modo: Posición r(t)", "Modo: Velocidad v(t)", "Modo: Aceleración a(t)"});
        cmbModo.setFont(new Font("Arial", Font.BOLD, 14));
        cmbModo.addActionListener(e -> { stopFlight(); simPanel.reset(); simPanel.updatePhysics(0); });
        JButton btnLaunch = new JButton("¡LANZAR!");
        btnLaunch.setBackground(new Color(220, 53, 38));
        btnLaunch.setForeground(Color.WHITE);
        btnLaunch.setFont(new Font("Arial", Font.BOLD, 16));
        btnLaunch.addActionListener(e -> { time = 0; isFlying = true; simPanel.reset(); timer.start(); });
        JButton btnReset = new JButton("REINICIAR");
        btnReset.addActionListener(e -> stopFlight());
        actionPanel.add(new JLabel("GRAFICAR: "));
        actionPanel.add(cmbModo);
        actionPanel.add(btnLaunch);
        actionPanel.add(btnReset);
        p.add(sliderPanel, BorderLayout.NORTH);
        p.add(actionPanel, BorderLayout.CENTER);
        return p;
    }

    private JPanel createSliderWithLabel(String title, int min, int max, int val, java.util.function.Consumer<Double> updater) {
        JPanel container = new JPanel(new BorderLayout());
        container.setBackground(Color.WHITE);
        JSlider s = new JSlider(min, max, val);
        s.setBackground(Color.WHITE);
        JLabel valLabel = new JLabel(""+(double)val);
        valLabel.setFont(new Font("Arial", Font.BOLD, 14));
        valLabel.setPreferredSize(new Dimension(40, 20));
        if(title.contains("A")) lblValA = valLabel;
        else if(title.contains("\u03B1")) lblValAlpha = valLabel;
        else lblValBeta = valLabel;
        s.addChangeListener(e -> updater.accept((double)s.getValue()));
        container.add(new JLabel(title), BorderLayout.WEST);
        container.add(s, BorderLayout.CENTER);
        container.add(valLabel, BorderLayout.EAST);
        return container;
    }

    private void stopFlight() {
        isFlying = false; timer.stop(); time = 0;
        simPanel.updatePhysics(0);
    }
    class SimulationPanel extends JPanel {
        private double pX, pY, vecX, vecY;
        private ArrayList<Point.Double> trail = new ArrayList<>();
        private double zoom = 1.0, offX = 100, offY = 600;
        private Point lastMouse;

        public SimulationPanel() {
            addMouseWheelListener(e -> {
                if (e.getWheelRotation() < 0) zoom *= 1.1; else zoom /= 1.1;
                repaint();
            });

            addMouseListener(new MouseAdapter() { public void mousePressed(MouseEvent e) { lastMouse = e.getPoint(); } });
            addMouseMotionListener(new MouseMotionAdapter() {
                public void mouseDragged(MouseEvent e) {
                    if (SwingUtilities.isRightMouseButton(e)) {
                        offX += (e.getX() - lastMouse.x); offY += (e.getY() - lastMouse.y);
                        lastMouse = e.getPoint(); repaint();
                    }
                }
            });
        }
        public void reset() { trail.clear(); repaint(); }
        public void updatePhysics(double t) {
            int modo = cmbModo.getSelectedIndex();
            double rX = A * alpha * t * t;
            double rY = A * beta * t;
            double vX = A * 2 * alpha * t;
            double vY = A * beta;
            double aX = A * 2 * alpha;
            if (modo == 0) { pX = rX; pY = rY; vecX = vX; vecY = vY; }
            else if (modo == 1) { pX = vX; pY = vY; vecX = aX; vecY = 0; }
            else { pX = aX; pY = 0; vecX = 0; vecY = 0; }
            trail.add(new Point.Double(pX, pY));
            repaint();
        }
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            // Cielo
            g2d.setPaint(new GradientPaint(0, 0, new Color(135,206,250), 0, getHeight(), Color.WHITE));
            g2d.fillRect(0, 0, getWidth(), getHeight());
            AffineTransform old = g2d.getTransform();
            g2d.translate(offX, offY);
            g2d.scale(zoom, zoom);
            drawClouds(g2d); // Nubes
            // Suelo
            g2d.setColor(new Color(123, 184, 43));
            g2d.fillRect(-5000, 0, 10000, 1000);
            g2d.setColor(new Color(80, 50, 20));
            g2d.fillRect(-5000, 5, 10000, 5); // Línea de tierra
            drawMountain(g2d); // La gran montaña final
            drawSlingshot(g2d); // Resortera inicial
            // Trayectoria
            g2d.setColor(new Color(255,255,255,150));
            g2d.setStroke(new BasicStroke(2, 1, 1, 10, new float[]{8}, 0));
            for (int i = 1; i < trail.size(); i++)
                g2d.drawLine((int)trail.get(i-1).x, (int)-trail.get(i-1).y, (int)trail.get(i).x, (int)-trail.get(i).y);
            // Vectores
            int modo = cmbModo.getSelectedIndex();
            if (modo == 0) drawArrow(g2d, (int)pX, (int)-pY, vecX*3, -vecY*3, Color.BLUE, "v(t)");
            if (modo == 1) drawArrow(g2d, (int)pX, (int)-pY, vecX*5, 0, new Color(255,140,0), "a(t)");
            drawBird(g2d, (int)pX, (int)-pY);
            g2d.setTransform(old);
            drawEquationHUD(g2d);
        }
        private void drawMountain(Graphics2D g2d) {
            double endX = A * alpha * (25.0 * 25.0);
            g2d.setColor(new Color(100, 105, 115));
            Path2D.Double m = new Path2D.Double();
            m.moveTo(endX - 200, 0);
            m.lineTo(endX + 100, -450); // Pico 1
            m.lineTo(endX + 300, -200);
            m.lineTo(endX + 500, -550); // Pico 2 (Más alto)
            m.lineTo(endX + 800, 0);
            m.closePath();
            g2d.fill(m);
            // Nieve
            g2d.setColor(Color.WHITE);
            Path2D.Double s = new Path2D.Double();
            s.moveTo(endX + 500, -550);
            s.lineTo(endX + 430, -420); s.lineTo(endX + 500, -450); s.lineTo(endX + 570, -420);
            s.closePath();
            g2d.fill(s);
        }
        private void drawSlingshot(Graphics2D g2d) {
            g2d.setColor(new Color(101, 67, 33));
            g2d.setStroke(new BasicStroke(12));
            g2d.drawLine(0, 0, 0, 80); // Base
            g2d.drawLine(0, 0, -20, -40); // Brazo izq
            g2d.drawLine(0, 0, 20, -40); // Brazo der
        }
        private void drawClouds(Graphics2D g2d) {
            g2d.setColor(new Color(255, 255, 255, 200));
            for(int i=-2; i<10; i++) {
                int cx = i * 800; int cy = -400 - (i%2)*100;
                g2d.fillOval(cx, cy, 150, 80);
                g2d.fillOval(cx+40, cy-30, 100, 80);
            }
        }
        private void drawEquationHUD(Graphics2D g2d) {
            g2d.setColor(new Color(255, 255, 255, 230));
            g2d.fillRoundRect(30, 30, 480, 180, 25, 25);
            g2d.setColor(new Color(30,30,30));
            g2d.setStroke(new BasicStroke(2));
            g2d.drawRoundRect(30, 30, 480, 180, 25, 25);
            g2d.setFont(new Font("Serif", Font.ITALIC | Font.BOLD, 22));
            int y = 65; int modo = cmbModo.getSelectedIndex();
            if (modo == 0) {
                g2d.setColor(Color.BLACK); g2d.drawString(String.format("r(t) = %.1f( %.1ft\u00B2 i + %.1ft j )", A, alpha, beta), 55, y);
                g2d.setColor(Color.BLUE); g2d.drawString(String.format("v(t) = %.1f( %.1ft i + %.1f j )", A, 2*alpha, beta), 55, y + 40);
                g2d.setColor(new Color(210,105,30)); g2d.drawString(String.format("a(t) = %.1f( %.1f i + 0j )", A, 2*alpha), 55, y + 80);
            } else if (modo == 1) {
                g2d.setColor(Color.BLUE); g2d.drawString("VISTA HODÓGRAFA (VELOCIDAD)", 55, y);
                g2d.drawString(String.format("v(t) = %.1f( %.1ft i + %.1f j )", A, 2*alpha, beta), 55, y + 45);
            } else {
                g2d.setColor(new Color(210,105,30)); g2d.drawString("VISTA ACELERACIÓN", 55, y);
                g2d.drawString(String.format("a(t) = %.1f( %.1f i + 0j )", A, 2*alpha), 55, y + 45);
            }
            g2d.setColor(Color.GRAY); g2d.setFont(new Font("Arial", Font.BOLD, 14));
            g2d.drawString(String.format("TIEMPO: %.2f s", time), 55, 185);
        }
        private void drawArrow(Graphics2D g2d, int x, int y, double dx, double dy, Color c, String l) {
            if(dx == 0 && dy == 0) return;
            g2d.setColor(c); g2d.setStroke(new BasicStroke(4));
            int tx = (int)(x+dx), ty = (int)(y+dy);
            g2d.drawLine(x, y, tx, ty);
            double ang = Math.atan2(dy, dx);
            Path2D.Double head = new Path2D.Double();
            head.moveTo(tx, ty);
            head.lineTo(tx - 12*Math.cos(ang-0.5), ty - 12*Math.sin(ang-0.5));
            head.lineTo(tx - 12*Math.cos(ang+0.5), ty - 12*Math.sin(ang+0.5));
            head.closePath(); g2d.fill(head);
            g2d.drawString(l, tx+5, ty);
        }
        private void drawBird(Graphics2D g2d, int cx, int cy) {
            int r = 22;
            g2d.setColor(new Color(220, 53, 38)); g2d.fillOval(cx - r, cy - r, r*2, r*2);
            g2d.setColor(Color.BLACK); g2d.setStroke(new BasicStroke(2)); g2d.drawOval(cx - r, cy - r, r*2, r*2);
            g2d.setColor(new Color(245, 245, 245)); g2d.fillArc(cx - r + 3, cy - r + 8, r*2 - 6, r*2 - 6, 180, 180);
            g2d.setColor(Color.WHITE); g2d.fillOval(cx - 16, cy - 12, 15, 15); g2d.fillOval(cx + 1, cy - 12, 15, 15);
            g2d.setColor(Color.BLACK); g2d.drawOval(cx - 16, cy - 12, 15, 15); g2d.drawOval(cx + 1, cy - 12, 15, 15);
            g2d.fillOval(cx - 8, cy - 6, 5, 5); g2d.fillOval(cx + 4, cy - 6, 5, 5);
            g2d.setStroke(new BasicStroke(5)); // Cejas muy enojadas
            g2d.drawLine(cx - 18, cy - 15, cx - 2, cy - 8); g2d.drawLine(cx + 18, cy - 15, cx + 2, cy - 8);
            g2d.setColor(new Color(255, 200, 0)); int[] px = {cx - 8, cx + 8, cx}; int[] py = {cy + 2, cy + 2, cy + 14}; g2d.fillPolygon(px, py, 3);
            g2d.setColor(Color.BLACK); g2d.setStroke(new BasicStroke(1)); g2d.drawPolygon(px, py, 3);
        }
    }
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new AngryKinematics().setVisible(true));
    }
} 

