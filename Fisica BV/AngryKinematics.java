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
    private JCheckBox chkSeguir;
    private JButton btnPlayPause; // Botón dinámico declarado a nivel de clase

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
                time += 0.02; 
                simPanel.updatePhysics(time);
                if (time >= 15) {
                    stopFlight(); 
                    btnPlayPause.setText("INICIAR"); // Restaura el botón al terminar
                }
            }
        });
    }

    private JPanel createControls() {
        JPanel p = new JPanel(new FlowLayout(FlowLayout.CENTER, 15, 15));
        p.setBackground(Color.WHITE);
        p.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));

        cmbModo = new JComboBox<>(new String[]{
            "Magnitud: Posición |r(t)|", 
            "Magnitud: Velocidad |v(t)|", 
            "Magnitud: Aceleración |a(t)|"
        });
        cmbModo.setFont(new Font("Arial", Font.BOLD, 16));
        cmbModo.addActionListener(e -> { 
            stopFlight(); 
            time = 0; 
            simPanel.reset(); 
            simPanel.updatePhysics(0); 
            if (btnPlayPause != null) btnPlayPause.setText("INICIAR");
        });

        chkSeguir = new JCheckBox("Seguir Pájaro", true);
        chkSeguir.setBackground(Color.WHITE);
        chkSeguir.setFont(new Font("Arial", Font.BOLD, 14));

        // Lógica del botón Dinámico: INICIAR -> PAUSAR -> REANUDAR
        btnPlayPause = new JButton("INICIAR");
        btnPlayPause.setBackground(new Color(220, 53, 38));
        btnPlayPause.setForeground(Color.WHITE);
        btnPlayPause.setFont(new Font("Arial", Font.BOLD, 16));
        btnPlayPause.addActionListener(e -> { 
            if (time >= 15) {
                // Si el vuelo ya había terminado, reinicia desde cero
                time = 0;
                simPanel.reset();
                isFlying = true;
                timer.start();
                btnPlayPause.setText("PAUSAR");
            } else if (isFlying) {
                // Si está volando, congela la simulación donde quedó
                isFlying = false;
                timer.stop();
                btnPlayPause.setText("REANUDAR");
            } else {
                // Si está en 0 o estaba pausado, arranca/reanuda
                isFlying = true;
                if (time == 0) simPanel.reset();
                timer.start();
                btnPlayPause.setText("PAUSAR");
            }
        });

        JButton btnReset = new JButton("REINICIAR");
        btnReset.setFont(new Font("Arial", Font.BOLD, 14));
        btnReset.addActionListener(e -> { 
            stopFlight(); 
            time = 0; 
            simPanel.reset(); 
            simPanel.updatePhysics(0); 
            btnPlayPause.setText("INICIAR"); // Restaura el botón al reiniciar
        });

        JButton btnVerTodo = new JButton("VER TODO");
        btnVerTodo.setBackground(new Color(70, 130, 180));
        btnVerTodo.setForeground(Color.WHITE);
        btnVerTodo.setFont(new Font("Arial", Font.BOLD, 14));
        btnVerTodo.addActionListener(e -> simPanel.verTodo());

        p.add(new JLabel("GRAFICAR: "));
        p.add(cmbModo);
        p.add(chkSeguir);
        p.add(btnPlayPause);
        p.add(btnReset);
        p.add(btnVerTodo);

        return p;
    }

    private void stopFlight() {
        isFlying = false; 
        timer.stop(); 
    }

    class SimulationPanel extends JPanel {
        private double pX, pY;
        private double currentMag = 0;
        private ArrayList<Point.Double> trail = new ArrayList<>();
        private double zoom = 1.0, offX = 100, offY = 680;
        private Point lastMouse;

        public SimulationPanel() {
            addMouseWheelListener(e -> {
                if (e.getWheelRotation() < 0) zoom *= 1.1; else zoom /= 1.1;
                chkSeguir.setSelected(false); 
                repaint();
            });

            addMouseListener(new MouseAdapter() { 
                public void mousePressed(MouseEvent e) { lastMouse = e.getPoint(); } 
            });
            
            addMouseMotionListener(new MouseMotionAdapter() {
                public void mouseDragged(MouseEvent e) {
                    if (SwingUtilities.isRightMouseButton(e) || SwingUtilities.isLeftMouseButton(e)) {
                        offX += (e.getX() - lastMouse.x); 
                        offY += (e.getY() - lastMouse.y);
                        lastMouse = e.getPoint(); 
                        chkSeguir.setSelected(false); 
                        repaint();
                    }
                }
            });
        }

        public void reset() { trail.clear(); zoom = 1.0; offX = 100; offY = 680; repaint(); }

        public void verTodo() {
            chkSeguir.setSelected(false); 
            int modo = cmbModo.getSelectedIndex();
            double tMax = 15.0;
            double scaleX = 120.0;
            double scaleY = 40.0;
            
            double maxX = tMax * scaleX;
            double maxY = 0;
            
            if (modo == 0) maxY = Math.sqrt(Math.pow(tMax * tMax, 2) + Math.pow(tMax, 2)) * scaleY;
            else if (modo == 1) maxY = Math.sqrt(Math.pow(2 * tMax, 2) + Math.pow(1, 2)) * scaleY;
            else maxY = 2.0 * scaleY;

            if (maxY < 400) maxY = 400; 

            double margenX = 100.0; 
            double margenY = 150.0;
            
            double zoomX = (getWidth() - margenX * 2) / maxX;
            double zoomY = (getHeight() - margenY * 2) / maxY;
            zoom = Math.min(zoomX, zoomY);
            
            double graphWidth = maxX * zoom;
            double graphHeight = maxY * zoom;
            
            offX = (getWidth() - graphWidth) / 2.0; 
            offY = getHeight() - (getHeight() - graphHeight) / 2.0;
            
            repaint();
        }

        public void updatePhysics(double t) {
            int modo = cmbModo.getSelectedIndex();
            
            double rMag = Math.sqrt(Math.pow(t * t, 2) + Math.pow(t, 2));
            double vMag = Math.sqrt(Math.pow(2 * t, 2) + Math.pow(1, 2));
            double aMag = 2.0;

            double scaleX = 120.0; 
            double scaleY = 40.0;  

            pX = t * scaleX;

            if (modo == 0) currentMag = rMag;
            else if (modo == 1) currentMag = vMag;
            else currentMag = aMag;

            pY = currentMag * scaleY;
            trail.add(new Point.Double(pX, pY));

            if (chkSeguir.isSelected()) {
                offX = getWidth() / 2.0 - pX * zoom;
                offY = getHeight() / 2.0 + pY * zoom;
            }

            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            g2d.setColor(Color.WHITE);
            g2d.fillRect(0, 0, getWidth(), getHeight());

            AffineTransform old = g2d.getTransform();
            
            // --- CAPA 1: MATEMÁTICA (Espacio Escalado) ---
            g2d.translate(offX, offY);
            g2d.scale(zoom, zoom);

            drawGridLines(g2d, zoom);

            g2d.setColor(Color.BLUE);
            g2d.setStroke(new BasicStroke((float)(4.0 / zoom))); 
            for (int i = 1; i < trail.size(); i++) {
                g2d.drawLine((int)trail.get(i-1).x, (int)-trail.get(i-1).y, (int)trail.get(i).x, (int)-trail.get(i).y);
            }

            // --- CAPA 2: INTERFAZ Y PERSONAJE (Espacio de Pantalla Original) ---
            g2d.setTransform(old); 

            drawAxesLabels(g2d);

            int birdScreenX = (int)(offX + pX * zoom);
            int birdScreenY = (int)(offY - pY * zoom);
            drawBird(g2d, birdScreenX, birdScreenY);

            drawEquationHUD(g2d);
        }

        private void drawGridLines(Graphics2D g2d, double z) {
            float strokeFino = (float)(1.0 / z);
            float strokeGrueso = (float)(3.0 / z);
            
            g2d.setColor(new Color(230, 230, 230));
            g2d.setStroke(new BasicStroke(strokeFino));
            
            for(int i=-2000; i<=15000; i+=40) {
                g2d.drawLine(i, -12000, i, 2000); 
                g2d.drawLine(-2000, -i, 15000, -i); 
            }

            g2d.setColor(Color.BLACK);
            g2d.setStroke(new BasicStroke(strokeGrueso));
            
            int endX = 2200; 
            int endY = -10000; 
            g2d.drawLine((int)(-30/z), 0, endX, 0); 
            g2d.drawLine(0, (int)(30/z), 0, endY); 

            int aL = (int)(15/z);
            int aW = (int)(8/z);
            g2d.fillPolygon(new int[]{endX, endX, endX+aL}, new int[]{-aW, aW, 0}, 3);
            g2d.fillPolygon(new int[]{-aW, aW, 0}, new int[]{endY, endY, endY-aL}, 3);

            int mark = (int)(6/z);
            for(int i=1; i<=15; i++) g2d.drawLine(i*120, -mark, i*120, mark);
            for(int i=1; i<=250; i++) {
                if(i%5==0 || i<10) g2d.drawLine(-mark, -i*40, mark, -i*40);
                else g2d.drawLine(-mark/2, -i*40, mark/2, -i*40);
            }
        }

        private void drawAxesLabels(Graphics2D g2d) {
            g2d.setColor(Color.BLACK);
            g2d.setFont(new Font("Arial", Font.BOLD, 16));
            
            int originX = (int)offX;
            int originY = (int)offY;
            
            g2d.drawString("0", originX - 18, originY + 22);
            g2d.drawString("Tiempo (t) en s", (int)(offX + 2200*zoom) - 130, originY + 35);
            g2d.drawString("Magnitud", originX - 90, (int)(offY - 10000*zoom));

            for(int i=1; i<=15; i++) {
                boolean drawX = (zoom >= 0.5) || (i % 5 == 0);
                if (drawX) {
                    g2d.drawString(i+"s", (int)(offX + i*120*zoom) - 10, originY + 25);
                }
            }
            
            for(int i=1; i<=250; i++) {
                boolean drawY = false;
                if (zoom >= 0.8 && (i % 1 == 0)) drawY = true;
                else if (zoom >= 0.3 && (i % 5 == 0 || i < 10)) drawY = true;
                else if (zoom >= 0.1 && (i % 10 == 0)) drawY = true;
                else if (i % 50 == 0) drawY = true;

                if(drawY) {
                    int offset = (i < 10) ? 22 : ((i < 100) ? 32 : 42);
                    g2d.drawString(String.valueOf(i), originX - offset, (int)(offY - i*40*zoom) + 6);
                }
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