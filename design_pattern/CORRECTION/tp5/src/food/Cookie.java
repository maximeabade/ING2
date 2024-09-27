package food;

public class Cookie extends Food {

	@Override
	public double getPrice() {
		return 1.95;
	}
	
	public String toString() {
		return "cookie";
	}

}
