package composite;

public enum Drink implements Article{
	
	Expresso(2.75,"Expresso"),
	Chocolat(3.55,"Chocolat"),
	Café(1.75,"Café"),
	Décaféiné(2.5,"Décaféiné"),
	Thé(3.15,"Thé");
	
	private final double price;	
	private final String label;
		
	private Drink(double price, String label) {
		this.price = price;
		this.label = label;
	}
	
	@Override
	public double getPrice() {
		return this.price;
	}
	
	
	 @Override
	 public String toString() {
		 return "boisson "+this.label;
	 }
}
