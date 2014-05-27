package daniel.winsor.twixt.domain;

import org.junit.Assert;
import org.junit.Test;

public class PegTest {
    @Test
    public void testEquality() {
        Peg immutablePeg = new ImmutablePeg(new Hole(0, 0), Team.UNOWNED);
        
        Assert.assertTrue(immutablePeg instanceof ImmutablePeg);
        Assert.assertNotEquals(Peg.nullPeg, immutablePeg);
        Assert.assertNotEquals(immutablePeg, Peg.nullPeg);
        
        Peg peg = new Peg(new Hole(0, 0), Team.UNOWNED);
        Assert.assertEquals(immutablePeg, peg);
        Assert.assertEquals(peg, immutablePeg);
    }
    
    @Test
    public void testCopyCtor() {
        Peg peg = new Peg(new Hole(1, 1), Team.RED);
        peg.addBlock(Direction.DOWN_LEFT);
        peg.addLink(Direction.UP_LEFT);
        Peg copiedPeg = new Peg(peg);
        Assert.assertEquals(copiedPeg, peg);
        Assert.assertEquals(peg, copiedPeg);
        
        Assert.assertEquals(Team.RED, copiedPeg.getOwner());
        Assert.assertEquals(new Hole(1, 1), copiedPeg.getHole());
        Assert.assertTrue(copiedPeg.isBlocked(Direction.DOWN_LEFT));
        Assert.assertFalse(copiedPeg.isBlocked(Direction.UP_LEFT));
        Assert.assertTrue(copiedPeg.isLinked(Direction.UP_LEFT));
        Assert.assertFalse(copiedPeg.isLinked(Direction.DOWN_LEFT));
    }
}
