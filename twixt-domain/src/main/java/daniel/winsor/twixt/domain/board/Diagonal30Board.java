package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.*;

/**
 * TODO list of holes, maybe interface for diagonal games
 * Should not be handicapped
 * @author Daniel
 *
 */
public class Diagonal30Board extends AbstractBoard implements IBoardFormat {
    public Diagonal30Board(BoardType boardType) {
        super(boardType);
        if (boardType != BoardType.DIAGONAL_30_DEGREES) {
            throw new IllegalArgumentException();
        }
    }
    
    /**
     * TODO Hardcode the holes that are outside the playing area.
     */
    @Override
    protected boolean isCornerHole(final Hole hole) {
        return true;
    }
    
    /**
     * TODO Hardcode the holes that are behind the finish line.
     */
    @Override
    public boolean isBehindFinishLine(final Hole hole, final Team team) {
        return false;
    }
}
