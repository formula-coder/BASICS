package model;

public enum Move {
    ATTACK,
    SPECIAL,
    DODGE,
    HEAL,
    CHARGE;

    public static Move fromString(String text) {
        try {
            return Move.valueOf(text.toUpperCase());
        } catch (IllegalArgumentException e) {
            return ATTACK;
        }
    }
}