package condiments;

import composite.Article;
import composite.DrinkCreate;

public class Moka extends DrinkCreate{
	
	
	public Moka(Article drink) {
		super.drink = drink;
	}
	
	@Override
	public double getPrice() {
		return super.drink.getPrice()+0.3;
	}
	
	public String toString() {
		return super.drink.toString() + " moka";
	}

}
