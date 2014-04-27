package daniel.winsor.twixt.domain.board;

import static daniel.winsor.twixt.domain.board.BoardType.STANDARD_24;

public class StandardBoard extends AbstractBoard implements IBoardFormat {
    @Override
    public int getMaxXSize() {
        return 24;
    }

    @Override
    public int getMaxYSize() {
        return 24;
    }

    @Override
    public BoardType getBoardType() {
        return STANDARD_24;
    }
}
