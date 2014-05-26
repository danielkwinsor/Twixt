package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.*;
import daniel.winsor.twixt.domain.board.data.*;

/**
 * Does most of the work of handling logic common to all boards.
 * @author Daniel
 *
 */
public abstract class AbstractBoard implements IBoard {
    protected final BoardType boardType;
    protected final ArrayPegData pegs;

    public AbstractBoard(BoardType boardType) {
        this.boardType = boardType;
        pegs = new ArrayPegData(boardType);
    }
    
    public Peg getPeg(final Hole hole) {
        return pegs.getPeg(hole);
    }
    
    @Override
    public int getMaxXSize() {
        return getBoardType().getDefaultSize();
    }
    
    @Override
    public int getMaxYSize() {
        return getBoardType().getDefaultSize();
    }
    
    @Override
    public BoardType getBoardType() {
        return boardType;
    }
    
    /**
     * TODO optimize by converting to hashCode?
     */
    @Override
    public boolean isInsideBoard(final Hole hole) {
        final int x = hole.getXCoord();
        final int y = hole.getYCoord();
        if (x >= 0 && x < getMaxXSize()) {
            if (y >= 0 && y < getMaxYSize()) {
                if (!isCornerHole(hole)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    @Override
    public boolean isBehindFinishLine(final Hole hole, final Team team) {
        switch (team) {
        case RED:
            return ((hole.getXCoord() == 0
                    || hole.getXCoord() == getMaxXSize() - 1)
                    && isCornerHole(hole) == false);
        case BLACK:
            return ((hole.getYCoord() == 0
                    || hole.getYCoord() == getMaxYSize() - 1)
                    && isCornerHole(hole) == false);
        default:
            return false;
        }
    }
    
    @Override
    public boolean isValidForTeam(final Hole hole, final Team team) {
        return (isInsideBoard(hole)
                && !isBehindFinishLine(hole, team.getOpponent()));
    }
    
    protected boolean isCornerHole(final Hole hole) {
        final int x = hole.getXCoord();
        final int y = hole.getYCoord();
        return ((x == 0 || x == getMaxXSize() - 1)
                && (y == 0 || y == getMaxYSize() - 1));
    }
}
