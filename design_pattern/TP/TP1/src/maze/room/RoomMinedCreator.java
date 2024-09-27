package maze.room;

public class RoomMinedCreator extends RoomCreator{
	
	public Room create(int number) {
		double rand = Math.random();
		
		if (rand < 0.5){
			return new RoomMined(number);
		} else {
			return new Room(number);
		}
	
	}

}
