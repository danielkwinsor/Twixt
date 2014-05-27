package daniel.winsor.twixt.domain;

import org.junit.Assert;
import org.junit.Test;

public class ImmutablePegTest {
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
    public void testImmutability() {
        Peg immutablePeg = new ImmutablePeg(new Hole(0, 0), Team.UNOWNED);
        Assert.assertEquals(Team.UNOWNED, immutablePeg.getOwner());
        
        immutablePeg.setOwner(Team.RED);
        Assert.assertEquals(Team.UNOWNED, immutablePeg.getOwner());
    }
    
    @Test
    public void testCopyCtor() {
        Peg peg = new Peg(new Hole(1, 1), Team.RED);
        peg.addBlock(Direction.DOWN_LEFT);
        peg.addLink(Direction.UP_LEFT);
        Peg immutablePeg = new ImmutablePeg(peg);
        Assert.assertEquals(immutablePeg, peg);
        Assert.assertEquals(peg, immutablePeg);
        
        Assert.assertEquals(Team.RED, immutablePeg.getOwner());
        Assert.assertEquals(new Hole(1, 1), immutablePeg.getHole());
        Assert.assertTrue(immutablePeg.isBlocked(Direction.DOWN_LEFT));
        Assert.assertFalse(immutablePeg.isBlocked(Direction.UP_LEFT));
        Assert.assertTrue(immutablePeg.isLinked(Direction.UP_LEFT));
        Assert.assertFalse(immutablePeg.isLinked(Direction.DOWN_LEFT));
    }
}
