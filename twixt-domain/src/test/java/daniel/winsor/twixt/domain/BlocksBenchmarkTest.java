package daniel.winsor.twixt.domain;

import org.junit.Assert;
import org.junit.Test;

import daniel.winsor.twixt.domain.board.BoardManager;

public class BlocksBenchmarkTest {
    @Test
    public void testBlocksCreation() {
        final int NUM_TESTS = 1;
        for (int count = 0; count < NUM_TESTS; ++count) {
            for (final GapType gapType : GapType.values()) {
                for (final Direction direction : Direction.values()) {
                    final IGap gap = new Gap(gapType, direction);
                    for (int x = 0; x < BoardManager.getCurrentBoard().getMaxXSize(); ++x) {
                        for (int y = 0; y < BoardManager.getCurrentBoard().getMaxYSize(); ++y) {
                            final Hole hole = new Hole(x, y);
                            final Jump jump = new Jump(hole, gap);
                            final Blocks block = new Blocks(jump);
                            Assert.assertTrue(block.getBlocks().size() <= 32);
                        }
                    }
                }
            }
        }
    }
}
