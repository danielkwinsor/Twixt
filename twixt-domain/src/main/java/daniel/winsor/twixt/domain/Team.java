package daniel.winsor.twixt.domain;

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
