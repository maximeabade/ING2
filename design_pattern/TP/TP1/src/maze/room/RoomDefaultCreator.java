package maze.room;

public class RoomDefaultCreator extends RoomCreator{
	
	public Room create(int number) {
		return new Room(number);
	}

}
