package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.Direction.*;
import static daniel.winsor.twixt.domain.GapType.*;
import static daniel.winsor.twixt.domain.PathType.*;

import org.junit.Assert;
import org.junit.Test;

public class JumpTest {
    @Test
    public void testIntermediates() {
        Hole fourfour = new Hole(4, 4);
        Assert.assertEquals(new Hole(2, 5),
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, LEFT_UP))
                        .getIntHole(LEFT));
        Assert.assertEquals(new Hole(2, 3),
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, LEFT_UP))
                        .getIntHole(RIGHT));
        
        Assert.assertEquals(Hole.nullHole,
                new Jump(Hole.nullHole, new Gap(DOUBLE_DIAMOND, LEFT_UP))
                        .getIntHole(RIGHT));
        Assert.assertEquals(Hole.nullHole,
                new Jump(fourfour, new Gap(NULL_GAP_TYPE, LEFT_UP))
                        .getIntHole(RIGHT));
        Assert.assertEquals(Hole.nullHole,
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, NULL_DIRECTION))
                        .getIntHole(RIGHT));
        Assert.assertEquals(Hole.nullHole,
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, LEFT_UP))
                        .getIntHole(NULL_PATH_TYPE));
    }
    
    @Test
    public void testDestination() {
        Hole fourfour = new Hole(4, 4);
        Assert.assertEquals(new Hole(0, 4),
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, LEFT_UP))
                        .getDest());
        Assert.assertEquals(new Hole(1, 1),
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, UP_LEFT))
                        .getDest());
        Assert.assertEquals(new Hole(4, 0),
                new Jump(fourfour, new Gap(DOUBLE_DIAMOND, UP_RIGHT))
                        .getDest());
        
        Assert.assertEquals(new Hole(1, 3),
                new Jump(fourfour, new Gap(DOUBLE_SQUARE, LEFT_UP))
                        .getDest());
        Assert.assertEquals(new Hole(0, 2),
                new Jump(fourfour, new Gap(DOUBLE_STRAIGHT, LEFT_UP))
                        .getDest());
        Assert.assertEquals(new Hole(2, 4),
                new Jump(fourfour, new Gap(DOUBLE_SHORT_DIAMOND, LEFT_UP))
                        .getDest());
        
        //offboard is ok
        Assert.assertEquals(new Hole(-4, -2),
                new Jump(new Hole(0, 0), new Gap(DOUBLE_STRAIGHT, LEFT_UP))
                        .getDest());
        
        Assert.assertEquals(Hole.nullHole,
                new Jump(Hole.nullHole, new Gap(DOUBLE_DIAMOND, LEFT_UP))
                        .getDest());
        Assert.assertEquals(Hole.nullHole,
                new Jump(new Hole(0, 0), new Gap(NULL_GAP_TYPE, LEFT_UP))
                        .getDest());
        Assert.assertEquals(Hole.nullHole,
                new Jump(new Hole(0, 0), new Gap(DOUBLE_DIAMOND, NULL_DIRECTION))
                        .getDest());
    }
    
    @Test
    public void testReversedJump() {
        Assert.assertEquals(
                new Jump(new Hole(4,4), new Gap(DOUBLE_DIAMOND, LEFT_UP)),
                new Jump(new Hole(0,4), new Gap(DOUBLE_DIAMOND, RIGHT_DOWN))
                        .getReversedJump());
        
        Assert.assertEquals(
                new Jump(new Hole(4,4), new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT)),
                new Jump(new Hole(4,2), new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT).getReversedGap())
                        .getReversedJump());
        
        Assert.assertEquals(
                new Jump(new Hole(4,4), new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT)),
                new Jump(new Hole(4,2), new Gap(DOUBLE_SHORT_DIAMOND, DOWN_LEFT))
                        .getReversedJump());
    }
    
    @Test
    public void testEquality() {
        Assert.assertEquals(
                new Jump(new Hole(4,4), new Gap(DOUBLE_DIAMOND, LEFT_UP)),
                new Jump(new Hole(0,4), new Gap(DOUBLE_DIAMOND, RIGHT_DOWN)));
        
        Assert.assertEquals(
                new Jump(new Hole(4,4), new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT)),
                new Jump(new Hole(4,2), new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT).getReversedGap()));
        
        Assert.assertEquals(
                new Jump(new Hole(4,4), new Gap(DOUBLE_SHORT_DIAMOND, UP_RIGHT)),
                new Jump(new Hole(4,2), new Gap(DOUBLE_SHORT_DIAMOND, DOWN_LEFT)));
    }
}
