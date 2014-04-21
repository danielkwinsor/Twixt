package daniel.winsor.twixt.domain;

import org.junit.Assert;
import org.junit.Test;

public class BlocksBenchmarkTest {
    @Test
    public void testBlocksCreation() {
        final int NUM_TESTS = 1;
        for (int count = 0; count < NUM_TESTS; ++count) {
            for (GapType gapType : GapType.values()) {
                for (Direction direction : Direction.values()) {
                    IGap gap = new Gap(gapType, direction);
                    for (int x = 0; x < Constants.MAX_BOARD_SIZE; ++x) {
                        for (int y = 0; y < Constants.MAX_BOARD_SIZE; ++y) {
                            Hole hole = new Hole(x, y);
                            Jump jump = new Jump(hole, gap);
                            Blocks block = new Blocks(jump);
                            Assert.assertTrue(block.getBlocks().size() <= 32);
                        }
                    }
                }
            }
        }
    }
}
