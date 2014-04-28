package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.GapType.*;
import static daniel.winsor.twixt.domain.Direction.*;

/**
 * This version of a Gap does not correspond to the "gap"
 * in "TwixT" literature. @see GapType.
 * @author Daniel
 *
 */
public final class Gap implements IGap {
    /**
     * Immutable object that represents a null value.
     */
    public static final IGap nullGap = new Gap(NULL_GAP_TYPE, NULL_DIRECTION);
    private GapType type;
    private Direction direction;
    
    public Gap(final GapType type, final Direction direction) {
        setType(type);
        setDirection(direction);
    }
    
    /* (non-Javadoc)
     * @see daniel.winsor.twixt.domain.IGap#getDirection()
     */
    @Override
    public Direction getDirection() {
        return direction;
    }
    
    private void setDirection(final Direction direction) {
        this.direction = direction;
    }
    
    /* (non-Javadoc)
     * @see daniel.winsor.twixt.domain.IGap#getType()
     */
    @Override
    public GapType getType() {
        return type;
    }
    
    private void setType(final GapType type) {
        this.type = type;
    }
    
    @Override
    public Direction getPathDirection(final PathType path) {
        switch (path) {
        case DIRECT:
            switch (getType()) {
            case SINGLE:
                return getDirection();
            default:
                break;
            }
            break;
            
        case LEFT:
            switch (getType()) {
            case DOUBLE_STRAIGHT:
                return getDirection();
            case DOUBLE_DIAMOND:
                return getDirection().rotateLeft();
            case DOUBLE_SQUARE:
                return getDirection().rotateLeft();
            case DOUBLE_SHORT_DIAMOND:
                return getDirection().rotateLeft().rotateLeft();
            default:
                break;
            }
            break;
            
        case RIGHT:
            switch (getType()) {
            case DOUBLE_STRAIGHT:
                return getDirection();
            case DOUBLE_DIAMOND:
                return getDirection();
            case DOUBLE_SQUARE:
                return getDirection().rotateRight();
            case DOUBLE_SHORT_DIAMOND:
                return getDirection().rotateRight();
            default:
                break;
            }
            break;
        default:
            break;
        }
        return NULL_DIRECTION;
    }
    
    /* (non-Javadoc)
     * @see daniel.winsor.twixt.domain.IGap#getReversedGap()
     */
    @Override
    public IGap getReversedGap() {
        return new Gap(getType(), getDirection().getOpposite());
    }
    
    public static IGap getGapFromHoles(final Hole start, final Hole dest) {
        final GapType gapType = GapType.getGapType(start, dest);
        if (gapType == NULL_GAP_TYPE) {
            return nullGap;
        }
        
        final int changeX = start.getXCoord() - dest.getXCoord();
        final int changeY = start.getYCoord() - dest.getYCoord();
        final int absX = Math.abs(changeX);
        final int absY = Math.abs(changeY);
        boolean left = changeX >= 0;
        boolean up = changeY >= 0;
        
        //if I go more to the sides...
        //true == LEFT_UP, false == UP_LEFT
        boolean sidesGreater = absX >= absY;
        
        //special logic needed for the gaps that go "straight" along an axis
        //of the board
        if (gapType == DOUBLE_DIAMOND || gapType == DOUBLE_SHORT_DIAMOND) {
            left = changeX > 0 || (changeX == 0 && (changeY == -4 || changeY == -2));
            up = changeY > 0 || (changeY == 0 && (changeX == 4 || changeX == 2));
            if ((left == true && up == true)
                    || (left == false && up == false)) {
                sidesGreater = absX != absY;
            }
            else {
                sidesGreater = absX == absY;
            }
        }
        
        if (left == true && up == true && sidesGreater == true) {
            return new Gap(gapType, LEFT_UP);
        }
        else if (left == true && up == true && sidesGreater == false) {
            return new Gap(gapType, UP_LEFT);
        }
        else if (left == false && up == true && sidesGreater == false) {
            return new Gap(gapType, UP_RIGHT);
        }
        else if (left == false && up == true && sidesGreater == true) {
            return new Gap(gapType, RIGHT_UP);
        }
        else if (left == false && up == false && sidesGreater == true) {
            return new Gap(gapType, RIGHT_DOWN);
        }
        else if (left == false && up == false && sidesGreater == false) {
            return new Gap(gapType, DOWN_RIGHT);
        }
        else if (left == true && up == false && sidesGreater == false) {
            return new Gap(gapType, DOWN_LEFT);
        }
        else if (left == true && up == false && sidesGreater == true) {
            return new Gap(gapType, LEFT_DOWN);
        }
        
        return nullGap;
    }
    
    @Override
    public String toString() {
        return "Gap(" + getType() + ", " + getDirection() + ")";
    }
    
    @Override
    public boolean equals(final Object compare) {
        if (compare == null || compare instanceof Gap == false) {
            return false;
        }
        
        final IGap other = (IGap) compare;
        return (getType().equals(other.getType())
                && getDirection().equals(other.getDirection()));
    }
    
    @Override
    public int hashCode() {
        return ((getDirection().ordinal() * GapType.NUM_GAP_TYPES)
                + getType().ordinal());
    }
}
