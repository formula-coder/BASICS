package game;

public class TurnDetail {
    private int turnNumber;
    private String firstPlayerName;
    private int firstPlayerSpeed;
    private String secondPlayerName;
    private int secondPlayerSpeed;
    private String firstPlayerAction;
    private String secondPlayerAction;
    private String firstPlayerEffect;
    private String secondPlayerEffect;
    private int firstPlayerHpAfter;
    private int secondPlayerHpAfter;

    public TurnDetail(int turnNumber) {
        this.turnNumber = turnNumber;
    }

    // Getters y Setters
    public int getTurnNumber() { return turnNumber; }
    public void setTurnNumber(int turnNumber) { this.turnNumber = turnNumber; }

    public String getFirstPlayerName() { return firstPlayerName; }
    public void setFirstPlayerName(String firstPlayerName) { this.firstPlayerName = firstPlayerName; }

    public int getFirstPlayerSpeed() { return firstPlayerSpeed; }
    public void setFirstPlayerSpeed(int firstPlayerSpeed) { this.firstPlayerSpeed = firstPlayerSpeed; }

    public String getSecondPlayerName() { return secondPlayerName; }
    public void setSecondPlayerName(String secondPlayerName) { this.secondPlayerName = secondPlayerName; }

    public int getSecondPlayerSpeed() { return secondPlayerSpeed; }
    public void setSecondPlayerSpeed(int secondPlayerSpeed) { this.secondPlayerSpeed = secondPlayerSpeed; }

    public String getFirstPlayerAction() { return firstPlayerAction; }
    public void setFirstPlayerAction(String firstPlayerAction) { this.firstPlayerAction = firstPlayerAction; }

    public String getSecondPlayerAction() { return secondPlayerAction; }
    public void setSecondPlayerAction(String secondPlayerAction) { this.secondPlayerAction = secondPlayerAction; }

    public String getFirstPlayerEffect() { return firstPlayerEffect; }
    public void setFirstPlayerEffect(String firstPlayerEffect) { this.firstPlayerEffect = firstPlayerEffect; }

    public String getSecondPlayerEffect() { return secondPlayerEffect; }
    public void setSecondPlayerEffect(String secondPlayerEffect) { this.secondPlayerEffect = secondPlayerEffect; }

    public int getFirstPlayerHpAfter() { return firstPlayerHpAfter; }
    public void setFirstPlayerHpAfter(int firstPlayerHpAfter) { this.firstPlayerHpAfter = firstPlayerHpAfter; }

    public int getSecondPlayerHpAfter() { return secondPlayerHpAfter; }
    public void setSecondPlayerHpAfter(int secondPlayerHpAfter) { this.secondPlayerHpAfter = secondPlayerHpAfter; }

    public String getFormattedMessage() {
        StringBuilder sb = new StringBuilder();
        sb.append("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        sb.append("⚔️ TURNO ").append(turnNumber).append("\n");
        sb.append("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        // Quién empieza y por qué
        sb.append("🎯 ").append(firstPlayerName).append(" inicia el turno (Velocidad: ").append(firstPlayerSpeed);
        sb.append(" > ").append(secondPlayerName).append(": ").append(secondPlayerSpeed).append(")\n\n");

        // Primer jugador
        sb.append("▶ ").append(firstPlayerName).append(": ").append(firstPlayerAction).append("\n");
        sb.append("   └─ ").append(firstPlayerEffect).append("\n");
        sb.append("   ❤️ Vida restante: ").append(firstPlayerHpAfter).append(" HP\n\n");

        // Segundo jugador
        sb.append("▶ ").append(secondPlayerName).append(": ").append(secondPlayerAction).append("\n");
        sb.append("   └─ ").append(secondPlayerEffect).append("\n");
        sb.append("   ❤️ Vida restante: ").append(secondPlayerHpAfter).append(" HP\n\n");

        return sb.toString();
    }
}
