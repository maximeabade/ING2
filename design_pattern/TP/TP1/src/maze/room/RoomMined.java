package maze.room;


public class RoomMined extends Room{
	
	public RoomMined(int number) {
		super(number);
	}
	
	public String toString() {
		return "mined "+super.toString();
	}
}
