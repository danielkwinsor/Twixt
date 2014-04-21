package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;


public interface IBoardFormat {
    public abstract BoardType getBoardType();
    
    public abstract int getMaxXSize();
    
    public abstract int getMaxYSize();
    
    public abstract boolean isInsideBoard(Hole hole);
    
    public abstract boolean isBehindFinishLine(Hole hole, Team team);
}