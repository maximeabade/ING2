import java.util.*;

public class Adapter implements Iterator<Object>{
	
	private Enumeration<Object> enumeration;
		
	public Adapter(Enumeration<Object> enm) {
		enumeration = enm;
	}

	@Override
	public boolean hasNext() {
		return enumeration.hasMoreElements();
	}

	@Override
	public Object next() {
		return enumeration.nextElement();
	}

}
