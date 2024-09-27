public class Exo1{

    static int [] triBicolore(int [] t ) {
        int i ;
        // start iterator
        int izero; //last index for next zero (last box)
        i=0;
        izero = t.length-1;
        while (i<izero) {
            // if read a zero , swap with last index
            if (t[i] == 0) {
                t[i]=t[izero];
                t[izero] = 0;
                izero = izero-1;
            }
            i++;
        }
    return t ;
    }
}