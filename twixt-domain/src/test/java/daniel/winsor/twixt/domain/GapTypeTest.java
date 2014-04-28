package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.GapType.*;

import org.junit.Assert;
import org.junit.Test;

public class GapTypeTest {
    @Test
    public void testGetGapType() {
        Assert.assertEquals(NULL_GAP_TYPE, GapType.getGapType(
                null, null));
        Assert.assertEquals(NULL_GAP_TYPE, GapType.getGapType(
                Hole.nullHole, new Hole(
                        Hole.nullHole.getXCoord() + 1,
                        Hole.nullHole.getYCoord() + 2)));
        Assert.assertEquals(NULL_GAP_TYPE, GapType.getGapType(
                new Hole(0, 0), new Hole(0, 0)));
        Assert.assertEquals(NULL_GAP_TYPE, GapType.getGapType(
                new Hole(0, 0), new Hole(0, 1)));
        
        
        Assert.assertEquals(DOUBLE_DIAMOND,
                GapType.getGapType(new Hole(4, 0), new Hole(0, 0)));
        
        Assert.assertEquals(DOUBLE_SHORT_DIAMOND,
                GapType.getGapType(new Hole(0, 0), new Hole(2, 0)));
    }
}
