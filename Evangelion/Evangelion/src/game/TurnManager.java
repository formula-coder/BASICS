package game;

import model.Robot;

public class TurnManager {
    private Robot robot1;
    private Robot robot2;
    private int turnValue1;
    private int turnValue2;

    public TurnManager(Robot robot1, Robot robot2) {
        this.robot1 = robot1;
        this.robot2 = robot2;
        this.turnValue1 = 0;
        this.turnValue2 = 0;
    }

    public Robot getNextTurn() {
        turnValue1 += robot1.getStats().getSpd();
        turnValue2 += robot2.getStats().getSpd();

        if (turnValue1 >= 100 && turnValue2 >= 100) {
            if (turnValue1 > turnValue2) {
                turnValue1 -= 100;
                return robot1;
            } else {
                turnValue2 -= 100;
                return robot2;
            }
        } else if (turnValue1 >= 100) {
            turnValue1 -= 100;
            return robot1;
        } else if (turnValue2 >= 100) {
            turnValue2 -= 100;
            return robot2;
        }

        return null;
    }

    public void reset() {
        turnValue1 = 0;
        turnValue2 = 0;
    }
}