  ;
public class Menu implements Article{

	private Drink drink;
	private Food food;
	
	public Menu(Drink drink, Food food) {
		this.drink = drink;
		this.food = food;
	}
	
	@Override
	public double getPrice() {
		return 0.9*(drink.getPrice() + food.getPrice());
	}

	
	@Override
	public String toString() {
		return "menu (" + this.drink.toString() + " + " + this.food.toString() + ")";
	}
}
