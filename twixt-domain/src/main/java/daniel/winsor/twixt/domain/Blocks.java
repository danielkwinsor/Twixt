package daniel.winsor.twixt.domain;

import static daniel.winsor.twixt.domain.GapType.*;
import static daniel.winsor.twixt.domain.PathType.*;
import static daniel.winsor.twixt.domain.Direction.*;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

/**
 * Given a particular Jump, this contains what other Jumps
 * will block it.
 * The nullBlocks object is immutable, so are any that
 * were created empty. Others are mutable.
 * @author Daniel
 *
 */
public class Blocks {
    /**
     * Immutable object that represents a null value.
     */
    public static final Blocks nullBlocks = new Blocks(Jump.nullJump);
    /**
     * Amazingly, LinkedList performs about the same as ArrayList
     * even in the use case of having no deletions!
     * From the code, this could be because
     * there are less checks in LinkedList than in ArrayList.
     * However, this was only true for when using a ListIterator.
     * Using the get(index) method was slower than the iter.next() for
     * both LinkedList and ArrayList, but was much worse for LinkedList
     * as one might expect.
     * 
     * For now I am choosing to go with LinkedList, as deletions
     * may perform much faster than modifying an ArrayList.
     * 
     * A straight array (32 max) with size value might be much faster
     * than both. Too much work.
     */
    private List<Jump> blocks;
    private Jump jumpToBlock;
    
    public Blocks(final Jump jumpToBlock) {
        setJumpToBlock(jumpToBlock);
        
        if (Jump.nullJump.equals(jumpToBlock)) {
            setBlocks(Collections.<Jump> emptyList());
            return;
        }
        
        setBlocks(new LinkedList<Jump>());
        addAllBlocks();
        
        //in fact, just to be safe, make the empty case immutable
        if (getBlocks().isEmpty()) {
            setBlocks(Collections.<Jump> emptyList());
        }
    }
    
    private void addAllBlocks() {
        final IGap gap = getJumpToBlock().getGap();
        if (gap.getType().isSingle()) {
            addBasicNine(getJumpToBlock().getStart(), gap.getDirection());
        }
        else {
            final Direction leftDir = gap.getPathDirection(LEFT);
            final Direction rightDir = gap.getPathDirection(RIGHT);
            addBasicNine(getJumpToBlock().getStart(), leftDir);
            addBasicNine(getJumpToBlock().getIntHole(LEFT), rightDir);
            
            if (false == gap.getType().isDoubleStraight()) {
                addBasicNine(getJumpToBlock().getStart(), rightDir);
                addBasicNine(getJumpToBlock().getIntHole(RIGHT), leftDir);
            }
        }
    }
    
    private void addIfValid(final int numPrecedingBlocks, final Jump block) {
        //check if the block is on the board
        //TODO delegate logic to the board
        
        //check that this block was not already present
        final List<Jump> precedingBlocks = getBlocks();
        if (numPrecedingBlocks > 0) {
            //Amazingly, using an iterator (with the caveat of only
            //in the way shown: also using a counter) is faster than
            //going straight to the element using an index.
            final ListIterator<Jump> iter = precedingBlocks.listIterator();
            
            for (int index = 0; index < numPrecedingBlocks; ++index) {
                final Jump preceding = iter.next();
                if (block.equals(preceding)) {
                    //not valid; it's a duplicate
                    return;
                }
            }
        }
        
        getBlocks().add(block);
    }
    
    private void addBasicNine(final Hole hole, final Direction direction) {
        if (Hole.nullHole.equals(hole)) {
            return;
        }
        
        final int numPrecedingBlocks = getBlocks().size();
        final int x = hole.getXCoord();
        final int y = hole.getYCoord();
        switch (direction) {
        case LEFT_UP:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y - 1), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y - 1), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y - 1), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 2, y), new Gap(SINGLE, UP_RIGHT)));
            break;
        case UP_LEFT:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y - 1), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y - 1), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y - 1), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 2), new Gap(SINGLE, LEFT_DOWN)));
            break;
        case UP_RIGHT:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y - 1), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y - 1), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y - 1), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 2), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 2), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, LEFT_UP)));
            break;
        case RIGHT_UP:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y - 1), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y - 1), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y - 1), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 2, y), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 2, y), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y - 1), new Gap(SINGLE, DOWN_RIGHT)));
            break;
        case RIGHT_DOWN:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y + 1), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y + 1), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y + 1), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 2, y), new Gap(SINGLE, DOWN_LEFT)));
            break;
        case DOWN_RIGHT:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y + 1), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y + 1), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y + 1), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x + 1, y), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 2), new Gap(SINGLE, RIGHT_UP)));
            break;
        case DOWN_LEFT:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y + 1), new Gap(SINGLE, RIGHT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y + 1), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y + 1), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, LEFT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 2), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 2), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, RIGHT_DOWN)));
            break;
        case LEFT_DOWN:
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y + 1), new Gap(SINGLE, LEFT_UP)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y + 1), new Gap(SINGLE, UP_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y + 1), new Gap(SINGLE, UP_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 1, y), new Gap(SINGLE, DOWN_LEFT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 2, y), new Gap(SINGLE, RIGHT_DOWN)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x - 2, y), new Gap(SINGLE, DOWN_RIGHT)));
            addIfValid(numPrecedingBlocks,
                    new Jump(new Hole(x, y + 1), new Gap(SINGLE, UP_LEFT)));
            break;
        default:
            break;
        }
    }
    
    public List<Jump> getBlocks() {
        return blocks;
    }
    
    private void setBlocks(final List<Jump> blocks) {
        this.blocks = blocks;
    }
    
    public Jump getJumpToBlock() {
        return jumpToBlock;
    }
    
    private void setJumpToBlock(final Jump jumpToBlock) {
        this.jumpToBlock = jumpToBlock;
    }
    
    @Override
    public boolean equals(final Object compare) {
        if (compare == null || compare instanceof Gap == false) {
            return false;
        }
        
        final Blocks other = (Blocks) compare;
        return (getJumpToBlock().equals(other.getJumpToBlock()));
    }
    
    @Override
    public int hashCode() {
        return getJumpToBlock().hashCode();
    }
}
