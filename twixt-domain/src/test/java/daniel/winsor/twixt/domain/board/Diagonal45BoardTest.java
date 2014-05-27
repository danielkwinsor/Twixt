package daniel.winsor.twixt.domain.board;

import org.junit.Assert;
import org.junit.Test;

import daniel.winsor.twixt.domain.*;

public class Diagonal45BoardTest {
    @Test
    public void testIsInsideBoard() {
        IBoardFormat board = new Diagonal45Board();
        Assert.assertFalse(board.isInsideBoard(new Hole(1, 1)));
        Assert.assertFalse(board.isInsideBoard(new Hole(0, 0)));
        Assert.assertFalse(board.isInsideBoard(new Hole(0, 1)));
        Assert.assertFalse(board.isInsideBoard(new Hole(1, 0)));
        
        Assert.assertFalse(board.isInsideBoard(Hole.nullHole));
        Assert.assertFalse(board.isInsideBoard(new Hole(23, 23)));
        Assert.assertFalse(board.isInsideBoard(new Hole(23, 22)));
        Assert.assertFalse(board.isInsideBoard(new Hole(22, 23)));
        
        Assert.assertFalse(board.isInsideBoard(new Hole("A9")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A10")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A11")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A12")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A13")));
        Assert.assertTrue(board.isInsideBoard(new Hole("A14")));
        Assert.assertFalse(board.isInsideBoard(new Hole("A15")));
        
        //there are no 24s
        Assert.assertFalse(board.isInsideBoard(new Hole("A24")));
        
        //there are no Xs
        Assert.assertFalse(board.isInsideBoard(new Hole("X13")));
        Assert.assertFalse(board.isInsideBoard(new Hole("X14")));
        Assert.assertFalse(board.isInsideBoard(new Hole("X17")));
        Assert.assertFalse(board.isInsideBoard(new Hole("X18")));
        
        Assert.assertFalse(board.isInsideBoard(new Hole("G3")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G4")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G5")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G6")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G18")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G19")));
        Assert.assertTrue(board.isInsideBoard(new Hole("G20")));
        Assert.assertFalse(board.isInsideBoard(new Hole("G21")));
    }
    
    @Test
    public void testIsBehindFinishLine() {
        IBoardFormat board = new Diagonal45Board();
        Assert.assertFalse(board.isBehindFinishLine(Hole.nullHole,
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(Hole.nullHole,
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(1, 1),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(0, 0),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole(1, 0),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A9"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A10"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A11"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A12"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A13"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A14"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A15"),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G3"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G4"),
                Team.RED));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G5"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G6"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G18"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G19"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G20"),
                Team.RED));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G21"),
                Team.RED));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A9"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A10"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A11"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A12"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A13"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("A14"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("A15"),
                Team.BLACK));
        
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G3"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G4"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G5"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G6"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G18"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G19"),
                Team.BLACK));
        Assert.assertTrue(board.isBehindFinishLine(new Hole("G20"),
                Team.BLACK));
        Assert.assertFalse(board.isBehindFinishLine(new Hole("G21"),
                Team.BLACK));
    }
}
