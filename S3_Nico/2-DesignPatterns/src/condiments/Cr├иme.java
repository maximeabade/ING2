package condiments;

import composite.Article;
import composite.DrinkCreate;

public class Crème extends DrinkCreate{
	
	public Crème(Article drink) {
		super.drink = drink;
	}
	
	@Override
	public double getPrice() {
		return super.drink.getPrice()+0.5;
	}
	
	public String toString() {
		return super.drink.toString() + " crème";
	}

}
