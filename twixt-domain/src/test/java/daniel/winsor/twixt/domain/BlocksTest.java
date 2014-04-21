package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.Direction.*;
import static daniel.winsor.twixt.domain.GapType.*;

import org.junit.Assert;
import org.junit.Test;

public class BlocksTest {
    @Test
    public void testBlocks() {
        //DOUBLE_SHORT_DIAMONDs will be the same
        Blocks block = new Blocks(new Jump(
                new Hole(6,6), new Gap(DOUBLE_DIAMOND, LEFT_UP)));
        Assert.assertEquals(32, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), new Gap(DOUBLE_DIAMOND, UP_LEFT)));
        Assert.assertEquals(28, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), new Gap(DOUBLE_SQUARE, LEFT_UP)));
        Assert.assertEquals(32, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), new Gap(DOUBLE_SQUARE, UP_LEFT)));
        Assert.assertEquals(32, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), new Gap(DOUBLE_STRAIGHT, UP_LEFT)));
        Assert.assertEquals(18, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), new Gap(SINGLE, UP_LEFT)));
        Assert.assertEquals(9, block.getBlocks().size());
    }
    
    @Test(expected=UnsupportedOperationException.class)
    public void testImmutability() {
        Blocks block = new Blocks(Jump.nullJump);
        block.getBlocks().add(Jump.nullJump);
    }
    
    @Test
    public void testNull() {
        Blocks block = new Blocks(new Jump(
                new Hole(6,6), new Gap(DOUBLE_DIAMOND, NULL_DIRECTION)));
        Assert.assertEquals(0, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), new Gap(NULL_GAP_TYPE, LEFT_UP)));
        Assert.assertEquals(0, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                new Hole(6,6), Gap.nullGap));
        Assert.assertEquals(0, block.getBlocks().size());
        
        block = new Blocks(new Jump(
                Hole.nullHole, new Gap(DOUBLE_DIAMOND, LEFT_UP)));
        Assert.assertEquals(0, block.getBlocks().size());
        
        block = new Blocks(Jump.nullJump);
        Assert.assertEquals(0, block.getBlocks().size());
        
        Assert.assertEquals(0, Blocks.nullBlocks.getBlocks().size());
    }
}
