package beverage.condiment;

import beverage.Beverage;

public class Milk extends CondimentDecorator {

	public Milk(Beverage b) {
		super(b);
	}

	public double getPrice() {
		return this.decorated.getPrice() + 0.2;
	}

	public String toString() {
		return this.decorated + ", milk";
	}
	
}
