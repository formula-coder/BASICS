import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

public class War extends JFrame {

    // Componentes de la interfaz
    private JSlider sldV1, sldTheta1, sldTheta2, sldDistancia;
    private JLabel lblV1, lblTheta1, lblTheta2, lblDistancia;
    private JTextArea txtResultados;
    private CampoGuerra panelGrafico;
    private JButton btnSimular;
    private JCheckBox chkModoNoche;
    private JComboBox<String> comboAtacante, comboDefensor;

    // Variables de la fisica
    private double v1, theta1Deg, theta2Deg, distancia;
    private double v2, tiempoImpacto, tiempoVuelo;
    private boolean interceptado;
    private double xImpacto, yImpacto;
    private final double gravedad = 9.81;

    // Variables para la animacion y camara
    private Timer timerAnimacion;
    private double tActual = 0.0;
    private double limiteT1 = 0.0;
    private boolean simulacionEnCurso = false;
    private int shakeIntensity = 0; 
    private double zoomLevel = 1.0;     
    private double targetZoom = 1.0;    
    private int explosionTimer = 0; 
    private boolean haciendoZoomOut = false;
    private List<Particula> particulas = new ArrayList<>(); 

    // Lista de paises disponibles
    private final String[] PAISES = {"Israel", "Irán", "EE.UU.", "Rusia", "Ucrania", "Corea del N.", "Corea del S.", "China", "Taiwán", "OTAN"};

    public War() {
        UIManager.put("Panel.background", new Color(30, 35, 40));
        UIManager.put("Label.foreground", new Color(171, 178, 191));
        UIManager.put("TitledBorder.titleColor", new Color(97, 175, 239));

        setTitle("Global Tactical Simulator v5.0 (Facciones y Banderas Dinámicas)");
        setSize(1200, 750); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout(10, 10));
        getContentPane().setBackground(new Color(30, 35, 40));

        // PANEL DE ENTRADA DE DATOS
        JPanel panelEntrada = new JPanel();
        panelEntrada.setLayout(new BoxLayout(panelEntrada, BoxLayout.Y_AXIS));
        panelEntrada.setBorder(BorderFactory.createTitledBorder("Centro de Comando Central"));
        panelEntrada.setPreferredSize(new Dimension(300, 0));

        // SELECTOR DE FACCIONES
        JPanel panelFacciones = new JPanel(new GridLayout(2, 2, 5, 5));
        panelFacciones.setBackground(new Color(30, 35, 40));
        panelFacciones.setBorder(BorderFactory.createTitledBorder("Selección de Facciones"));
        
        comboAtacante = new JComboBox<>(PAISES);
        comboAtacante.setSelectedItem("Irán");
        comboAtacante.setBackground(new Color(40, 45, 50));
        comboAtacante.setForeground(new Color(220, 38, 38)); 
        comboAtacante.setFont(new Font("Consolas", Font.BOLD, 12));
        comboAtacante.addActionListener(e -> { actualizarTextos(); panelGrafico.repaint(); });

        comboDefensor = new JComboBox<>(PAISES);
        comboDefensor.setSelectedItem("Israel");
        comboDefensor.setBackground(new Color(40, 45, 50));
        comboDefensor.setForeground(new Color(59, 130, 246)); 
        comboDefensor.setFont(new Font("Consolas", Font.BOLD, 12));
        comboDefensor.addActionListener(e -> { actualizarTextos(); panelGrafico.repaint(); });

        JLabel lblAtacante = new JLabel("Atacante:");
        lblAtacante.setForeground(new Color(220, 38, 38));
        JLabel lblDefensor = new JLabel("Defensor:");
        lblDefensor.setForeground(new Color(59, 130, 246));

        panelFacciones.add(lblAtacante);
        panelFacciones.add(comboAtacante);
        panelFacciones.add(lblDefensor);
        panelFacciones.add(comboDefensor);
        panelFacciones.setMaximumSize(new Dimension(280, 80));

        panelEntrada.add(Box.createVerticalStrut(10));
        panelEntrada.add(panelFacciones);

        // SLIDERS DE FISICA
        lblV1 = new JLabel("150 m/s");
        lblTheta1 = new JLabel("60°");
        lblTheta2 = new JLabel("45°");
        lblDistancia = new JLabel("1200 m");

        Dimension dimLabels = new Dimension(60, 20);
        lblV1.setPreferredSize(dimLabels);
        lblTheta1.setPreferredSize(dimLabels);
        lblTheta2.setPreferredSize(dimLabels);
        lblDistancia.setPreferredSize(dimLabels);

        sldV1 = new JSlider(50, 300, 150);
        sldTheta1 = new JSlider(10, 85, 60);
        sldTheta2 = new JSlider(10, 85, 45);
        sldDistancia = new JSlider(500, 2500, 1200);

        JSlider[] sliders = {sldV1, sldTheta1, sldTheta2, sldDistancia};
        for(JSlider s : sliders) {
            s.setBackground(new Color(30, 35, 40));
            s.setForeground(Color.GRAY);
        }

        ChangeListener actualizador = e -> {
            if(timerAnimacion != null && timerAnimacion.isRunning()) timerAnimacion.stop();
            simulacionEnCurso = false;
            haciendoZoomOut = false;
            particulas.clear();
            shakeIntensity = 0;
            zoomLevel = 1.0; 
            targetZoom = 1.0;
            explosionTimer = 0;
            actualizarTextos();
            calcularFisica();
            tActual = limiteT1; 
            panelGrafico.repaint();
        };

        sldV1.addChangeListener(actualizador);
        sldTheta1.addChangeListener(actualizador);
        sldTheta2.addChangeListener(actualizador);
        sldDistancia.addChangeListener(actualizador);

        panelEntrada.add(Box.createVerticalStrut(15));
        panelEntrada.add(crearPanelSlider("Vel. Amenaza (m/s):", sldV1, lblV1));
        panelEntrada.add(Box.createVerticalStrut(15));
        panelEntrada.add(crearPanelSlider("Trayectoria Enemiga (°):", sldTheta1, lblTheta1));
        panelEntrada.add(Box.createVerticalStrut(15));
        panelEntrada.add(crearPanelSlider("Calibración Interceptor (°):", sldTheta2, lblTheta2));
        panelEntrada.add(Box.createVerticalStrut(15));
        panelEntrada.add(crearPanelSlider("Distancia Base (m):", sldDistancia, lblDistancia));

        // CONTROLES EXTRAS Y BOTON
        JPanel panelControlesExtra = new JPanel(new GridLayout(2, 1, 5, 15));
        panelControlesExtra.setBackground(new Color(30, 35, 40));
        panelControlesExtra.setMaximumSize(new Dimension(280, 100));
        
        chkModoNoche = new JCheckBox("  Activar Entorno Nocturno", true);
        chkModoNoche.setBackground(new Color(30, 35, 40));
        chkModoNoche.setForeground(new Color(171, 178, 191));
        chkModoNoche.setFont(new Font("Consolas", Font.BOLD, 14));
        chkModoNoche.setFocusPainted(false);
        chkModoNoche.addActionListener(e -> panelGrafico.repaint());

        btnSimular = new JButton("INICIAR DEFENSA AÉREA");
        btnSimular.setBackground(new Color(220, 38, 38));
        btnSimular.setForeground(Color.WHITE);
        btnSimular.setFont(new Font("Consolas", Font.BOLD, 16));
        btnSimular.setFocusPainted(false);
        btnSimular.addActionListener(e -> iniciarAnimacion());
        
        panelControlesExtra.add(chkModoNoche);
        panelControlesExtra.add(btnSimular);
        
        panelEntrada.add(Box.createVerticalStrut(20));
        panelEntrada.add(panelControlesExtra);

        // PANEL GRAFICO Y CONSOLA
        panelGrafico = new CampoGuerra();
        panelGrafico.setBorder(BorderFactory.createTitledBorder("Monitor Táctico Global"));

        txtResultados = new JTextArea();
        txtResultados.setEditable(false);
        txtResultados.setFont(new Font("Consolas", Font.PLAIN, 14));
        txtResultados.setBackground(new Color(10, 15, 20));
        txtResultados.setForeground(new Color(0, 255, 100)); 
        
        JScrollPane scrollResultados = new JScrollPane(txtResultados);
        scrollResultados.setPreferredSize(new Dimension(0, 130));
        scrollResultados.setBorder(BorderFactory.createTitledBorder("Log del Sistema"));

        add(panelEntrada, BorderLayout.WEST);
        add(panelGrafico, BorderLayout.CENTER);
        add(scrollResultados, BorderLayout.SOUTH);

        actualizarTextos();
        calcularFisica();
        tActual = limiteT1; 
    }

    private JPanel crearPanelSlider(String titulo, JSlider slider, JLabel labelValor) {
        JPanel p = new JPanel(new BorderLayout(5, 5));
        p.setBackground(new Color(30, 35, 40));
        JLabel lblTitulo = new JLabel(titulo);
        lblTitulo.setFont(new Font("Consolas", Font.BOLD, 13));
        p.add(lblTitulo, BorderLayout.NORTH);
        p.add(slider, BorderLayout.CENTER);
        JPanel pValor = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        pValor.setBackground(new Color(30, 35, 40));
        labelValor.setFont(new Font("Consolas", Font.BOLD, 14));
        labelValor.setForeground(new Color(97, 175, 239));
        pValor.add(labelValor);
        p.add(pValor, BorderLayout.EAST);
        p.setMaximumSize(new Dimension(280, 50));
        return p;
    }

    private void actualizarTextos() {
        lblV1.setText(sldV1.getValue() + " m/s");
        lblTheta1.setText(sldTheta1.getValue() + "°");
        lblTheta2.setText(sldTheta2.getValue() + "°");
        lblDistancia.setText(sldDistancia.getValue() + " m");
    }

    private void calcularFisica() {
        v1 = sldV1.getValue();
        theta1Deg = sldTheta1.getValue();
        theta2Deg = sldTheta2.getValue();
        distancia = sldDistancia.getValue();

        double t1Rad = Math.toRadians(theta1Deg);
        double t2Rad = Math.toRadians(theta2Deg);

        v2 = (v1 * Math.sin(t1Rad)) / Math.sin(t2Rad);
        double v1x = v1 * Math.cos(t1Rad);
        double v2x = v2 * Math.cos(t2Rad);
        
        tiempoImpacto = distancia / (v1x + v2x);
        tiempoVuelo = (2 * v1 * Math.sin(t1Rad)) / gravedad;

        if (tiempoImpacto < tiempoVuelo) {
            interceptado = true;
            limiteT1 = tiempoImpacto;
            xImpacto = v1x * tiempoImpacto;
            yImpacto = (v1 * Math.sin(t1Rad) * tiempoImpacto) - (0.5 * gravedad * Math.pow(tiempoImpacto, 2));
        } else {
            interceptado = false;
            limiteT1 = tiempoVuelo;
        }

        imprimirConsola();
    }

    private void imprimirConsola() {
        String atacante = comboAtacante.getSelectedItem().toString();
        String defensor = comboDefensor.getSelectedItem().toString();

        txtResultados.setText(String.format(">>> ESCENARIO DE CONFLICTO: %s [Ataca] vs %s [Defiende]\n", atacante.toUpperCase(), defensor.toUpperCase()));
        txtResultados.append(String.format(">>> Carga interceptor requerida: %.2f m/s\n", v2));
        txtResultados.append(String.format(">>> Tiempo de intersección balística: %.2f seg\n", tiempoImpacto));
        if(interceptado) {
            txtResultados.append(String.format(">>> ESTADO: [%s ASEGURADO] - Intercepción viable.\n", defensor.toUpperCase()));
        } else {
            txtResultados.setForeground(new Color(255, 80, 80));
            txtResultados.append(String.format(">>> ESTADO: [ALERTA CRÍTICA] - Impacto inminente en territorio de %s.\n", defensor));
        }
    }

    private void iniciarAnimacion() {
        if (timerAnimacion != null && timerAnimacion.isRunning()) {
            timerAnimacion.stop();
        }
        calcularFisica();
        tActual = 0.0;
        simulacionEnCurso = true;
        shakeIntensity = 0;
        zoomLevel = 1.0;      
        targetZoom = 1.0;
        explosionTimer = 0;
        haciendoZoomOut = false;
        particulas.clear();
        txtResultados.setForeground(new Color(0, 255, 100)); 
        
        timerAnimacion = new Timer(16, e -> {
            if (simulacionEnCurso) {
                double paso = limiteT1 / 80.0; 
                tActual += paso;

                if (tActual >= limiteT1) {
                    tActual = limiteT1;
                    simulacionEnCurso = false;
                    shakeIntensity = interceptado ? 15 : 30; 
                    targetZoom = 2.0; 
                }
            }

            if (!simulacionEnCurso && tActual >= limiteT1) {
                if (!haciendoZoomOut) {
                    if (zoomLevel < targetZoom) {
                        zoomLevel += 0.05;
                        if (zoomLevel > targetZoom) zoomLevel = targetZoom;
                    } else {
                        explosionTimer++;
                        if (explosionTimer > 90) haciendoZoomOut = true; 
                    }
                } else {
                    if (zoomLevel > 1.0) {
                        zoomLevel -= 0.03; 
                        if (zoomLevel <= 1.0) zoomLevel = 1.0;
                    }
                }
            }

            Iterator<Particula> it = particulas.iterator();
            while(it.hasNext()){
                Particula p = it.next();
                p.actualizar();
                if(p.vida <= 0) it.remove();
            }

            if(shakeIntensity > 0) shakeIntensity -= 1;

            if (!simulacionEnCurso && particulas.isEmpty() && shakeIntensity == 0 && zoomLevel == 1.0 && haciendoZoomOut) {
                timerAnimacion.stop();
            }

            panelGrafico.repaint();
        });
        timerAnimacion.start();
    }

    private class Particula {
        double x, y, vx, vy;
        int vida, vidaMax;
        Color color;
        int size;

        public Particula(double x, double y, Color color) {
            this.x = x;
            this.y = y;
            this.color = color;
            this.vidaMax = 15 + (int)(Math.random() * 20); 
            this.vida = vidaMax;
            this.size = 4 + (int)(Math.random() * 6);
            this.vx = (Math.random() - 0.5) * 2;
            this.vy = (Math.random() - 0.5) * 2;
        }
        public void actualizar() { x += vx; y += vy; vida--; }
        public void dibujar(Graphics2D g2) {
            float alpha = (float) vida / vidaMax; 
            g2.setColor(new Color(color.getRed(), color.getGreen(), color.getBlue(), (int)(alpha * 255)));
            g2.fillOval((int)x, (int)y, size, size);
        }
    }

    // CLASE INTERNA: Lienzo Visual 
    private class CampoGuerra extends JPanel {
        
        public CampoGuerra() {
            setBackground(new Color(15, 20, 25)); 
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            boolean esNoche = chkModoNoche.isSelected();
            int w = getWidth();
            int h = getHeight();
            int margenX = 110; 
            int sueloY = h - 60;

            String nombreAtacante = comboAtacante.getSelectedItem().toString();
            String nombreDefensor = comboDefensor.getSelectedItem().toString();

            double maxH_Enemigo = (Math.pow(v1 * Math.sin(Math.toRadians(theta1Deg)), 2)) / (2 * gravedad);
            double altoMaximoReal = Math.max(maxH_Enemigo, (interceptado ? yImpacto : maxH_Enemigo)) * 1.2;
            double anchoMaximoReal = distancia;
            double escalaX = (w - (margenX * 2)) / anchoMaximoReal;
            double escalaY = (sueloY - 50) / altoMaximoReal;

            int expX = interceptado ? (margenX + (int)(xImpacto * escalaX)) : (margenX + (int)(v1 * Math.cos(Math.toRadians(theta1Deg)) * tiempoVuelo * escalaX));
            int expY = interceptado ? (sueloY - (int)(yImpacto * escalaY)) : sueloY;

            if (zoomLevel > 1.0) {
                g2.translate(expX, expY);
                g2.scale(zoomLevel, zoomLevel);
                g2.translate(-expX, -expY);
            }
            if (shakeIntensity > 0) {
                int offsetX = (int)((Math.random() - 0.5) * shakeIntensity);
                int offsetY = (int)((Math.random() - 0.5) * shakeIntensity);
                g2.translate(offsetX, offsetY); 
            }

            // 1. DIBUJAR CIELO Y ENTORNO
            if(esNoche) {
                GradientPaint cieloNoche = new GradientPaint(0, 0, new Color(5, 10, 20), 0, h, new Color(40, 25, 25));
                g2.setPaint(cieloNoche);
                g2.fillRect(-2000, -2000, 5000, 5000); 
                
                g2.setColor(new Color(255, 255, 255, 12));
                g2.fillPolygon(new int[]{w - margenX, w / 2 - 150, w / 2 - 50}, new int[]{sueloY, -1000, -1000}, 3);
                g2.fillPolygon(new int[]{margenX, w / 2 + 50, w / 2 + 150}, new int[]{sueloY, -1000, -1000}, 3);
            } else {
                GradientPaint cieloDia = new GradientPaint(0, 0, new Color(135, 206, 235), 0, h, new Color(240, 255, 255));
                g2.setPaint(cieloDia);
                g2.fillRect(-2000, -2000, 5000, 5000); 
            }

            // 2. GENERAR CIUDAD
            Random rand = new Random(42); 
            int currentX = margenX;
            while (currentX < (w - margenX)) {
                int anchoEdificio = 30 + rand.nextInt(40);
                int altoEdificio = 40 + rand.nextInt(90);
                
                g2.setColor(esNoche ? new Color(15, 20, 30) : new Color(150, 160, 170));
                g2.fillRect(currentX, sueloY - altoEdificio, anchoEdificio, altoEdificio);
                
                if(esNoche) {
                    g2.setColor(new Color(255, 255, 150, 80));
                    for(int vY = sueloY - altoEdificio + 10; vY < sueloY - 10; vY += 15) {
                        for(int vX = currentX + 5; vX < currentX + anchoEdificio - 10; vX += 12) {
                            if(rand.nextBoolean()) g2.fillRect(vX, vY, 4, 6);
                        }
                    }
                } else {
                    g2.setColor(new Color(100, 110, 120));
                    for(int vY = sueloY - altoEdificio + 10; vY < sueloY - 10; vY += 15) {
                        for(int vX = currentX + 5; vX < currentX + anchoEdificio - 10; vX += 12) {
                            g2.fillRect(vX, vY, 4, 6);
                        }
                    }
                }
                currentX += anchoEdificio + 2;
            }

            // 3. DIBUJAR EL SUELO INFINITO
            g2.setColor(esNoche ? new Color(25, 30, 40) : new Color(90, 100, 110));
            g2.fillRect(-2000, sueloY, 5000, h);
            g2.setColor(esNoche ? new Color(60, 70, 80) : new Color(60, 70, 80));
            g2.setStroke(new BasicStroke(3));
            g2.drawLine(-2000, sueloY, 5000, sueloY);

            // 4. ESCUDO HOLOGRAFICO 
            g2.setColor(new Color(6, 182, 212, esNoche ? 35 : 60));
            int radioEscudo = (int) (350 * escalaX);
            g2.fillArc((w - margenX) - radioEscudo, sueloY - radioEscudo, radioEscudo * 2, radioEscudo * 2, 90, 90);
            g2.setColor(new Color(6, 182, 212, 120));
            g2.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10, new float[]{5}, 0)); 
            g2.drawArc((w - margenX) - radioEscudo, sueloY - radioEscudo, radioEscudo * 2, radioEscudo * 2, 90, 90);

            // 5. DIBUJAR VEHICULOS (COLOR DINÁMICO Y BANDERAS)
            dibujarCamion(g2, margenX, sueloY, true, esNoche, nombreAtacante); 
            dibujarCamion(g2, w - margenX, sueloY, false, esNoche, nombreDefensor); 

            // 6. DIBUJAR PARTICULAS
            for (Particula p : particulas) p.dibujar(g2);

            // 7. TRAYECTORIAS Y FISICA
            dibujarLineaPrediccion(g2, margenX, sueloY, v1, theta1Deg, limiteT1, escalaX, escalaY, true); 
            if(interceptado) {
                dibujarLineaPrediccion(g2, w - margenX, sueloY, v2, theta2Deg, limiteT1, escalaX, escalaY, false); 
            }

            // Animación
            if (tActual > 0) {
                // Misil Enemigo
                double r1x = v1 * Math.cos(Math.toRadians(theta1Deg)) * tActual;
                double r1y = (v1 * Math.sin(Math.toRadians(theta1Deg)) * tActual) - (0.5 * gravedad * Math.pow(tActual, 2));
                int m1X = margenX + (int)(r1x * escalaX);
                int m1Y = sueloY - (int)(r1y * escalaY);
                
                double v1y_actual = (v1 * Math.sin(Math.toRadians(theta1Deg))) - (gravedad * tActual);
                double v1x_actual = v1 * Math.cos(Math.toRadians(theta1Deg));
                double anguloM1 = Math.atan2(-v1y_actual, v1x_actual); 
                
                if(simulacionEnCurso) particulas.add(new Particula(m1X, m1Y, new Color(200, 100, 50)));
                if (simulacionEnCurso || tActual < limiteT1) {
                    dibujarMisilSprite(g2, m1X, m1Y, anguloM1, new Color(220, 38, 38));
                }

                // Misil Aliado
                if(interceptado || simulacionEnCurso) {
                    double r2x = distancia - (v2 * Math.cos(Math.toRadians(theta2Deg)) * tActual);
                    double r2y = (v2 * Math.sin(Math.toRadians(theta2Deg)) * tActual) - (0.5 * gravedad * Math.pow(tActual, 2));
                    int m2X = margenX + (int)(r2x * escalaX);
                    int m2Y = sueloY - (int)(r2y * escalaY);
                    
                    double v2y_actual = (v2 * Math.sin(Math.toRadians(theta2Deg))) - (gravedad * tActual);
                    double v2x_actual = -v2 * Math.cos(Math.toRadians(theta2Deg)); 
                    double anguloM2 = Math.atan2(-v2y_actual, v2x_actual);
                    
                    if(simulacionEnCurso) particulas.add(new Particula(m2X, m2Y, new Color(150, 200, 255)));
                    if (simulacionEnCurso || tActual < limiteT1) {
                        dibujarMisilSprite(g2, m2X, m2Y, anguloM2, new Color(34, 197, 94));
                    }
                }

                // Explosión
                if (!simulacionEnCurso && tActual >= limiteT1) {
                    dibujarExplosionAnimada(g2, expX, expY, interceptado, zoomLevel);
                }
            }
        }
        
        // --- COLORES TÁCTICOS POR PAÍS ---
        private Color getColorVehiculo(String pais) {
            switch(pais) {
                case "Israel": return new Color(130, 150, 160); // Gris azulado Naval
                case "Irán": return new Color(85, 105, 75); // Verde militar oscuro
                case "EE.UU.": return new Color(200, 180, 140); // Arena desierto
                case "Rusia": return new Color(75, 85, 75); // Verde muy oscuro
                case "Ucrania": return new Color(140, 150, 110); // Verde oliva claro
                case "Corea del N.": return new Color(60, 70, 60); // Gris carbon
                case "Corea del S.": return new Color(150, 160, 150); // Gris tactico claro
                case "China": return new Color(150, 100, 90); // Marron/Rojizo
                case "Taiwán": return new Color(90, 120, 90); // Verde selva
                case "OTAN": return new Color(60, 80, 110); // Azul marino militar
                default: return new Color(190, 160, 120); 
            }
        }

        // --- SISTEMA DE DIBUJO DE BANDERAS (PIXEL ART) ---
        private void dibujarBandera(Graphics2D g2, int x, int y, String pais) {
            // Fondo blanco base y borde
            g2.setColor(Color.WHITE);
            g2.fillRect(x, y, 14, 8);
            g2.setColor(Color.BLACK);
            g2.drawRect(x, y, 14, 8); 

            switch (pais) {
                case "Israel":
                    g2.setColor(Color.BLUE);
                    g2.fillRect(x, y+1, 14, 2);
                    g2.fillRect(x, y+5, 14, 2);
                    break;
                case "Irán":
                    g2.setColor(new Color(46, 139, 87));
                    g2.fillRect(x, y, 14, 3);
                    g2.setColor(Color.RED);
                    g2.fillRect(x, y+5, 14, 3);
                    break;
                case "EE.UU.":
                    g2.setColor(Color.RED);
                    g2.fillRect(x, y+1, 14, 1);
                    g2.fillRect(x, y+3, 14, 1);
                    g2.fillRect(x, y+5, 14, 1);
                    g2.fillRect(x, y+7, 14, 1);
                    g2.setColor(Color.BLUE);
                    g2.fillRect(x, y, 7, 4);
                    break;
                case "Rusia":
                    g2.setColor(Color.BLUE);
                    g2.fillRect(x, y+3, 14, 3);
                    g2.setColor(Color.RED);
                    g2.fillRect(x, y+5, 14, 3);
                    break;
                case "Ucrania":
                    g2.setColor(Color.BLUE);
                    g2.fillRect(x, y, 14, 4);
                    g2.setColor(Color.YELLOW);
                    g2.fillRect(x, y+4, 14, 4);
                    break;
                case "Corea del N.":
                    g2.setColor(Color.BLUE);
                    g2.fillRect(x, y, 14, 2);
                    g2.fillRect(x, y+6, 14, 2);
                    g2.setColor(Color.RED);
                    g2.fillRect(x, y+2, 14, 4);
                    break;
                case "Corea del S.":
                    g2.setColor(Color.WHITE);
                    g2.fillRect(x, y, 14, 8);
                    g2.setColor(Color.RED);
                    g2.fillArc(x+4, y+1, 6, 6, 0, 180);
                    g2.setColor(Color.BLUE);
                    g2.fillArc(x+4, y+1, 6, 6, 180, 180);
                    break;
                case "China":
                    g2.setColor(Color.RED);
                    g2.fillRect(x, y, 14, 8);
                    g2.setColor(Color.YELLOW);
                    g2.fillRect(x+2, y+1, 3, 3);
                    break;
                case "Taiwán":
                    g2.setColor(Color.RED);
                    g2.fillRect(x, y, 14, 8);
                    g2.setColor(Color.BLUE);
                    g2.fillRect(x, y, 7, 4);
                    break;
                case "OTAN":
                    g2.setColor(new Color(0, 51, 153));
                    g2.fillRect(x, y, 14, 8);
                    g2.setColor(Color.WHITE);
                    g2.drawLine(x+7, y+1, x+7, y+7);
                    g2.drawLine(x+4, y+4, x+10, y+4);
                    break;
            }
        }

        private void dibujarCamion(Graphics2D g2, int cX, int cY, boolean enemigo, boolean esNoche, String nombrePais) {
            Color colorVehiculo = getColorVehiculo(nombrePais);
            
            // Chasis y Cabina
            g2.setColor(colorVehiculo);
            g2.fillRoundRect(cX - 20, cY - 12, 55, 10, 4, 4); 
            g2.fillRect(enemigo ? cX + 20 : cX - 20, cY - 20, 15, 12); 
            
            // Estampar la Bandera en el chasis
            int banderaX = enemigo ? cX - 15 : cX + 15;
            dibujarBandera(g2, banderaX, cY - 11, nombrePais);
            
            // Focos encendidos (Solo de noche)
            if(esNoche) { 
                g2.setColor(new Color(255, 255, 150, 150));
                if(enemigo) g2.fillPolygon(new int[]{cX+35, cX+55, cX+55}, new int[]{cY-15, cY-5, cY-25}, 3);
                else        g2.fillPolygon(new int[]{cX-20, cX-40, cX-40}, new int[]{cY-15, cY-5, cY-25}, 3);
            }

            // Llantas
            g2.setColor(Color.BLACK); 
            g2.fillOval(cX - 15, cY - 6, 10, 10);
            g2.fillOval(cX + 5, cY - 6, 10, 10);
            g2.fillOval(cX + 20, cY - 6, 10, 10);
            
            // Lanzador / Batería
            g2.setColor(enemigo ? new Color(130, 40, 40) : new Color(80, 90, 80)); 
            if(enemigo) g2.fillPolygon(new int[]{cX-10, cX+20, cX+10, cX-20}, new int[]{cY-12, cY-35, cY-35, cY-12}, 4);
            else        g2.fillPolygon(new int[]{cX+25, cX-5, cX+5, cX+35}, new int[]{cY-12, cY-35, cY-35, cY-12}, 4);
            
            // Texto Etiqueta
            g2.setColor(enemigo ? new Color(220, 38, 38) : new Color(59, 130, 246));
            g2.setFont(new Font("Consolas", Font.BOLD, 12));
            String etiqueta = enemigo ? "Base Hostil ("+nombrePais+")" : "Radar Defensivo ("+nombrePais+")";
            int textWidth = g2.getFontMetrics().stringWidth(etiqueta);
            g2.drawString(etiqueta, cX - (textWidth/2) + 10, cY + 20);
        }

        private void dibujarLineaPrediccion(Graphics2D g2, int oX, int oY, double v, double angulo, double tMax, double escX, double escY, boolean enemigo) {
            g2.setColor(enemigo ? new Color(220, 38, 38, 60) : new Color(34, 197, 94, 60)); 
            g2.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10, new float[]{8}, 0));
            
            int prevX = oX;
            int prevY = oY;
            for (double t = 0; t <= tMax; t += 0.2) {
                double rx = v * Math.cos(Math.toRadians(angulo)) * t;
                double ry = (v * Math.sin(Math.toRadians(angulo)) * t) - (0.5 * gravedad * t * t);
                int sx = enemigo ? oX + (int)(rx * escX) : oX - (int)(rx * escX);
                int sy = oY - (int)(ry * escY);
                g2.drawLine(prevX, prevY, sx, sy);
                prevX = sx;
                prevY = sy;
            }
        }

        private void dibujarMisilSprite(Graphics2D g2, int x, int y, double anguloRadianes, Color colorBase) {
            Graphics2D g = (Graphics2D) g2.create();
            g.translate(x, y);
            g.rotate(anguloRadianes);
            g.setColor(new Color(255, 100, 0, 200)); 
            g.fillPolygon(new int[]{-8, -20, -20, -8}, new int[]{-3, -6, 6, 3}, 4);
            g.setColor(new Color(255, 255, 50, 200)); 
            g.fillPolygon(new int[]{-8, -15, -8}, new int[]{-2, 0, 2}, 3);
            g.setColor(colorBase);
            g.fillRoundRect(-8, -3, 14, 6, 3, 3);
            g.setColor(Color.WHITE);
            g.fillPolygon(new int[]{6, 12, 6}, new int[]{-3, 0, 3}, 3);
            g.setColor(Color.DARK_GRAY); 
            g.fillRect(-6, -5, 4, 10);
            g.dispose();
        }

        private void dibujarExplosionAnimada(Graphics2D g2, int x, int y, boolean exito, double zoom) {
            int radio = exito ? 60 : 100;
            g2.setColor(new Color(255, 200, 50, 150)); 
            g2.fillOval(x - radio/2, y - radio/2, radio, radio);
            g2.setColor(new Color(255, 80, 0, 200)); 
            g2.fillOval(x - radio/3, y - radio/3, radio/2 + 10, radio/2 + 10);
            g2.setColor(Color.WHITE);
            g2.fillOval(x - 5, y - 5, 10, 10);
            
            int fontSize = (int) (18 / zoom);
            if (fontSize < 10) fontSize = 10;
            g2.setFont(new Font("Consolas", Font.BOLD, fontSize));
            
            if(exito) {
                g2.setColor(new Color(0, 255, 100));
                g2.drawString(">> IMPACTO TÁCTICO", x + (int)(40 / zoom), y - (int)(10 / zoom));
            } else {
                g2.setColor(Color.RED);
                g2.drawString("!! CIUDAD ALCANZADA !!", x - (int)(90 / zoom), y - (int)(60 / zoom));
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new War().setVisible(true));
    }
}