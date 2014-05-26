package daniel.winsor.twixt.domain.board.data;

import daniel.winsor.twixt.domain.*;
import daniel.winsor.twixt.domain.board.*;

/**
 * The data for the board is stored in a 2d array
 * @author Daniel
 *
 */
public class ArrayPegData {
    protected final BoardType boardType;
    protected final Peg[][] pegs;

    public ArrayPegData(BoardType boardType) {
        this.boardType = boardType;
        pegs = new Peg[boardType.getDefaultSize()]
                [boardType.getDefaultSize()];
        for (int x = 0; x < boardType.getDefaultSize(); ++x) {
            for (int y = 0; y < boardType.getDefaultSize(); ++y) {
                pegs[x][y] = new Peg(new Hole(x, y), Team.UNOWNED);
            }
        }
    }
    
    public Peg getPeg(final Hole hole) {
        try {
            return pegs[hole.getXCoord()][hole.getYCoord()];
        }
        catch (IndexOutOfBoundsException e) {
            return Peg.nullPeg;
        }
    }
}
