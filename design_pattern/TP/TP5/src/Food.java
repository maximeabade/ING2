  
public enum Food implements Article{
	
	Pâtisserie(2.25,"Pâtisserie"),
	Viennoiserie(1.50,"Viennoiserie"),
	Muffin(2.25,"Muffin"),
	Cookie(1.95,"Cookie"),
	Donut(2.0,"Donut"),
	Sandwich(5.45,"Sandwich");
	
	private final double price;	
	private final String label;
		
	private Food(double price, String label) {
		this.price = price;
		this.label = label;
	}
	
	@Override
	public double getPrice() {
		return this.price;
	}

	@Override
	public String toString() {
		return "encas " + this.label;
	}

}
