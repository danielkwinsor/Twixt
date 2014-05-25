package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.*;

/**
 * Can only handicap regular square boards.
 * Delegates to the wrapped board, except for MaxSize calls.
 * For MaxSize calls, will make the call once when HandicappedBoard
 * is created, SUBTRACT a handicap, and store result for later.
 * @author Daniel
 *
 */
public class HandicappedBoard implements IBoard {
    protected IBoard boardToHandicap;
    protected int handicappedXSize;
    protected int handicappedYSize;
    
    public HandicappedBoard(final IBoard boardToHandicap,
            final int xHandicap, final int yHandicap) {
        setBoardToHandicap(boardToHandicap);
        
        //if we fail the checks below, then the handicapped board
        //is still usable as a regular board that just
        //delegates all calls.  Therefore, return instead of throw
        
        if (!getBoard().getBoardType().isRegularSquare()) {
            //TODO logger warning
            return;
        }
        if (xHandicap < 0 || boardToHandicap.getMaxXSize() >= xHandicap
                || yHandicap < 0 || boardToHandicap.getMaxYSize() >= yHandicap) {
            //TODO logger warning
            return;
        }
        
        setHandicappedXSize(boardToHandicap.getMaxXSize() - xHandicap);
        setHandicappedYSize(boardToHandicap.getMaxYSize() - yHandicap);
    }
    
    protected void setBoardToHandicap(final IBoard boardToHandicap) {
        this.boardToHandicap = boardToHandicap;
    }
    
    protected void setHandicappedXSize(final int handicappedXSize) {
        this.handicappedXSize = handicappedXSize;
    }
    
    protected void setHandicappedYSize(final int handicappedYSize) {
        this.handicappedYSize = handicappedYSize;
    }
    
    protected IBoard getBoard() {
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

    @Override
    public Peg getPeg(Hole hole) {
        return getBoard().getPeg(hole);
    }
}
