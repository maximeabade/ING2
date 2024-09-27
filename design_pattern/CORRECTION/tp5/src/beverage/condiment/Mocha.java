package beverage.condiment;

import beverage.Beverage;

public class Mocha extends CondimentDecorator {

	public Mocha(Beverage b) {
		super(b);
	}

	public double getPrice() {
		return this.decorated.getPrice() + 0.3;
	}

	public String toString() {
		return this.decorated + ", mocha";
	}
	
}
