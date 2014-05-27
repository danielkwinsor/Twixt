package daniel.winsor.twixt.domain.board;

import org.junit.Assert;
import org.junit.Test;

import daniel.winsor.twixt.domain.*;

public class BoardTypeTest {
    @Test
    public void testRotate() {
        BoardType type = BoardType.STANDARD_24;
        Assert.assertEquals(new Hole("X1"),
                type.rotateClockwiseAboutBoard(new Hole("A1")));
        Assert.assertEquals(new Hole("X24"),
                type.rotateClockwiseAboutBoard(new Hole("X1")));
        Assert.assertEquals(new Hole("A24"),
                type.rotateClockwiseAboutBoard(new Hole("X24")));
        Assert.assertEquals(new Hole("A1"),
                type.rotateClockwiseAboutBoard(new Hole("A24")));
        
        type = BoardType.DIAGONAL_45_DEGREES;
        Assert.assertEquals(new Hole("W1"),
                type.rotateClockwiseAboutBoard(new Hole("A1")));
        Assert.assertEquals(new Hole("W23"),
                type.rotateClockwiseAboutBoard(new Hole("W1")));
        Assert.assertEquals(new Hole("A23"),
                type.rotateClockwiseAboutBoard(new Hole("W23")));
        Assert.assertEquals(new Hole("A1"),
                type.rotateClockwiseAboutBoard(new Hole("A23")));
        
        Assert.assertEquals(new Hole("V10"),
                type.rotateClockwiseAboutBoard(new Hole("J2")));
        Assert.assertEquals(new Hole("N22"),
                type.rotateClockwiseAboutBoard(new Hole("V10")));
        Assert.assertEquals(new Hole("B14"),
                type.rotateClockwiseAboutBoard(new Hole("N22")));
        Assert.assertEquals(new Hole("J2"),
                type.rotateClockwiseAboutBoard(new Hole("B14")));
    }
}
