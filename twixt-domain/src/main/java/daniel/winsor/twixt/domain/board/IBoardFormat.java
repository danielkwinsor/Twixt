package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;


public interface IBoardFormat {
    public abstract BoardType getBoardType();
    
    public abstract int getMaxXSize();
    
    public abstract int getMaxYSize();
    
    public abstract boolean isInsideBoard(final Hole hole);
    
    public abstract boolean isBehindFinishLine(final Hole hole, final Team team);
    
    public abstract boolean isValidForTeam(final Hole hole, final Team team);
}