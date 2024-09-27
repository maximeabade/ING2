package food;

public class Sandwich extends Food {

	@Override
	public double getPrice() {
		return 5.45;
	}
	
	public String toString() {
		return "sandwich";
	}

}
