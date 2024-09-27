package flower;

import java.util.Observable;
import java.util.Observer;

@SuppressWarnings("deprecation")
public class Flower extends Observable implements Observer{

	private String name;
	private int blossomSeason;
	private boolean hasBlossomed;
	
	@Override
	public void update(Observable season, Object currentSeason) {
		if (this.blossomSeason == (Integer) currentSeason) {
			this.hasBlossomed = true;
		} else {
			this.hasBlossomed = false;
		}
		System.out.println(this.name + this.hasBlossomed);
	}
	
	
	
	public Flower(int season,String name) {
		this.blossomSeason = season;
		this.name = name;
	}
	
	

}