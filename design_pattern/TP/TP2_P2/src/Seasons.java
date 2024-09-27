import java.util.HashMap;
import java.util.Map;
import java.util.Observable;

@SuppressWarnings("deprecation")

public class Seasons extends Observable{
	
	
	private int currentSeason = 0;
	private Map<Integer,String> seasons = new HashMap<Integer,String>();
	
	public Seasons() {
		this.seasons.put(0, "Winter");
		this.seasons.put(1, "Spring");
		this.seasons.put(2, "Summer");
		this.seasons.put(3, "Autumn");
	}
	
	public String passTime() {
		this.currentSeason = (this.currentSeason + 1) % 4;
		System.out.println("Change to :" + seasons.get(currentSeason));
		setChanged();
		notifyObservers(this.currentSeason);
		return this.seasons.get(this.currentSeason);
	}
	
	
}
