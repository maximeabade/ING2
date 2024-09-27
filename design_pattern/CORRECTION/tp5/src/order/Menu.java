package order;

import food.Food;
import beverage.Beverage;

public class Menu extends Order {

	private Beverage beverage;

	private Food food;

	public Menu(Beverage b, Food f) {
		this.beverage = b;
		this.food = f;
	}

	@Override
	public double getPrice() {
		return (this.beverage.getPrice() + this.food.getPrice()) * 0.9;
	}

	public String toString() {
		return "menu (" + this.beverage + " + " + this.food + ")";
	}

}
