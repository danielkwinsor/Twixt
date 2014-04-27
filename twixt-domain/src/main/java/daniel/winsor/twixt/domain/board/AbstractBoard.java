package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;

public abstract class AbstractBoard implements IBoardFormat {
    
    /**
     * TODO optimize by converting to hashCode?
     */
    @Override
    public boolean isInsideBoard(final Hole hole) {
        int x = hole.getXCoord();
        int y = hole.getYCoord();
        if (x >= 0 && x < getMaxXSize()) {
            if (y >= 0 && y < getMaxYSize()) {
                if ((x == 0 && y == 0)
                        || (x == 0 && y == getMaxYSize()-1)
                        || (x == getMaxXSize()-1 && y == 0)
                        || (x == getMaxXSize()-1 && y == getMaxYSize()-1)) {
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
                    || hole.getXCoord() == getMaxXSize()-1);
        case UP_DOWN:
            return (hole.getYCoord() == 0
                    || hole.getYCoord() == getMaxYSize()-1);
        default:
            return false;
        }
    }
    
    @Override
    public boolean isValidForTeam(final Hole hole, final Team team) {
        return (isInsideBoard(hole)
                && !isBehindFinishLine(hole, team.getOpponent()));
    }
}
