package composite;

import condiments.*;

public class Main {
	
	public static void main(String[] args) {
		
		Command command = new Command();
		
		command.add(new Menu(Drink.Chocolat,Food.Muffin));
		command.add(new Moka(new Moka(Drink.Café)));
		command.add(new Lait(new Soja(Drink.Café)));

		System.out.println(command.toString());
		
		
	}

}
