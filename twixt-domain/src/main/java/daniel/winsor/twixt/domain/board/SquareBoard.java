package daniel.winsor.twixt.domain.board;

/**
 * Exact copy of AbstractBoard, with a check on the constructor
 * parameter.
 * @author Daniel
 *
 */
public class SquareBoard extends AbstractBoard implements IBoard {
    public SquareBoard(BoardType boardType) {
        super(boardType);
        if (!boardType.isRegularSquare()) {
            throw new IllegalArgumentException();
        }
    }
}
