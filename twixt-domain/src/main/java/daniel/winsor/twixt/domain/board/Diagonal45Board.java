package daniel.winsor.twixt.domain.board;

import java.util.*;

import daniel.winsor.twixt.domain.*;

/**
 * Should not be handicapped
 * @author Daniel
 *
 */
public class Diagonal45Board extends DiagonalBoard implements IBoard {
    public Diagonal45Board() {
        super(BoardType.DIAGONAL_45_DEGREES);
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
        for (int xCoord = 0; xCoord < getMaxXSize(); ++xCoord) {
            if (xCoord + 12 < getMaxXSize()) {
                finishLineHoles.add(
                        new Hole(xCoord, xCoord + 12));
            }
            if (xCoord + 13 < getMaxXSize()) {
                finishLineHoles.add(
                        new Hole(xCoord, xCoord + 13));
            }
            if (xCoord - 12 >= 0) {
                finishLineHoles.add(
                        new Hole(xCoord, xCoord - 12));
            }
            if (xCoord - 13 >= 0) {
                finishLineHoles.add(
                        new Hole(xCoord, xCoord - 13));
            }
        }
        return finishLineHoles;
    }

    private Set<Hole> getUpDownFinishLine() {
        Set<Hole> finishLineHoles = new HashSet<Hole>();
        for (Hole hole : getLeftRightFinishLine()) {
            //the coords are just rotated, but remember
            //that the board is size 23
            finishLineHoles.add(
                    getBoardType().rotateClockwiseAboutBoard(hole));
        }
        return finishLineHoles;
    }

    @Override
    protected Set<Hole> createCornerHoles() {
        Set<Hole> cornerHoles = new HashSet<Hole>();
        for (int xCoord = 0; xCoord < getMaxXSize(); ++xCoord) {
            for (int yCoord = 0; yCoord < getMaxYSize(); ++yCoord) {
                //"O1" = 14,0; upper right
                //"P2" = 15,1; "P1" = 15,0
                if (xCoord - 14 >= yCoord) {
                    cornerHoles.add(new Hole(xCoord, yCoord));
                }
                //"I23" = 8,22; lower left
                //"A15" = 0,14
                //"F20" = 5,19
                //"F21" = 5,20
                if (xCoord + 14 <= yCoord && yCoord >= 14) {
                    cornerHoles.add(new Hole(xCoord, yCoord));
                }
                
                //the coords are just rotated, but remember
                //that the board is size 23
                if (xCoord - 14 >= yCoord) {
                    cornerHoles.add(
                            getBoardType().rotateClockwiseAboutBoard(
                                    new Hole(xCoord, yCoord)));
                }
                if (xCoord + 14 <= yCoord && yCoord >= 14) {
                    cornerHoles.add(
                            getBoardType().rotateClockwiseAboutBoard(
                                    new Hole(xCoord, yCoord)));
                }
            }
        }
        return cornerHoles;
    }
}
