package daniel.winsor.twixt.domain;

/**
 * TODO decide on colors (is it w/b or r/b?).  Decide on better names.
 * @author Daniel
 *
 */
public enum Team {
    //TODO better names
    LEFT_RIGHT,
    UP_DOWN,
    UNOWNED,
    NULL_TEAM;
    
    public Team getOpponent() {
        switch (this) {
        case LEFT_RIGHT:
            return UP_DOWN;
        case UP_DOWN:
            return LEFT_RIGHT;
        default:
            return NULL_TEAM;
        }
    }
}
