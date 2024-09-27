import java.util.*;



public class TD2{
	
	public Integer add(String st){
		Integer count = 0;

		for(int i = 0; i < st.length(); i++) {    
		if( Character.isDigit(st.charAt(i)))    
			count += Integer.parseInt(st.charAt(i)) ;    
        }    

		return count;
	}
	
}


