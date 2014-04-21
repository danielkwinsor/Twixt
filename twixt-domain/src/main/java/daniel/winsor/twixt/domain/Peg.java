package daniel.winsor.twixt.domain;

public class Peg {
    private Hole hole;
    private Team owner;
    
    public Hole getHole() {
        return hole;
    }
    public void setHole(Hole hole) {
        this.hole = hole;
    }
    public Team getOwner() {
        return owner;
    }
    public void setOwner(Team owner) {
        this.owner = owner;
    }
}
