package flower;

import java.util.Observable;
import java.util.Observer;

import flower.SeasonCycle.Season;

public class Flower extends Observable implements Observer {

	private boolean isBlooming;

	private Season season;

	public Flower(Season season) {
		this.isBlooming = false;
		this.season = season;
	}

	public boolean isBlooming() {
		return this.isBlooming;
	}

	public void bloom() {
		this.isBlooming = true;
		setChanged();
		notifyObservers();
	}

	public Season getSeason() {
		return this.season;
	}

	public String toString() {
		return "Fleur fleurissant durant la saison " + this.getSeason() + ".";
	}

	@Override
	public void update(Observable obs, Object o) {
		SeasonCycle season = (SeasonCycle) obs;
		if (season.getSeason().equals(this.getSeason()) && !isBlooming()) {
			this.bloom();
		}
	}
}
