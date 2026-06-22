import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.util.ArrayList;

public class AngryKinematics extends JFrame {
    private SimulationPanel simPanel;
    private double time = 0;
    private Timer timer;
    private boolean isFlying = false;
    private JComboBox<String> cmbModo;

    public AngryKinematics() {
        setTitle("Angry Birds - Gráficas de Magnitud vs Tiempo");
        setSize(1280, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        
        simPanel = new SimulationPanel();
        add(simPanel, BorderLayout.CENTER);
        
        JPanel controls = createControls();
        add(controls, BorderLayout.SOUTH);
        
        timer = new Timer(16, e -> {
            if (isFlying) {
                time += 0.02; // Velocidad del tiempo
                simPanel.updatePhysics(time);
                if (time > 10) stopFlight(); // Se detiene a los 10 segundos
            }
        });
    }

    private JPanel createControls() {
        JPanel p = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 15));
        p.setBackground(Color.WHITE);
        p.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));

        cmbModo = new JComboBox<>(new String[]{
            "Magnitud: Posición |r(t)|", 
            "Magnitud: Velocidad |v(t)|", 
            "Magnitud: Aceleración |a(t)|"
        });
        cmbModo.setFont(new Font("Arial", Font.BOLD, 16));
        cmbModo.addActionListener(e -> { stopFlight(); simPanel.reset(); simPanel.updatePhysics(0); });

        JButton btnLaunch = new JButton("INICIAR");
        btnLaunch.setBackground(new Color(220, 53, 38));
        btnLaunch.setForeground(Color.WHITE);
        btnLaunch.setFont(new Font("Arial", Font.BOLD, 16));
        btnLaunch.addActionListener(e -> { time = 0; isFlying = true; simPanel.reset(); timer.start(); });

        JButton btnReset = new JButton("REINICIAR");
        btnReset.setFont(new Font("Arial", Font.BOLD, 14));
        btnReset.addActionListener(e -> stopFlight());

        p.add(new JLabel("GRAFICAR: "));
        p.add(cmbModo);
        p.add(btnLaunch);
        p.add(btnReset);

        return p;
    }

    private void stopFlight() {
        isFlying = false; 
        timer.stop(); 
        time = 0;
        simPanel.updatePhysics(0);
    }

    class SimulationPanel extends JPanel {
        private double pX, pY;
        private double currentMag = 0;
        private ArrayList<Point.Double> trail = new ArrayList<>();
        private double zoom = 1.0, offX = 80, offY = 650;
        private Point lastMouse;

        public SimulationPanel() {
            addMouseWheelListener(e -> {
                if (e.getWheelRotation() < 0) zoom *= 1.1; else zoom /= 1.1;
                repaint();
            });

            addMouseListener(new MouseAdapter() { 
                public void mousePressed(MouseEvent e) { lastMouse = e.getPoint(); } 
            });
            
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
            
            // Cálculos basados en A=1, alpha=1, beta=1
            // r(t) = t^2 i + t j
            double rMag = Math.sqrt(Math.pow(t * t, 2) + Math.pow(t, 2));
            // v(t) = 2t i + 1 j
            double vMag = Math.sqrt(Math.pow(2 * t, 2) + Math.pow(1, 2));
            // a(t) = 2 i + 0 j
            double aMag = 2.0;

            // Escalas visuales para mapear Tiempo y Magnitud a los pixeles de la pantalla
            double scaleX = 120.0; // 1 segundo = 120 pixeles en eje X
            double scaleY = 40.0;  // 1 unidad de magnitud = 40 pixeles en eje Y

            pX = t * scaleX;

            if (modo == 0) {
                currentMag = rMag;
            } else if (modo == 1) {
                currentMag = vMag;
            } else {
                currentMag = aMag;
            }

            pY = currentMag * scaleY;
            trail.add(new Point.Double(pX, pY));
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            // Fondo plano cartesiano
            g2d.setColor(Color.WHITE);
            g2d.fillRect(0, 0, getWidth(), getHeight());

            AffineTransform old = g2d.getTransform();
            g2d.translate(offX, offY);
            g2d.scale(zoom, zoom);

            drawGridAndAxes(g2d);

            // Trayectoria
            g2d.setColor(Color.BLUE);
            g2d.setStroke(new BasicStroke(4));
            for (int i = 1; i < trail.size(); i++) {
                g2d.drawLine((int)trail.get(i-1).x, (int)-trail.get(i-1).y, (int)trail.get(i).x, (int)-trail.get(i).y);
            }

            // Dibujar el Angry Bird siguiendo la gráfica
            drawBird(g2d, (int)pX, (int)-pY);

            g2d.setTransform(old);
            drawEquationHUD(g2d);
        }

        private void drawGridAndAxes(Graphics2D g2d) {
            g2d.setColor(new Color(230, 230, 230));
            g2d.setStroke(new BasicStroke(1));
            
            // Cuadrícula
            for(int i=-1000; i<3000; i+=40) {
                g2d.drawLine(i, -2000, i, 1000);
                g2d.drawLine(-1000, -i, 3000, -i);
            }

            // Ejes X e Y
            g2d.setColor(Color.BLACK);
            g2d.setStroke(new BasicStroke(3));
            g2d.drawLine(0, 0, 2000, 0); // Eje X (Tiempo)
            g2d.drawLine(0, 0, 0, -1500); // Eje Y (Magnitud)

            g2d.setFont(new Font("Arial", Font.BOLD, 16));
            g2d.drawString("Tiempo (t) en segundos", 1000, 25);
            g2d.drawString("Magnitud", -90, -800);

            // Marcas en X (Tiempo)
            for(int i=1; i<=15; i++) {
                g2d.drawLine(i*120, -5, i*120, 5);
                g2d.drawString(i+"s", i*120 - 10, 25);
            }
            // Marcas en Y (Magnitud)
            for(int i=1; i<=30; i++) {
                g2d.drawLine(-5, -i*40, 5, -i*40);
                g2d.drawString(String.valueOf(i), -25, -i*40 + 6);
            }
        }

        private void drawEquationHUD(Graphics2D g2d) {
            g2d.setColor(new Color(255, 255, 255, 245));
            g2d.fillRoundRect(30, 30, 600, 150, 20, 20);
            g2d.setColor(new Color(40, 40, 40));
            g2d.setStroke(new BasicStroke(2));
            g2d.drawRoundRect(30, 30, 600, 150, 20, 20);

            g2d.setFont(new Font("Serif", Font.BOLD, 22));
            int y = 70; 
            int modo = cmbModo.getSelectedIndex();

            if (modo == 0) {
                g2d.setColor(Color.BLUE);
                g2d.drawString("Vector:  r(t) = t² i + t j", 50, y);
                g2d.setColor(new Color(220, 53, 38));
                g2d.drawString(String.format("Magnitud:  |r(t)| = \u221A(t\u2074 + t\u00B2) = %.2f m", currentMag), 50, y + 40);
            } else if (modo == 1) {
                g2d.setColor(new Color(255, 140, 0));
                g2d.drawString("Vector:  v(t) = 2t i + 1 j", 50, y);
                g2d.setColor(new Color(220, 53, 38));
                g2d.drawString(String.format("Magnitud:  |v(t)| = \u221A(4t\u00B2 + 1) = %.2f m/s", currentMag), 50, y + 40);
            } else {
                g2d.setColor(new Color(34, 139, 34));
                g2d.drawString("Vector:  a(t) = 2 i + 0 j", 50, y);
                g2d.setColor(new Color(220, 53, 38));
                g2d.drawString(String.format("Magnitud:  |a(t)| = \u221A(4) = %.2f m/s\u00B2", currentMag), 50, y + 40);
            }

            g2d.setColor(Color.DARK_GRAY); 
            g2d.setFont(new Font("Arial", Font.BOLD, 16));
            g2d.drawString(String.format("TIEMPO ACTUAL: %.2f s", time), 50, 150);
        }

        private void drawBird(Graphics2D g2d, int cx, int cy) {
            int r = 20;
            g2d.setColor(new Color(220, 53, 38)); g2d.fillOval(cx - r, cy - r, r*2, r*2);
            g2d.setColor(Color.BLACK); g2d.setStroke(new BasicStroke(2)); g2d.drawOval(cx - r, cy - r, r*2, r*2);
            g2d.setColor(new Color(245, 245, 245)); g2d.fillArc(cx - r + 3, cy - r + 8, r*2 - 6, r*2 - 6, 180, 180);
            g2d.setColor(Color.WHITE); g2d.fillOval(cx - 16, cy - 12, 15, 15); g2d.fillOval(cx + 1, cy - 12, 15, 15);
            g2d.setColor(Color.BLACK); g2d.drawOval(cx - 16, cy - 12, 15, 15); g2d.drawOval(cx + 1, cy - 12, 15, 15);
            g2d.fillOval(cx - 8, cy - 6, 5, 5); g2d.fillOval(cx + 4, cy - 6, 5, 5);
            g2d.setStroke(new BasicStroke(4));
            g2d.drawLine(cx - 18, cy - 15, cx - 2, cy - 8); g2d.drawLine(cx + 18, cy - 15, cx + 2, cy - 8);
            g2d.setColor(new Color(255, 200, 0)); 
            int[] px = {cx - 8, cx + 8, cx}; int[] py = {cy + 2, cy + 2, cy + 14}; 
            g2d.fillPolygon(px, py, 3);
            g2d.setColor(Color.BLACK); g2d.setStroke(new BasicStroke(1)); g2d.drawPolygon(px, py, 3);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new AngryKinematics().setVisible(true));
    }
}