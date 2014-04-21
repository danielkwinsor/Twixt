package daniel.winsor.twixt.domain;

/**
 * When looking at a special GapType, there may be certain paths.
 * For instance, when forming a DOUBLE_DIAMOND going from the start to the end,
 * you can take the left or right path, with 1 of 2 intermediate holes
 * inbetween.
 * @author Daniel
 *
 */
public enum PathType {
    //a single jump will go straight to it
    DIRECT,
    
    //for double jumps, including DOUBLE_STRAIGHT
    LEFT,
    RIGHT,
    
    //for triple jump gaps there are 6 paths
    //TODO if necessary
    //LEFT_LEFT,
    //LEFT_RIGHT,
    //CENTER_LEFT,
    //CENTER_RIGHT,
    //RIGHT_LEFT,
    //RIGHT_RIGHT,
    
    //A path composed of N number Jumps
    FREE_FORM,
    
    NULL_PATH_TYPE;
}
