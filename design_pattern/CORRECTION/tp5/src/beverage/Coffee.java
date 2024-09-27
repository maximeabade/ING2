package beverage;

public class Coffee extends Beverage {

	@Override
	public double getPrice() {
		return 1.75;
	}

	public String toString() {
		return "coffee";
	}

}
