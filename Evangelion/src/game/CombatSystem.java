package game;

import model.*;
import java.util.ArrayList;
import java.util.List;

public class CombatSystem {
    private Robot player;
    private Robot opponent;
    private TurnManager turnManager;
    private List<String> combatLog;
    private boolean playerDodgeActive;

    public CombatSystem(Robot player, Robot opponent) {
        this.player = player;
        this.opponent = opponent;
        this.turnManager = new TurnManager(player, opponent);
        this.combatLog = new ArrayList<>();
        this.playerDodgeActive = false;
    }

    public String executeMove(Robot attacker, Robot defender, Move move) {
        StringBuilder result = new StringBuilder();
        String moveResult = "";

        switch (move) {
            case ATTACK:
                double damage = defender.calculateNormalDamage(attacker);
                boolean dodged = defender.tryDodge();
                if (dodged) {
                    moveResult = "DODGE";
                    result.append(attacker.getName()).append(" atacó pero ").append(defender.getName()).append(" esquivó!");
                } else {
                    defender.takeDamage(damage);
                    moveResult = "HIT";
                    result.append(attacker.getName()).append(" causó ").append(String.format("%.2f", damage))
                            .append(" de daño a ").append(defender.getName());
                }
                defender.resetDodge();
                break;

            case SPECIAL:
                if (attacker.getStats().getNrg() > 0) {
                    double specialDamage = defender.calculateSpecialDamage(attacker);
                    boolean specialDodged = defender.tryDodge();
                    if (specialDodged) {
                        moveResult = "DODGE";
                        result.append(attacker.getName()).append(" usó ataque especial pero ").append(defender.getName()).append(" esquivó!");
                    } else {
                        defender.takeDamage(specialDamage);
                        moveResult = "HIT";
                        result.append(attacker.getName()).append(" usó ataque especial causando ").append(String.format("%.2f", specialDamage))
                                .append(" de daño a ").append(defender.getName());
                    }
                    attacker.getStats().setNrg(0);
                    defender.resetDodge();
                } else {
                    result.append("Energía insuficiente para ataque especial!");
                    moveResult = "FAIL";
                }
                break;

            case DODGE:
                attacker.incrementDodgeCount();
                attacker.tryDodge();
                result.append(attacker.getName()).append(" se prepara para esquivar! (Probabilidad: ").append(attacker.getDodgeCount() >= 2 ? "75%" : "50%").append(")");
                moveResult = "DODGE_SET";
                break;

            case HEAL:
                attacker.heal();
                result.append(attacker.getName()).append(" se curó 10 HP. HP actual: ").append(attacker.getStats().getHp());
                moveResult = "HEAL";
                break;

            case CHARGE:
                attacker.charge();
                result.append(attacker.getName()).append(" cargó 10 de energía. NRG actual: ").append(attacker.getStats().getNrg());
                moveResult = "CHARGE";
                break;
        }

        combatLog.add(result.toString());
        return moveResult;
    }

    public boolean isGameOver() {
        return !player.isAlive() || !opponent.isAlive();
    }

    public Robot getWinner() {
        if (!player.isAlive()) return opponent;
        if (!opponent.isAlive()) return player;
        return null;
    }

    public List<String> getCombatLog() { return combatLog; }
    public Robot getPlayer() { return player; }
    public Robot getOpponent() { return opponent; }
    public TurnManager getTurnManager() { return turnManager; }
}
