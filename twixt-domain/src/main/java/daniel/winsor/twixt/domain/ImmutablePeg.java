package daniel.winsor.twixt.domain;

/**
 * The sets, adds, and removes do nothing.
 * Package visibility by design.
 * @author Daniel
 *
 */
class ImmutablePeg extends Peg {
    ImmutablePeg(final Hole hole, final Team owner) {
        super(hole, owner);
        super.setHole(hole);
        super.setOwner(owner);
    }
    
    ImmutablePeg(Peg peg) {
        super(peg);
        super.setHole(peg.getHole());
        super.setOwner(peg.getOwner());
    }

    @Override
    public void setOwner(final Team owner) {
    }
    
    @Override
    public void setHole(final Hole hole) {
    }
    
    @Override
    public void addBlock(Direction direction) {
    }
    
    @Override
    public void removeBlock(Direction direction) {
    }
    
    @Override
    public void addLink(Direction direction) {
    }
    
    @Override
    public void removeLink(Direction direction) {
    }
    
    @Override
    public String toString() {
        return "Immutable" + super.toString();
    }
}