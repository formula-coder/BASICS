package model;

import java.io.Serializable;

public class Robot implements Serializable {
    private static final long serialVersionUID = 1L;

    private String name;
    private Stats stats;
    private int turnCounter;
    private boolean dodgeActive;
    private int dodgeCount;

    public Robot(String name, Stats stats) {
        this.name = name;
        this.stats = stats;
        this.turnCounter = 0;
        this.dodgeActive = false;
        this.dodgeCount = 0;
    }

    public double calculateNormalDamage(Robot attacker) {
        int atkValue = attacker.getStats().getAtk();
        int defValue = this.stats.getDef();
        return Math.pow(atkValue, 2) / (defValue + atkValue);
    }

    public double calculateSpecialDamage(Robot attacker) {
        int atkValue = attacker.getStats().getAtk();
        int defValue = this.stats.getDef();
        int nrgValue = attacker.getStats().getNrg();
        double boostedAtk = atkValue + 0.5 * nrgValue;
        return Math.pow(boostedAtk, 2) / (boostedAtk + defValue);
    }

    public boolean tryDodge() {
        double probability = 0.5;
        if (dodgeCount >= 2) {
            probability = 0.75;
        }
        boolean dodged = Math.random() < probability;
        if (dodged) {
            dodgeActive = true;
        }
        return dodged;
    }

    public void resetDodge() {
        dodgeActive = false;
        dodgeCount = 0;
    }

    public void incrementDodgeCount() {
        dodgeCount++;
    }

    // Getters y Setters
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public Stats getStats() { return stats; }
    public void setStats(Stats stats) { this.stats = stats; }
    public int getTurnCounter() { return turnCounter; }
    public void setTurnCounter(int turnCounter) { this.turnCounter = turnCounter; }
    public boolean isDodgeActive() { return dodgeActive; }
    public void setDodgeActive(boolean dodgeActive) { this.dodgeActive = dodgeActive; }
    public int getDodgeCount() { return dodgeCount; }

    public void takeDamage(double damage) {
        int newHp = (int)(stats.getHp() - damage);
        stats.setHp(Math.max(0, newHp));
    }

    public void heal() {
        int newHp = stats.getHp() + 10;
        stats.setHp(Math.min(100, newHp));
    }

    public void charge() {
        int newNrg = stats.getNrg() + 10;
        stats.setNrg(Math.min(100, newNrg));
    }

    public boolean isAlive() {
        return stats.getHp() > 0;
    }
}
