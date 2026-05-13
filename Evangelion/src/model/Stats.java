package model;

import java.io.Serializable;

public class Stats implements Serializable {
    private static final long serialVersionUID = 1L;

    private int atk;
    private int def;
    private int spd;
    private int nrg;
    private int hp;

    public Stats(int atk, int def, int spd, int nrg) {
        this.atk = atk;
        this.def = def;
        this.spd = spd;
        this.nrg = nrg;
        this.hp = 100;
    }

    public boolean isValid() {
        return (atk + def + spd + nrg) == 100;
    }

    // Getters y Setters
    public int getAtk() { return atk; }
    public void setAtk(int atk) { this.atk = atk; }
    public int getDef() { return def; }
    public void setDef(int def) { this.def = def; }
    public int getSpd() { return spd; }
    public void setSpd(int spd) { this.spd = spd; }
    public int getNrg() { return nrg; }
    public void setNrg(int nrg) { this.nrg = nrg; }
    public int getHp() { return hp; }
    public void setHp(int hp) { this.hp = hp; }

    @Override
    public String toString() {
        return String.format("ATK: %d, DEF: %d, SPD: %d, NRG: %d, HP: %d",
                atk, def, spd, nrg, hp);
    }
}
