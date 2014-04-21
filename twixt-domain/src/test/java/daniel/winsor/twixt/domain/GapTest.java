package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.Direction.*;
import static daniel.winsor.twixt.domain.GapType.*;
import static daniel.winsor.twixt.domain.PathType.*;

import org.junit.Assert;
import org.junit.Test;

public class GapTest {
    @Test
    public void testEquality() {
        Assert.assertNotEquals(
                new Gap(DOUBLE_DIAMOND, RIGHT_DOWN),
                new Gap(DOUBLE_SHORT_DIAMOND, RIGHT_DOWN));
        
        Assert.assertEquals(
                new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT),
                new Gap(DOUBLE_SHORT_DIAMOND, DOWN_LEFT).getReversedGap());
    }
    
    @Test
    public void testReverse() {
        Assert.assertNotEquals(
                new Gap(DOUBLE_DIAMOND, RIGHT_DOWN),
                new Gap(DOUBLE_DIAMOND, RIGHT_DOWN).getReversedGap());
        
        Assert.assertEquals(
                new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT),
                new Gap(DOUBLE_SHORT_DIAMOND, DOWN_LEFT).getReversedGap());
    }
    
    @Test
    public void testGetGapFromHoles() {
        Assert.assertEquals(Gap.nullGap, Gap.getGapFromHoles(
                null, null));
        Assert.assertEquals(Gap.nullGap, Gap.getGapFromHoles(
                Hole.nullHole, new Hole(
                        Hole.nullHole.getXCoord()+1,
                        Hole.nullHole.getYCoord()+2)));
        Assert.assertEquals(Gap.nullGap, Gap.getGapFromHoles(
                new Hole(0,0), new Hole(0,0)));
        Assert.assertEquals(Gap.nullGap, Gap.getGapFromHoles(
                new Hole(0,0), new Hole(0,1)));
        
        
        Assert.assertEquals(new Gap(DOUBLE_DIAMOND, LEFT_UP),
                Gap.getGapFromHoles(new Hole(4,0), new Hole(0,0)));
        
        Assert.assertEquals(new Gap(DOUBLE_SHORT_DIAMOND, RIGHT_DOWN),
                Gap.getGapFromHoles(new Hole(0,0), new Hole(2,0)));
    }
    
    @Test
    public void testPathDirection() {
        IGap illegalDirGap = new Gap(DOUBLE_SQUARE, NULL_DIRECTION);
        Assert.assertEquals(NULL_DIRECTION, illegalDirGap.getPathDirection(DIRECT));
        Assert.assertEquals(NULL_DIRECTION, illegalDirGap.getPathDirection(RIGHT));
        
        IGap illegalTypeGap = new Gap(NULL_GAP_TYPE, LEFT_UP);
        Assert.assertEquals(NULL_DIRECTION, illegalTypeGap.getPathDirection(DIRECT));
        Assert.assertEquals(NULL_DIRECTION, illegalTypeGap.getPathDirection(RIGHT));
        
        IGap singleGap = new Gap(SINGLE, LEFT_UP);
        Assert.assertEquals(LEFT_UP, singleGap.getPathDirection(DIRECT));
        Assert.assertEquals(NULL_DIRECTION, singleGap.getPathDirection(RIGHT));
        
        IGap doubleGap = new Gap(DOUBLE_SQUARE, LEFT_UP);
        Assert.assertEquals(NULL_DIRECTION, doubleGap.getPathDirection(DIRECT));
        Assert.assertEquals(LEFT_DOWN, doubleGap.getPathDirection(LEFT));
        Assert.assertEquals(UP_LEFT, doubleGap.getPathDirection(RIGHT));
    }
}
