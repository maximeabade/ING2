package flower;

import java.util.Observable;
import java.util.Random;

import flower.observer.Bee;
import flower.observer.HummingBird;

public class SeasonCycle extends Observable {

	public static enum Season {
		PRINTEMPS, ETE, AUTOMNE, HIVER
	};

	private Season season;

	public SeasonCycle(Season season) {
		this.season = season;
	}

	public SeasonCycle() {
		this(Season.HIVER);
	}

	public Season getSeason() {
		return this.season;
	}

	public void next() {
		season = Season.values()[(season.ordinal() + 1) % 4];
		setChanged();
		notifyObservers();
	}

	public static void main(String[] args) {
		SeasonCycle cycle = new SeasonCycle();
		Bee maya = new Bee();
		HummingBird flit = new HummingBird();
		System.out.println(">>> FLEURS <<<");
		for (int i = 0; i < 10; i++) {
			Flower f = new Flower(Season.values()[new Random().nextInt(4)]);
			System.out.println(f);
			cycle.addObserver(f);
			f.addObserver(maya);
			f.addObserver(flit);
		}
		for (int i = 0; i < 4; i++) {
			System.out.println(">>> "
					+ Season.values()[(cycle.getSeason().ordinal() + 1) % 4]
					+ " <<<");
			cycle.next();
		}
	}

}
