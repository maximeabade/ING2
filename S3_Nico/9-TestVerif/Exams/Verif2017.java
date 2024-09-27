//@+ CheckArithOverflow = no
public class Verif2017 {
  /*@ requires 
    @   t != null;
    @ ensures 
    @   \result <==> \forall integer i; 0 <= i < t.length ==> (0 <= t[i] < t.length && \forall integer j; i + 1 <= j < t.length ==> t[i] != t[j]);
    @*/
  public static boolean permutation(int[] t) {
    /*@ loop_invariant
      @  0 <= i <= t.length && 
      @  \forall integer x; 0 <= x < i ==> (0 <= t[x] < t.length && \forall integer y; x + 1 <= y < t.length ==> t[x] != t[y]);
      @ loop_variant t.length - i; 
      @*/
    for (int i = 0; i < t.length; i++) {
      if (t[i] < 0 || t[i] >= t.length)
        return false;
      /*@ loop_invariant
        @  i+1 <= j <= t.length && 
	@   \forall integer x; i + 1 <= x < j ==> t[i] != t[x];
        @ loop_variant t.length - j; 
        @*/
      for (int j = i + 1; j < t.length; j++)
        if (t[i] == t[j])
          return false;
      }
    return true;
  }
  
}
