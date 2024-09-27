package order;

public abstract class Order {

	public abstract double getPrice();

	protected void print() {
		System.out.println("-" + this + " : " + this.getPrice());
	}

	public void total() {
		this.print();
		System.out.println("Total : " + this.getPrice());
	}

	public void add(Order o) {
	}

	public void remove(Order o) {
	}

	public Order getChild(int i) {
		return null;
	}

}
