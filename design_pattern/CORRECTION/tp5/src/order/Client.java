package order;

import food.Cake;
import food.Muffin;
import beverage.Chocolate;
import beverage.Coffee;
import beverage.condiment.Milk;
import beverage.condiment.Mocha;
import beverage.condiment.Soy;

public class Client {

	public static void main(String[] args) {
		// Composite pattern
		Order simpleOrder = new Cake();
		System.out.println(">>> Commande simple <<<");
		simpleOrder.total();
		System.out.println();
		Order compositeOrder = new OrderComposite();
		compositeOrder.add(new Menu(new Chocolate(), new Muffin()));
		compositeOrder.add(new Coffee());
		compositeOrder.add(new Coffee());
		System.out.println(">>> Commande composite <<<");
		compositeOrder.total();
		System.out.println();
		
		// Decorator pattern
		Order orderWithCondiments = new OrderComposite();
		orderWithCondiments.add(new Menu(new Chocolate(), new Muffin()));
		orderWithCondiments.add(new Mocha(new Mocha(new Coffee())));
		orderWithCondiments.add(new Milk(new Soy(new Coffee())));
		System.out.println(">>> Commande avec condiments <<<");
		orderWithCondiments.total();
	}

}
