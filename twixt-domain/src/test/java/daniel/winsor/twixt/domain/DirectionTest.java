package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.Direction.*;

import org.junit.Assert;
import org.junit.Test;

public class DirectionTest {
    @Test
    public void testOpposite() {
        Assert.assertEquals(RIGHT_DOWN, LEFT_UP.getOpposite());
        Assert.assertEquals(LEFT_UP, RIGHT_DOWN.getOpposite());
    }
    
    @Test
    public void testLeft() {
        Assert.assertEquals(LEFT_DOWN, LEFT_UP.rotateLeft());
        Assert.assertEquals(DOWN_LEFT, LEFT_DOWN.rotateLeft());
        Assert.assertEquals(LEFT_DOWN, LEFT_UP.rotateCounterClockwise());
        Assert.assertEquals(DOWN_LEFT, LEFT_DOWN.rotateCounterClockwise());
        Assert.assertEquals(DOWN_LEFT, LEFT_UP.rotateLeft().rotateLeft());
        Assert.assertEquals(DOWN_RIGHT, LEFT_UP.rotateLeft().rotateLeft()
                .rotateLeft());
        Assert.assertEquals(RIGHT_DOWN, LEFT_UP.rotateLeft().rotateLeft()
                .rotateLeft().rotateLeft());
        Assert.assertEquals(RIGHT_UP, LEFT_UP.rotateLeft().rotateLeft()
                .rotateLeft().rotateLeft().rotateLeft());
        Assert.assertEquals(UP_RIGHT, LEFT_UP.rotateLeft().rotateLeft()
                .rotateLeft().rotateLeft().rotateLeft().rotateLeft());
        Assert.assertEquals(UP_LEFT, LEFT_UP.rotateLeft().rotateLeft()
                .rotateLeft().rotateLeft().rotateLeft().rotateLeft()
                .rotateLeft());
        Assert.assertEquals(LEFT_UP, LEFT_UP.rotateLeft().rotateLeft()
                .rotateLeft().rotateLeft().rotateLeft().rotateLeft()
                .rotateLeft().rotateLeft());
    }

    @Test
    public void testRight() {
        Assert.assertEquals(UP_LEFT, LEFT_UP.rotateRight());
        Assert.assertEquals(LEFT_UP, LEFT_DOWN.rotateRight());
        Assert.assertEquals(UP_LEFT, LEFT_UP.rotateClockwise());
        Assert.assertEquals(LEFT_UP, LEFT_DOWN.rotateClockwise());
        Assert.assertEquals(UP_RIGHT, LEFT_UP.rotateRight().rotateRight());
    }

    @Test
    public void testNull() {
        Assert.assertEquals(NULL_DIRECTION, NULL_DIRECTION);
        Assert.assertEquals(NULL_DIRECTION, NULL_DIRECTION.rotateLeft());
        Assert.assertEquals(NULL_DIRECTION, NULL_DIRECTION.rotateRight());
        Assert.assertEquals(NULL_DIRECTION, NULL_DIRECTION.getOpposite());
    }
}
