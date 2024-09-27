package flower.observer;

import java.util.Observable;
import java.util.Observer;

import flower.Flower;


public class Bee implements Observer {

	public void gatherPollen(Flower flower) {
		System.out.println("L'abeille butine une fleur.");
	}

	@Override
	public void update(Observable obs, Object o) {
		Flower flower = (Flower) obs;
		if (flower.isBlooming()) {
			this.gatherPollen(flower);
		}
	}

}
