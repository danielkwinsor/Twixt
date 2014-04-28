package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.Direction.*;

import org.junit.Assert;
import org.junit.Test;

public class HoleTest {
    @Test
    public void testEquality() {
        Assert.assertFalse(new Hole(0, 0).equals(null));
        Assert.assertFalse(new Hole(0, 0).equals(new Object()));
        
        Assert.assertEquals(new Hole(0, 0), new Hole(0, 0));
        Assert.assertEquals(new Hole(25, 25), new Hole(25, 25));
        Assert.assertEquals(new Hole(-1, 0), new Hole(-1, 0));
        
        Assert.assertNotEquals(new Hole(0, 0), new Hole(-1, 0));
        Assert.assertNotEquals(new Hole(0, 0), new Hole(0, 1));
        Assert.assertNotEquals(new Hole(1, 1), new Hole(0, 1));
    }
    
    @Test
    public void testHoleFromChar() {
        Assert.assertEquals(new Hole(0, 0), new Hole('A', 0));
        Assert.assertEquals(new Hole(0, 1), new Hole('a', 1));
        Assert.assertNotEquals(new Hole(0, 0), new Hole('0', 0));
        Assert.assertEquals(Hole.nullHole, new Hole('z', 0));
    }
    
    @Test
    public void testHoleFromString() {
        Assert.assertEquals(new Hole(0, 0), new Hole("A1"));
        Assert.assertEquals(new Hole(0, 9), new Hole("a10"));
        Assert.assertEquals(new Hole(23, 23), new Hole("X24"));
        Assert.assertEquals(new Hole(23, 1233), new Hole("X1234"));
        Assert.assertEquals(Hole.nullHole, new Hole("Z1"));
        Assert.assertEquals(Hole.nullHole, new Hole("AA"));
        Assert.assertEquals(Hole.nullHole, new Hole("1A"));
        Assert.assertEquals(Hole.nullHole, new Hole(""));
    }
    
    /**
     * The board is arranged with 0,0 at bottom left
     */
    @Test
    public void testHoleFromDirection() {
        Assert.assertEquals(new Hole(0, 1), new Hole(2, 2).getHoleFromDir(LEFT_UP));
        Assert.assertEquals(new Hole(1, 0), new Hole(2, 2).getHoleFromDir(UP_LEFT));
        Assert.assertEquals(new Hole(3, 0), new Hole(2, 2).getHoleFromDir(UP_RIGHT));
        Assert.assertEquals(new Hole(4, 1), new Hole(2, 2).getHoleFromDir(RIGHT_UP));
        Assert.assertEquals(new Hole(4, 3), new Hole(2, 2).getHoleFromDir(RIGHT_DOWN));
        Assert.assertEquals(new Hole(3, 4), new Hole(2, 2).getHoleFromDir(DOWN_RIGHT));
        Assert.assertEquals(new Hole(1, 4), new Hole(2, 2).getHoleFromDir(DOWN_LEFT));
        Assert.assertEquals(new Hole(0, 3), new Hole(2, 2).getHoleFromDir(LEFT_DOWN));
    }
}
