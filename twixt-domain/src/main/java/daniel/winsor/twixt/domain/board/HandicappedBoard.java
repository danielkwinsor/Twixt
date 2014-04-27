package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;

public class HandicappedBoard implements IBoardFormat {
    protected IBoardFormat boardToHandicap;
    protected int handicappedXSize;
    protected int handicappedYSize;
    
    protected void setBoardToHandicap(IBoardFormat boardToHandicap) {
        this.boardToHandicap = boardToHandicap;
    }

    protected void setHandicappedXSize(int handicappedXSize) {
        this.handicappedXSize = handicappedXSize;
    }

    protected void setHandicappedYSize(int handicappedYSize) {
        this.handicappedYSize = handicappedYSize;
    }

    public HandicappedBoard(final IBoardFormat boardToHandicap,
            final int xHandicap, final int yHandicap) {
        setBoardToHandicap(boardToHandicap);
        setHandicappedXSize(boardToHandicap.getMaxXSize() + xHandicap);
        setHandicappedYSize(boardToHandicap.getMaxYSize() + yHandicap);
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
