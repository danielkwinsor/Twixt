package daniel.winsor.twixt.domain;

/**
 * There are 8 "Knight" like directions by which 2 pegs can link
 * The order of the enum matters below, because they are intended
 * to rotate clockwise or CCW.  Based on the type of Gap, the direction
 * may be slightly different.  For instance, LEFT_UP for
 * GapType.DOUBLE_DIAMOND is at the 9 o'clock position, while LEFT_UP
 * for a GapType.SINGLE_JUMP is at the 10 o'clock position.
 * @author Daniel
 *
 */
public enum Direction {
    LEFT_UP,
    UP_LEFT,
    UP_RIGHT,
    RIGHT_UP,
    RIGHT_DOWN,
    DOWN_RIGHT,
    DOWN_LEFT,
    LEFT_DOWN,
    
    NULL_DIRECTION;
    
    public static final int NUM_DIRECTIONS = 8;
    
    public Direction getOpposite() {
        if (this == NULL_DIRECTION) {
            return NULL_DIRECTION;
        }
        return Direction.values()[((this.ordinal() + 4) % NUM_DIRECTIONS)];
//        switch (this) {
//        case LEFT_UP:
//            return RIGHT_DOWN;
//        case UP_LEFT:
//            return DOWN_RIGHT;
//        case UP_RIGHT:
//            return DOWN_LEFT;
//        case RIGHT_UP:
//            return LEFT_DOWN;
//        case RIGHT_DOWN:
//            return LEFT_UP;
//        case DOWN_RIGHT:
//            return UP_LEFT;
//        case DOWN_LEFT:
//            return UP_RIGHT;
//        case LEFT_DOWN:
//            return DOWN_RIGHT;
//        }
//        return NULL_DIRECTION;
    }
    
    public Direction rotateRight() {
        return rotateClockwise();
    }
    
    public Direction rotateLeft() {
        return rotateCounterClockwise();
    }
    
    public Direction rotateClockwise() {
        if (this == NULL_DIRECTION) {
            return NULL_DIRECTION;
        }
        return Direction.values()[((this.ordinal() + 1) % NUM_DIRECTIONS)];
//        switch (this) {
//        case LEFT_UP:
//            return UP_LEFT;
//        case UP_LEFT:
//            return UP_RIGHT;
//        case UP_RIGHT:
//            return RIGHT_UP;
//        case RIGHT_UP:
//            return RIGHT_DOWN;
//        case RIGHT_DOWN:
//            return DOWN_RIGHT;
//        case DOWN_RIGHT:
//            return DOWN_LEFT;
//        case DOWN_LEFT:
//            return LEFT_DOWN;
//        case LEFT_DOWN:
//            return LEFT_UP;
//        }
//        return NULL_DIRECTION;
    }
    
    public Direction rotateCounterClockwise() {
        if (this == NULL_DIRECTION) {
            return NULL_DIRECTION;
        }
        return Direction.values()[((this.ordinal() + 7) % NUM_DIRECTIONS)];
//        switch (this) {
//        case LEFT_UP:
//            return LEFT_DOWN;
//        case UP_LEFT:
//            return LEFT_UP;
//        case UP_RIGHT:
//            return UP_LEFT;
//        case RIGHT_UP:
//            return UP_RIGHT;
//        case RIGHT_DOWN:
//            return RIGHT_UP;
//        case DOWN_RIGHT:
//            return RIGHT_DOWN;
//        case DOWN_LEFT:
//            return DOWN_RIGHT;
//        case LEFT_DOWN:
//            return DOWN_LEFT;
//        }
//        return NULL_DIRECTION;
    }
}
