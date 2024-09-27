
import java.util.*;

public class test {
	
	public static void display(Iterator<Object> iterator) {
		while (iterator.hasNext()) {
			Object current = iterator.next();
			if(current instanceof String) {
				System.out.println(current);
			}
		}
	}

	@SuppressWarnings({ "deprecation" })
	public static void main(String[] args) {
		
		List<Object> list = new ArrayList<Object>();
		list.add("string");
		list.add(new Integer(42));
		list.add("string2");
		list.add("string3");
		list.add(new Float(4.2));

		Iterator<Object> itr = list.iterator();
		
		display(itr);
		
		Vector<Object> vect= new Vector<Object>();
		vect.add("string_2");
		vect.add(new Integer(42));
		vect.add("string2_2");
		vect.add("string3_2");
		vect.add(new Float(4.2));

		Enumeration<Object> itr2 = vect.elements();
		
		display(itr2);
	}
	
}
