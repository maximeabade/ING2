package condiments;

import composite.Article;
import composite.DrinkCreate;

public class Lait extends DrinkCreate {

	
	
	public Lait(Article drink) {
		super.drink = drink;
	}
	
	@Override
	public double getPrice() {
		return super.drink.getPrice()+0.2;
	}
	
	public String toString() {
		return super.drink.toString() + " lait";
	}

}
