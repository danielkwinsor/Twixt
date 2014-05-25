package daniel.winsor.twixt.domain.board;

import java.util.*;

import daniel.winsor.twixt.domain.*;

/**
 * Should not be handicapped
 * @author Daniel
 *
 */
public abstract class DiagonalBoard extends AbstractBoard
        implements IBoard {
    protected final Map<Team, Set<Hole>> finishLineHoles;
    protected final Set<Hole> cornerHoles;
    
    public DiagonalBoard(BoardType boardType) {
        super(boardType);
        if (boardType.isDiagonal() == false) {
            throw new IllegalArgumentException(
                    "Must be a diagonal board type");
        }
        
        finishLineHoles = createFinishLineHoles();
        cornerHoles = createCornerHoles();
        if (finishLineHoles == null || cornerHoles == null) {
            throw new IllegalArgumentException(
                    "the list of holes cannot be null");
        }
    }
    
    protected Map<Team, Set<Hole>> getFinishLineHoles() {
        return finishLineHoles;
    }

    protected Set<Hole> getCornerHoles() {
        return cornerHoles;
    }

    /**
     * This need not be mutable
     * @return
     */
    protected abstract Map<Team, Set<Hole>> createFinishLineHoles();
    
    /**
     * This need not be mutable
     * @return
     */
    protected abstract Set<Hole> createCornerHoles();
    
    /**
     * Check all the holes that are outside the playing area.
     */
    @Override
    protected boolean isCornerHole(final Hole hole) {
        return getCornerHoles().contains(hole);
    }
    
    /**
     * Check all the holes that are behind the finish line.
     */
    @Override
    public boolean isBehindFinishLine(final Hole hole, final Team team) {
        Set<Hole> teamHoles = getFinishLineHoles().get(team);
        if (teamHoles == null) {
            return false;
        }
        return teamHoles.contains(hole);
    }
}
