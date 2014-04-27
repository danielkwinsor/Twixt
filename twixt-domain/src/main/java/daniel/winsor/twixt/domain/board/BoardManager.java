package daniel.winsor.twixt.domain.board;

/**
 * TODO
 * @author Daniel
 *
 */
public class BoardManager {
    public static IBoardFormat board = new StandardBoard();
    
    public static IBoardFormat getCurrentBoard() {
        return board;
    }
    
    public static IBoardFormat getCopyOfCurrentBoard() {
        return board;
    }
}
