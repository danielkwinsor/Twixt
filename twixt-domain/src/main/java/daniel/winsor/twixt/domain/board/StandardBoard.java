package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.Hole;
import daniel.winsor.twixt.domain.Team;

public class StandardBoard implements IBoardFormat {
    @Override
    public int getMaxXSize() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public int getMaxYSize() {
        // TODO Auto-generated method stub
        return 0;
    }

    @Override
    public boolean isInsideBoard(Hole hole) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean isBehindFinishLine(Hole hole, Team team) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public BoardType getBoardType() {
        // TODO Auto-generated method stub
        return null;
    }
}
