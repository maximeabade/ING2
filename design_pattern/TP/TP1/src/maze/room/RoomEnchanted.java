package maze.room;

public class RoomEnchanted extends Room{


	public RoomEnchanted(int number) {
		super(number);
	}
	
	public String toString() {
		return "enchanted "+super.toString();
	}
}
