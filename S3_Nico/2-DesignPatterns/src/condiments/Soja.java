package condiments;

import composite.Article;
import composite.DrinkCreate;

public class Soja extends DrinkCreate{
	
	public Soja(Article drink) {
		super.drink = drink;
	}
	
	@Override
	public double getPrice() {
		return super.drink.getPrice()+0.4;
	}
	
	public String toString() {
		return super.drink.toString() + " soja";
	}

}
