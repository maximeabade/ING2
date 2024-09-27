package factory;

import maze.door.Door;
import maze.door.MagicDoor;
import maze.room.EnchantedRoom;
import maze.room.Room;

public class EnchantedMazeFactory extends MazeFactory {

	@Override
	public Room makeRoom(int number) {
		return new EnchantedRoom(number);
	}

	@Override
	public Door makeDoor(Room room1, Room room2) {
		return new MagicDoor(room1, room2);
	}

}
