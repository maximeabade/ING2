package beverage.condiment;

import beverage.Beverage;

public class Whip extends CondimentDecorator {

	public Whip(Beverage b) {
		super(b);
	}

	public double getPrice() {
		return this.decorated.getPrice() + 0.5;
	}

	public String toString() {
		return this.decorated + ", whip";
	}
	
}
