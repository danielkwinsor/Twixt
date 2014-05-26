package daniel.winsor.twixt.domain.board.data;

import static daniel.winsor.twixt.domain.board.BoardType.*;

import org.junit.Assert;
import org.junit.Test;

import daniel.winsor.twixt.domain.*;

/**
 * TODO benchmark
 * @author Daniel
 *
 */
public class ArrayListPegDataTest {
    @Test
    public void testGet() {
        ArrayListPegData data = new ArrayListPegData(STANDARD_24);
        Assert.assertEquals(Peg.nullPeg,
                data.getPeg(new Hole(99, 99)));
        Assert.assertEquals(Peg.nullPeg,
                data.getPeg(Hole.nullHole));
        Assert.assertEquals(new Peg(new Hole(0,0), Team.UNOWNED),
                data.getPeg(new Hole(0,0)));
        Assert.assertEquals(new Peg(new Hole(23,23), Team.UNOWNED),
                data.getPeg(new Hole(23,23)));
    }
}
