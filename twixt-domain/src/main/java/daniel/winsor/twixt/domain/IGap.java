package daniel.winsor.twixt.domain;

/**
 * Represents the pattern of a particular move type.
 * @author Daniel
 *
 */
public interface IGap {
    
    Direction getDirection();
    
    GapType getType();
    
    Direction getPathDirection(final PathType path);
    
    IGap getReversedGap();
    
}