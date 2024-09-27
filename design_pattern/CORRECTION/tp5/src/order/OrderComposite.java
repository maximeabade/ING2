package order;

import java.util.LinkedList;
import java.util.List;

public class OrderComposite extends Order {

	private List<Order> children;

	public OrderComposite() {
		this.children = new LinkedList<Order>();
	}

	public void add(Order o) {
		children.add(o);
	}

	public void remove(Order o) {
		children.remove(o);
	}

	public Order getChild(int i) {
		return children.get(i);
	}

	@Override
	public double getPrice() {
		double sum = 0;
		for (Order o : children) {
			sum += o.getPrice();
		}
		return sum;
	}

	public void print() {
		for (Order o : children) {
			o.print();
		}
	}

}
