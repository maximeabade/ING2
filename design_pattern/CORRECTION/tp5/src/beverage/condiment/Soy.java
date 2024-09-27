package beverage.condiment;

import beverage.Beverage;

public class Soy extends CondimentDecorator {

	public Soy(Beverage b) {
		super(b);
	}

	public double getPrice() {
		return this.decorated.getPrice() + 0.4;
	}

	public String toString() {
		return this.decorated + ", soy";
	}
	
}
