  ;
public class Main {
	
	public static void main(String[] args) {
		
		Command command = new Command();
		
		command.add((Food.Muffin));
		command.add((Drink.Café));
		command.add(new Menu(Drink.Chocolat,Food.Muffin));
		System.out.println(command);
	}

}
