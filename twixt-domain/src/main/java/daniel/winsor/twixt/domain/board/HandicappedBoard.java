package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;

/**
 * Can only handicap regular square boards.
 * Delegates to the wrapped board, except for MaxSize calls.
 * For MaxSize calls, will make the call once when HandicappedBoard
 * is created, ADD a handicap, and store result for later.
 * @author Daniel
 *
 */
public class HandicappedBoard implements IBoardFormat {
    protected IBoardFormat boardToHandicap;
    protected int handicappedXSize;
    protected int handicappedYSize;
    
    public HandicappedBoard(final IBoardFormat boardToHandicap,
            final int xHandicap, final int yHandicap) {
        setBoardToHandicap(boardToHandicap);
        if (getBoard().getBoardType().isRegularSquare()) {
            setHandicappedXSize(boardToHandicap.getMaxXSize() + xHandicap);
            setHandicappedYSize(boardToHandicap.getMaxYSize() + yHandicap);
        }
        else {
            //TODO logger warning
        }
    }
    
    protected void setBoardToHandicap(final IBoardFormat boardToHandicap) {
        this.boardToHandicap = boardToHandicap;
    }
    
    protected void setHandicappedXSize(final int handicappedXSize) {
        this.handicappedXSize = handicappedXSize;
    }
    
    protected void setHandicappedYSize(final int handicappedYSize) {
        this.handicappedYSize = handicappedYSize;
    }
    
    protected IBoardFormat getBoard() {
        return boardToHandicap;
    }
    
    @Override
    public int getMaxXSize() {
        return handicappedXSize;
    }
    
    @Override
    public int getMaxYSize() {
        return handicappedYSize;
    }
    
    @Override
    public BoardType getBoardType() {
        return getBoard().getBoardType();
    }
    
    @Override
    public boolean isInsideBoard(final Hole hole) {
        return getBoard().isInsideBoard(hole);
    }
    
    @Override
    public boolean isBehindFinishLine(final Hole hole, final Team team) {
        return getBoard().isBehindFinishLine(hole, team);
    }
    
    @Override
    public boolean isValidForTeam(final Hole hole, final Team team) {
        return getBoard().isValidForTeam(hole, team);
    }
}
