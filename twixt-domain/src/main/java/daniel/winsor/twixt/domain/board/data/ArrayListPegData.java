package daniel.winsor.twixt.domain.board.data;

import java.util.*;

import daniel.winsor.twixt.domain.*;
import daniel.winsor.twixt.domain.board.*;

/**
 * The data for the board is stored in an ArrayList
 * @author Daniel
 *
 */
public class ArrayListPegData {
    protected final BoardType boardType;
    protected final List<Peg> pegs;

    public ArrayListPegData(BoardType boardType) {
        this.boardType = boardType;
        pegs = new ArrayList<Peg>(
                boardType.getDefaultSize() * boardType.getDefaultSize());
        for (int x = 0; x < boardType.getDefaultSize(); ++x) {
            for (int y = 0; y < boardType.getDefaultSize(); ++y) {
                pegs.add(new Peg(new Hole(x, y), Team.UNOWNED));
            }
        }
    }
    
    public Peg getPeg(final Hole hole) {
        try {
            return pegs.get(hole.getXCoord() * boardType.getDefaultSize()
                    + hole.getYCoord());
        }
        catch (IndexOutOfBoundsException e) {
            return Peg.nullPeg;
        }
    }
}
