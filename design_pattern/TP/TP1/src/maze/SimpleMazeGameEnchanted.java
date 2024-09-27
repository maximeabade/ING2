package maze;

import maze.room.Room;
import maze.room.RoomEnchanted;

public class SimpleMazeGameEnchanted extends SimpleMazeGame{
	
	public Room createRoom(int number) {
		return new RoomEnchanted(number);
	}
	
}
