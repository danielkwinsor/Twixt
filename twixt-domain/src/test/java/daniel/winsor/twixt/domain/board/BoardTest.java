package daniel.winsor.twixt.domain.board;

import static daniel.winsor.twixt.domain.board.BoardType.*;

import org.junit.Assert;
import org.junit.Test;

import daniel.winsor.twixt.domain.*;

public class BoardTest {
    @Test
    public void testIsInsideBoard() {
        IBoardFormat board = new SquareBoard(STANDARD_24);
        Assert.assertTrue(board.isInsideBoard(new Hole(1, 1)));
        Assert.assertFalse(board.isInsideBoard(new Hole(0, 0)));
        Assert.assertTrue(board.isInsideBoard(new Hole(0, 1)));
        Assert.assertTrue(board.isInsideBoard(new Hole(1, 0)));
        
        Assert.assertFalse(board.isInsideBoard(Hole.nullHole));
        Assert.assertFalse(board.isInsideBoard(new Hole(23, 23)));
        Assert.assertTrue(board.isInsideBoard(new Hole(23, 22)));
        
        board = new SquareBoard(SMALL_12);
        Assert.assertFalse(board.isInsideBoard(new Hole(23, 22)));
        Assert.assertFalse(board.isInsideBoard(new Hole(12, 12)));
        
        board = new SquareBoard(HUGE_36);
        Assert.assertTrue(board.isInsideBoard(new Hole(23, 22)));
        Assert.assertTrue(board.isInsideBoard(new Hole(12, 12)));
        Assert.assertFalse(board.isInsideBoard(new Hole(35, 35)));
        Assert.assertFalse(board.isInsideBoard(new Hole(35, 0)));
        Assert.assertFalse(board.isInsideBoard(new Hole(0, 35)));
        Assert.assertTrue(board.isInsideBoard(new Hole(34, 0)));
        Assert.assertTrue(board.isInsideBoard(new Hole(0, 34)));
    }
    
    @Test
    public void testIsBehindFinishLine() {
        IBoardFormat board = new SquareBoard(STANDARD_24);
        Assert.assertFalse(board.isBehindFinishLine(new Hole(1, 1),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(0, 0),
                Team.RED));
        
        Assert.assertTrue(board.isBehindFinishLine(new Hole(0, 1),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(1, 0),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(0, 1),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole(1, 0),
                Team.BLACK));
    }
    
    @Test
    public void testIsValidForTeam() {
        IBoardFormat board = new SquareBoard(STANDARD_24);
        Assert.assertTrue(board.isValidForTeam(new Hole(1, 1),
                Team.RED));
        Assert.assertTrue(board.isValidForTeam(new Hole(1, 1),
                Team.BLACK));
        Assert.assertFalse(board.isValidForTeam(new Hole(0, 0),
                Team.RED));
        Assert.assertFalse(board.isValidForTeam(new Hole(0, 0),
                Team.BLACK));
        
        Assert.assertTrue(board.isValidForTeam(new Hole(0, 1),
                Team.RED));
        Assert.assertFalse(board.isValidForTeam(new Hole(1, 0),
                Team.RED));
        Assert.assertFalse(board.isValidForTeam(new Hole(0, 1),
                Team.BLACK));
        Assert.assertTrue(board.isValidForTeam(new Hole(1, 0),
                Team.BLACK));
    }
}
