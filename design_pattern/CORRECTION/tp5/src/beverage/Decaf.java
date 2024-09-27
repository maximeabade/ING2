package beverage;

public class Decaf extends Beverage {

	@Override
	public double getPrice() {
		return 2.50;
	}

	public String toString() {
		return "decaf";
	}

}
