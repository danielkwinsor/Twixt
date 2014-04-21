package daniel.winsor.twixt.domain;

/**
 * A section of the board able to fit 1 Peg into.
 * @author Daniel
 *
 */
public final class Hole {
    private static final int nullValue = -99;
    /**
     * Hole(-1,-1) might not be good enough, Hole(-1,-1) (invalid)
     *  can reach Hole(0,1) (valid) in just 1 jump.
     *  So nullHole is Hole(nullValue, nullValue)
     */
    public static final Hole nullHole = new Hole(nullValue, nullValue);
    private int xCoord;
    private int yCoord;
    
    public Hole(final int xCoord, final int yCoord) {
        init(xCoord, yCoord);
    }
    
    public Hole(final char xChar, final int yCoord) {
        init(xChar, yCoord);
    }
    
    public Hole(final String string) {
        init(string);
    }
    
    private void init(final int xCoord, final int yCoord) {
        this.setxCoord(xCoord);
        this.setyCoord(yCoord);
    }
    
    private void init(final char xChar, final int yCoord) {
        if (xChar >= 'a' && xChar <= 'x') {
            init((xChar - 'a'), yCoord);
            return;
        }
        if (xChar >= 'A' && xChar <= 'X') {
            init((xChar - 'A'), yCoord);
            return;
        }
        init(nullValue, nullValue);
    }
    
    private void init(final String string) {
        if (string == null || string.length() < 2) {
            init(nullValue, nullValue);
            return;
        }
        
        char xChar = string.charAt(0);
        int yCoord = nullValue;
        try {
            //these numbers are not 0 based
            yCoord = Integer.parseInt(string.substring(1));
            --yCoord;
        }
        catch (NumberFormatException e) {
            //e.printStackTrace();
            //TODO: logger
            init(nullValue, nullValue);
            return;
        }
        init(xChar, yCoord);
    }
    
    /**
     * The board is arranged with 0,0 at top left
     * @param dir
     * @return The Hole that would result if going 1 Link in the dir Direction
     */
    public Hole getHoleFromDir(Direction dir) {
        if (nullHole.equals(this)) {
            return nullHole;
        }
        switch (dir) {
        case LEFT_UP:
            return new Hole(getXCoord()-2, getYCoord()-1);
        case UP_LEFT:
            return new Hole(getXCoord()-1, getYCoord()-2);
        case UP_RIGHT:
            return new Hole(getXCoord()+1, getYCoord()-2);
        case RIGHT_UP:
            return new Hole(getXCoord()+2, getYCoord()-1);
        case RIGHT_DOWN:
            return new Hole(getXCoord()+2, getYCoord()+1);
        case DOWN_RIGHT:
            return new Hole(getXCoord()+1, getYCoord()+2);
        case DOWN_LEFT:
            return new Hole(getXCoord()-1, getYCoord()+2);
        case LEFT_DOWN:
            return new Hole(getXCoord()-2, getYCoord()+1);
        default:
            return nullHole;
        }
    }
    
    public Hole getHoleFromDir(IGap gap) {
        return getHoleFromDir(gap.getDirection(), gap.getType());
    }
    
    public Hole getHoleFromDir(Direction dir, GapType type) {
        switch (type) {
        case SINGLE:
            return getHoleFromDir(dir);
        case DOUBLE_DIAMOND:
            return getHoleFromDir(dir).getHoleFromDir(dir.rotateLeft());
        case DOUBLE_SQUARE:
            return getHoleFromDir(dir.rotateLeft()).getHoleFromDir(dir.rotateRight());
        case DOUBLE_SHORT_DIAMOND:
            return getHoleFromDir(dir.rotateLeft().rotateLeft()).getHoleFromDir(dir.rotateRight());
        case DOUBLE_STRAIGHT:
            return getHoleFromDir(dir).getHoleFromDir(dir);
        default:
            break;
        }
        return nullHole;
    }
    
    public int getYCoord() {
        return yCoord;
    }

    private void setyCoord(int yCoord) {
        this.yCoord = yCoord;
    }

    public int getXCoord() {
        return xCoord;
    }

    private void setxCoord(int xCoord) {
        this.xCoord = xCoord;
    }
    
    @Override
    public String toString() {
        char xChar = (char) (this.getXCoord() + 'A');
        String xString = Character.toString(xChar);
        if (xChar < 'A' || xChar > 'X') {
            xString = Integer.toString(this.getXCoord());
        }
        return "Hole(" + getXCoord() + ", " + getYCoord() + ")["
                + xString + (getYCoord() + 1) + "]";
    }
    
    @Override
    public boolean equals(Object compare) {
        if (compare == null || compare instanceof Hole == false) {
            return false;
        }
        
        Hole other = (Hole) compare;
        return (getXCoord() == other.getXCoord()
                && getYCoord() == other.getYCoord());
    }
    
    @Override
    public int hashCode() {
        return ((getXCoord() * Constants.MAX_BOARD_SIZE) + getYCoord());
    }
}