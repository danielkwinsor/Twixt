package daniel.winsor.twixt.domain.board;

/**
 * Also hard codes a default size, but this size may be overridden.
 * @author Daniel
 *
 */
public enum BoardType {
    STANDARD_24(24),
    HUGE_36(36),
    SMALL_12(12),
    UPPER_LEFT_QUADRANT_12(12),
    DIAGONAL_30_DEGREES(24),
    DIAGONAL_45_DEGREES(24),
    IMURI_30(30);
    
    private final int defaultSize;
    
    BoardType(int defaultSize) {
        this.defaultSize = defaultSize;
    }

    public int getDefaultSize() {
        return defaultSize;
    }
    
    public boolean isRegularSquare() {
        switch (this) {
        case STANDARD_24:
        case HUGE_36:
        case SMALL_12:
        case IMURI_30:
            return true;
        default:
            return false;
        }
    }
    
    public boolean isQuadrantSquare() {
        switch (this) {
        case UPPER_LEFT_QUADRANT_12:
            return true;
        default:
            return false;
        }
    }
    
    public boolean isDiagonal() {
        switch (this) {
        case DIAGONAL_30_DEGREES:
        case DIAGONAL_45_DEGREES:
            return true;
        default:
            return false;
        }
    }
}
