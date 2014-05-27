package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.*;

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
    DIAGONAL_45_DEGREES(23),
    IMURI_30(30);
    
    /**
     * The board is not supposed to go over this size
     */
    public static final int MAX_SIZE = HUGE_36.getDefaultSize();
    
    private final int defaultSize;
    private final int defaultSizeMinusOne;
    
    BoardType(int defaultSize) {
        this.defaultSize = defaultSize;
        defaultSizeMinusOne = defaultSize - 1;
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
    
    /**
     * A quadrant type board is one where only 1/4 of the board
     * is shown, often for puzzles.
     * @return
     */
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
    
    /**
     * Rotates a Hole about the center midpoint of the
     * default board.
     * Will yield incorrect results if the board
     * has been handicapped.
     * It is assumed the hole is already within the bounds
     * of the board.
     * You can do this faster if you don't need to check for
     * null holes.
     * @param hole
     * @return
     */
    public Hole rotateClockwiseAboutBoard(Hole hole) {
        if (Hole.nullHole.equals(hole)) {
            return Hole.nullHole;
        }
        return new Hole(
                defaultSizeMinusOne - hole.getYCoord(),
                hole.getXCoord());
    }
}
