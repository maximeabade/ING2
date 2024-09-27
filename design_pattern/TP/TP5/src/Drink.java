  ;
public enum Drink implements Article{
	
	Expresso(2.75,"Expresso"),
	Chocolat(3.55,"Chocolat"),
	Café(1.75,"Café"),
	Décaféiné(2.5,"Décaféiné"),
	Thé(3.15,"Thé");
	
	private double price;	
	private String label;
	private boolean milk;
	private boolean soy;
	private boolean moka;
	private boolean cream;
	


	private Drink(double price, String label) {
		this.price = price;
		this.label = label;
	}

	private Drink(double price, String label, boolean milk, boolean soy, boolean moka, boolean cream) {
		this.price = price;
		this.label = label;
		this.milk = milk;
		this.soy = soy;
		this.moka = moka;
		this.cream = cream;
		if(milk){this.price += 0.20;}
		if(soy){this.price += 0.30;}
		if(moka){this.price += 0.40;}
		if(cream){this.price += 0.50;}
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
