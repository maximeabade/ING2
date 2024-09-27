package maze.room;

public class RoomEnchantedCreator extends RoomCreator {

	public Room create(int number) {
		return new RoomEnchanted(number);
	}
}
