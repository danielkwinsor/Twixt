package daniel.winsor.twixt.domain;

/**
 * A game piece that has been placed onto the board in a Hole.
 * @author Daniel
 *
 */
public class Peg {
    protected Hole hole;
    protected Team owner;
    protected boolean[] linkedDirs = new boolean[Direction.NUM_DIRECTIONS];
    protected boolean[] blockedDirs = new boolean[Direction.NUM_DIRECTIONS];
    
    /**
     * Immutable object that represents a null value.
     */
    public static final Peg nullPeg =
            new ImmutablePeg(Hole.nullHole, Team.NULL_TEAM);
    
    public Peg(final Hole hole, final Team owner) {
        setHole(hole);
        setOwner(owner);
    }

    public Peg(final Peg peg) {
        this(peg.getHole(), peg.getOwner());
        this.linkedDirs = peg.linkedDirs.clone();
        this.blockedDirs = peg.blockedDirs.clone();
    }
    
    public Hole getHole() {
        return hole;
    }
    
    public void setHole(final Hole hole) {
        this.hole = hole;
    }
    
    public Team getOwner() {
        return owner;
    }
    
    public void setOwner(final Team owner) {
        this.owner = owner;
    }
    
    public boolean isLinked(Direction direction) {
        return linkedDirs[direction.ordinal()];
    }
    
    public boolean isBlocked(Direction direction) {
        return blockedDirs[direction.ordinal()];
    }
    
    public void addBlock(Direction direction) {
        blockedDirs[direction.ordinal()] = true;
    }
    
    public void removeBlock(Direction direction) {
        blockedDirs[direction.ordinal()] = false;
    }
    
    public void addLink(Direction direction) {
        linkedDirs[direction.ordinal()] = true;
    }
    
    public void removeLink(Direction direction) {
        linkedDirs[direction.ordinal()] = false;
    }
    
    @Override
    public String toString() {
        return "Peg: " + getHole() + " " + getOwner();
    }
    
    /**
     * This equals does not compare the links or blocks
     */
    @Override
    public boolean equals(final Object compare) {
        if (compare == null || compare instanceof Peg == false) {
            return false;
        }
        
        final Peg other = (Peg) compare;
        return (getHole().equals(other.getHole())
                && getOwner().equals(other.getOwner()));
    }
    
    @Override
    public int hashCode() {
        return ((getHole().hashCode() * Team.values().length)
                + getOwner().ordinal());
    }
}
