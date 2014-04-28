package daniel.winsor.twixt.domain;

/**
 * A game piece that has been placed onto the board in a Hole.
 * @author Daniel
 *
 */
public class Peg {
    private Hole hole;
    private Team owner;
    
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
}
