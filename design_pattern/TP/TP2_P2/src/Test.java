import flower.Flower;

public class Test {

	@SuppressWarnings("deprecation")
	public static void main(String[] args) {
		
		
		Seasons seasons = new Seasons();
		Flower winterFlower = new Flower(0,"winterFlower");
		Flower springFlower = new Flower(1,"springFlower");
		Flower summerFlower = new Flower(2,"summerFlower");
		Flower autumnFlower = new Flower(3,"autumnFlower");
		
		seasons.addObserver(winterFlower);
		seasons.addObserver(springFlower);
		seasons.addObserver(summerFlower);
		seasons.addObserver(autumnFlower);
		
		seasons.passTime();
		seasons.passTime();
		seasons.passTime();
		seasons.passTime();
		seasons.passTime();
	}
}
