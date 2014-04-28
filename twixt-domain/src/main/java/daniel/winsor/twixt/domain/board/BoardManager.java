package daniel.winsor.twixt.domain.board;

/**
 * TODO
 * @author Daniel
 *
 */
public class BoardManager {
    private static IBoardFormat board = new SquareBoard(BoardType.STANDARD_24);
    
    public static IBoardFormat getCurrentBoard() {
        return board;
    }
    
    public static IBoardFormat getCopyOfCurrentBoard() {
        return board;
    }
}
