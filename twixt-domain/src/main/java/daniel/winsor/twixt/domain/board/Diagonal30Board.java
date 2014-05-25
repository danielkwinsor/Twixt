package daniel.winsor.twixt.domain.board;

import java.util.*;

import daniel.winsor.twixt.domain.*;

/**
 * Should not be handicapped
 * @author Daniel
 *
 */
public class Diagonal30Board extends DiagonalBoard implements IBoard {
    public Diagonal30Board() {
        super(BoardType.DIAGONAL_30_DEGREES);
    }
    
    @Override
    protected Map<Team, Set<Hole>> createFinishLineHoles() {
        Map<Team, Set<Hole>> teamFinishLines =
                new HashMap<Team, Set<Hole>>();
        
        teamFinishLines.put(Team.BLACK, getLeftRightFinishLine());
        teamFinishLines.put(Team.RED, getUpDownFinishLine());
        
        return teamFinishLines;
    }
    
    private Set<Hole> getLeftRightFinishLine() {
        Set<Hole> finishLineHoles = new HashSet<Hole>();
        for (int yCoord = 0; yCoord < getMaxYSize(); ++yCoord) {
            if (yCoord >= 8 && yCoord < 11) {
                finishLineHoles.add(new Hole('A', yCoord));
            }
            if (yCoord >= 9 && yCoord < 13) {
                finishLineHoles.add(new Hole('B', yCoord));
            }
            if (yCoord >= 11 && yCoord < 15) {
                finishLineHoles.add(new Hole('C', yCoord));
            }
            if (yCoord >= 13 && yCoord < 17) {
                finishLineHoles.add(new Hole('D', yCoord));
            }
            if (yCoord >= 15 && yCoord < 19) {
                finishLineHoles.add(new Hole('E', yCoord));
            }
            if (yCoord >= 17 && yCoord < 21) {
                finishLineHoles.add(new Hole('F', yCoord));
            }
            if (yCoord >= 19 && yCoord < 23) {
                finishLineHoles.add(new Hole('G', yCoord));
            }
            if (yCoord >= 21) {
                finishLineHoles.add(new Hole('H', yCoord));
            }
            if (yCoord < 2) {
                finishLineHoles.add(new Hole('Q', yCoord));
            }
            if (yCoord >= 1 && yCoord < 4) {
                finishLineHoles.add(new Hole('R', yCoord));
            }
            if (yCoord >= 3 && yCoord < 6) {
                finishLineHoles.add(new Hole('S', yCoord));
            }
            if (yCoord >= 5 && yCoord < 8) {
                finishLineHoles.add(new Hole('T', yCoord));
            }
            if (yCoord >= 7 && yCoord < 10) {
                finishLineHoles.add(new Hole('U', yCoord));
            }
            if (yCoord >= 9 && yCoord < 12) {
                finishLineHoles.add(new Hole('V', yCoord));
            }
            if (yCoord >= 11 && yCoord < 14) {
                finishLineHoles.add(new Hole('W', yCoord));
            }
            if (yCoord >= 13 && yCoord < 15) {
                finishLineHoles.add(new Hole('X', yCoord));
            }
        }
        return finishLineHoles;
    }

    private Set<Hole> getUpDownFinishLine() {
        Set<Hole> finishLineHoles = new HashSet<Hole>();
        for (Hole hole : getLeftRightFinishLine()) {
            //the coords are just rotated
            finishLineHoles.add(
                    new Hole(23 - hole.getYCoord(), hole.getXCoord()));
        }
        return finishLineHoles;
    }

    @Override
    protected Set<Hole> createCornerHoles() {
        Set<Hole> cornerHoles = new HashSet<Hole>();
        for (int yCoord = 0; yCoord < getMaxYSize(); ++yCoord) {
            if (yCoord < 7 || yCoord >= 11) {
                cornerHoles.add(new Hole('A', yCoord));
            }
            if (yCoord < 6 || yCoord >= 13) {
                cornerHoles.add(new Hole('B', yCoord));
            }
            if (yCoord < 6 || yCoord >= 15) {
                cornerHoles.add(new Hole('C', yCoord));
            }
            if (yCoord < 5 || yCoord >= 17) {
                cornerHoles.add(new Hole('D', yCoord));
            }
            if (yCoord < 5 || yCoord >= 19) {
                cornerHoles.add(new Hole('E', yCoord));
            }
            if (yCoord < 4 || yCoord >= 21) {
                cornerHoles.add(new Hole('F', yCoord));
            }
            if (yCoord < 4 || yCoord >= 23) {
                cornerHoles.add(new Hole('G', yCoord));
            }
            if (yCoord < 3) {
                cornerHoles.add(new Hole('H', yCoord));
            }
            if (yCoord < 3) {
                cornerHoles.add(new Hole('I', yCoord));
            }
            if (yCoord < 2) {
                cornerHoles.add(new Hole('J', yCoord));
            }
            if (yCoord < 2) {
                cornerHoles.add(new Hole('K', yCoord));
            }
            if (yCoord < 1 || yCoord >= 23) {
                cornerHoles.add(new Hole('L', yCoord));
            }
            if (yCoord < 1 || yCoord >= 23) {
                cornerHoles.add(new Hole('M', yCoord));
            }
            if (yCoord >= 22) {
                cornerHoles.add(new Hole('N', yCoord));
            }
            if (yCoord >= 22) {
                cornerHoles.add(new Hole('O', yCoord));
            }
            if (yCoord >= 21) {
                cornerHoles.add(new Hole('P', yCoord));
            }
            if (yCoord >= 21) {
                cornerHoles.add(new Hole('Q', yCoord));
            }
            if (yCoord < 1 || yCoord >= 20) {
                cornerHoles.add(new Hole('R', yCoord));
            }
            if (yCoord < 3 || yCoord >= 20) {
                cornerHoles.add(new Hole('S', yCoord));
            }
            if (yCoord < 5 || yCoord >= 19) {
                cornerHoles.add(new Hole('T', yCoord));
            }
            if (yCoord < 7 || yCoord >= 19) {
                cornerHoles.add(new Hole('U', yCoord));
            }
            if (yCoord < 9 || yCoord >= 18) {
                cornerHoles.add(new Hole('V', yCoord));
            }
            if (yCoord < 11 || yCoord >= 18) {
                cornerHoles.add(new Hole('W', yCoord));
            }
            if (yCoord < 13 || yCoord >= 17) {
                cornerHoles.add(new Hole('X', yCoord));
            }
        }
        return cornerHoles;
    }
}
