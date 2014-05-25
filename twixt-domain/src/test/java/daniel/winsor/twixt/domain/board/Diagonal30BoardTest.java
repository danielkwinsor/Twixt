package daniel.winsor.twixt.domain.board;

import org.junit.Assert;
import org.junit.Test;

import daniel.winsor.twixt.domain.*;

public class Diagonal30BoardTest {
    @Test
    public void testIsInsideBoard() {
        IBoardFormat board = new Diagonal30Board();
        Assert.assertFalse(board.isInsideBoard(new Hole(1, 1)));
        Assert.assertFalse(board.isInsideBoard(new Hole(0, 0)));
        Assert.assertFalse(board.isInsideBoard(new Hole(0, 1)));
        Assert.assertFalse(board.isInsideBoard(new Hole(1, 0)));
        
        Assert.assertFalse(board.isInsideBoard(Hole.nullHole));
        Assert.assertFalse(board.isInsideBoard(new Hole(23, 23)));
        Assert.assertFalse(board.isInsideBoard(new Hole(23, 22)));
        Assert.assertFalse(board.isInsideBoard(new Hole(22, 23)));
        
        Assert.assertFalse(board.isInsideBoard(new Hole("A7")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A8")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A11")));
        Assert.assertFalse(board.isInsideBoard(new Hole("A12")));
        
        Assert.assertFalse(board.isInsideBoard(new Hole("X13")));
        Assert.assertTrue(board.isInsideBoard(new Hole("X14")));
        Assert.assertTrue(board.isInsideBoard(new Hole("X17")));
        Assert.assertFalse(board.isInsideBoard(new Hole("X18")));
        
        Assert.assertFalse(board.isInsideBoard(new Hole("G4")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G5")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G23")));
        Assert.assertFalse(board.isInsideBoard(new Hole("G24")));

        Assert.assertFalse(board.isInsideBoard(new Hole("M1")));
        Assert.assertTrue(board.isInsideBoard(new Hole("M2")));
        Assert.assertTrue(board.isInsideBoard(new Hole("M23")));
        Assert.assertFalse(board.isInsideBoard(new Hole("M24")));
    }
    
    @Test
    public void testIsBehindFinishLine() {
        IBoardFormat board = new Diagonal30Board();
        Assert.assertFalse(board.isBehindFinishLine(new Hole(1, 1),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(0, 0),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(1, 0),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A7"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A8"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A9"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A10"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A11"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A12"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A7"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A8"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A9"),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("B6"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("B7"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("B8"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("B9"),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("B9"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("B10"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("B11"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("B12"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("B13"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("B14"),
                Team.BLACK));

        Assert.assertFalse(board.isBehindFinishLine(new Hole("M1"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("M2"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("M3"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("M4"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("M21"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("M22"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("M23"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("M24"),
                Team.RED));

        Assert.assertFalse(board.isBehindFinishLine(new Hole("G4"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G5"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G6"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G7"),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G19"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G20"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G23"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G24"),
                Team.BLACK));
    }
}
