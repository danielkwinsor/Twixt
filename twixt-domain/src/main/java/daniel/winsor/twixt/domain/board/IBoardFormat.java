package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;

/**
 * Boards
 * @author Daniel
 *
 */
public interface IBoardFormat {
    BoardType getBoardType();
    
    int getMaxXSize();
    
    int getMaxYSize();
    
    boolean isInsideBoard(final Hole hole);
    
    boolean isBehindFinishLine(final Hole hole, final Team team);
    
    boolean isValidForTeam(final Hole hole, final Team team);
}