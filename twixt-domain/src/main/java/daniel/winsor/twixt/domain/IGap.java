package daniel.winsor.twixt.domain;


public interface IGap {
    
    public abstract Direction getDirection();
    
    public abstract GapType getType();
    
    public abstract Direction getPathDirection(PathType path);
    
    public abstract IGap getReversedGap();
    
}