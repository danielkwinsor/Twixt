package daniel.winsor.twixt.domain;

/**
 * A Jump represents going from one Hole to another 
 * in one of the special "moves" that may take 2 or 3 pegs,
 * with 1 or 2 (or 3 or 4) links inbetween.
 * @author Daniel
 *
 */
public final class Jump implements IGap {
    public static final Jump nullJump = new Jump(Hole.nullHole, Gap.nullGap);
    private IGap gap;
    private Hole start;
    
    public Jump(final Hole start, final IGap gap) {
        setGap(gap);
        setStart(start);
    }
    
    public IGap getGap() {
        return gap;
    }
    private void setGap(final IGap gap) {
        this.gap = gap;
    }
    public Hole getStart() {
        return start;
    }
    private void setStart(final Hole start) {
        this.start = start;
    }
    
    public Jump getReversedJump() {
        return new Jump(getDest(), getGap().getReversedGap());
    }
    
    public Hole getDest() {
        return getStart().getHoleFromDir(
                getGap().getDirection(), getGap().getType());
    }

    public Hole getIntHole(final PathType pathType) {
        Direction direction = getGap().getPathDirection(pathType);
        return getStart().getHoleFromDir(direction);
    }
    
    /**
     * Also returns true if it matches the reversed Jump 
     */
    @Override
    public boolean equals(final Object compare) {
        if (compare == null || compare instanceof Jump == false) {
            return false;
        }
        
        Jump other = (Jump) compare;
        if (getGap().equals(other.getGap())) {
            if (getStart().equals(other.getStart())) {
                return true;
            }
        }
        else if (getGap().equals(other.getGap().getReversedGap())) {
            if (getStart().equals(other.getDest())) {
                return true;
            }
        }
        return false;
    }
    
    @Override
    public int hashCode() {
        return ((getStart().hashCode() * Direction.NUM_DIRECTIONS)
                + getGap().hashCode());
    }
    
    @Override
    public String toString() {
        return "Jump(" + getStart() + ", " + getGap() + ")";
    }

    @Override
    public Direction getDirection() {
        return getGap().getDirection();
    }

    @Override
    public GapType getType() {
        return getGap().getType();
    }

    @Override
    public Direction getPathDirection(final PathType path) {
        return getGap().getPathDirection(path);
    }

    @Override
    public IGap getReversedGap() {
        return getGap().getReversedGap();
    }
}
