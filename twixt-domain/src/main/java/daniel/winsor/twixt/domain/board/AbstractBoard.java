package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;

/**
 * Does most of the work of handling logic common to all boards.
 * @author Daniel
 *
 */
public abstract class AbstractBoard implements IBoardFormat {
    protected final BoardType boardType;

    public AbstractBoard(BoardType boardType) {
        this.boardType = boardType;
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
                if (isCornerHole(hole)) {
                    return false;
                }
                return true;
            }
        }
        return false;
    }
    
    @Override
    public boolean isBehindFinishLine(final Hole hole, final Team team) {
        switch (team) {
        case LEFT_RIGHT:
            return (hole.getXCoord() == 0
                    || hole.getXCoord() == getMaxXSize() - 1);
        case UP_DOWN:
            return (hole.getYCoord() == 0
                    || hole.getYCoord() == getMaxYSize() - 1);
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
