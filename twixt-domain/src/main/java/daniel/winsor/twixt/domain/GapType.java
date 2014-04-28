package daniel.winsor.twixt.domain;

/**
 * Related to the "TwixT" definition of "gap".
 * This GapType represents the different types of patterns
 * that can be made.
 * DOUBLE_DIAMOND SAME AS TILT AND BEAM.
 * DOUBLE_SQUARE AKA COIGN.
 * DOUBLE_SHORT_DIAMOND AKA MESH AND SHORT.
 * @author Daniel
 *
 */
public enum GapType {
    SINGLE,
    DOUBLE_DIAMOND, //SAME AS TILT AND BEAM
    DOUBLE_SQUARE, //AKA COIGN
    DOUBLE_SHORT_DIAMOND, //AKA MESH AND SHORT
    DOUBLE_STRAIGHT,
    
    NULL_GAP_TYPE;
    
    public static final int NUM_GAP_TYPES = 5;
    
    public boolean isSingle() {
        return this == SINGLE;
    }
    
    public boolean isDoubleStraight() {
        return this == DOUBLE_STRAIGHT;
    }
    
    public boolean isDouble() {
        return this != SINGLE && this != NULL_GAP_TYPE;
    }
    
    public static GapType getGapType(final Hole start, final Hole dest) {
        if (start == null || dest == null) {
            return NULL_GAP_TYPE;
        }
        if (Hole.nullHole.equals(start) || Hole.nullHole.equals(dest)) {
            return NULL_GAP_TYPE;
        }
        
        final int x = Math.abs(start.getXCoord() - dest.getXCoord());
        final int y = Math.abs(start.getYCoord() - dest.getYCoord());
        switch (x + y) {
        case 0:
        case 1:
            return NULL_GAP_TYPE;
        case 2:
            return DOUBLE_SHORT_DIAMOND;
        case 3:
            return SINGLE;
        case 4:
            if (x == 1 || y == 1) {
                return DOUBLE_SQUARE;
            }
            else if (x == 0 || y == 0) {
                return DOUBLE_DIAMOND;
            }
            else {
                return NULL_GAP_TYPE;
            }
        case 5:
            return NULL_GAP_TYPE;
        case 6:
            if (x == 3) {
                return DOUBLE_DIAMOND;
            }
            else if (x == 2 || y == 2) {
                return DOUBLE_STRAIGHT;
            }
            else {
                return NULL_GAP_TYPE;
            }
        default:
            return NULL_GAP_TYPE;
        }
    }
}
