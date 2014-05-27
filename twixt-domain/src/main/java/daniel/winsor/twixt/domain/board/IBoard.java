package daniel.winsor.twixt.domain.board;

import daniel.winsor.twixt.domain.*;

/**
 * An interface to the actual board and its data.
 * TODO eg getPegAt(), copyBoard(), setPeg() etc.
 * TODO determine if includes isLinked, isBlocked, setLinked, setBlocked.
 * Does NOT include logic like willPegBlockLink,
 * canPegLink, etc - this goes in logic module.
 * @author Daniel
 *
 */
public interface IBoard extends IBoardFormat {
    Peg getPeg(final Hole hole);
    //IBoard copyBoard();
    //void doFirstTurnSwap();
}
