import boolexpr.*;

public class VisitorNot implements Not {
    @Override
    public boolean Not(Node bool){
        if(bool.toString() == "true"){return false;}
        else{return true;}
    }
}
