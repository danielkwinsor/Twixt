package daniel.winsor.twixt.domain;

/**
 * The adopted convention is that black connects left to right
 * and red connects up and down
 * @author Daniel
 *
 */
public enum Team {
    RED,
    BLACK,
    UNOWNED,
    NULL_TEAM;
    
    public Team getOpponent() {
        switch (this) {
        case RED:
            return BLACK;
        case BLACK:
            return RED;
        default:
            return NULL_TEAM;
        }
    }
}
