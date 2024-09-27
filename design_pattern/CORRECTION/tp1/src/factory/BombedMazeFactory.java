package factory;

import maze.room.Room;
import maze.room.RoomWithABomb;
import maze.wall.BombedWall;
import maze.wall.Wall;

public class BombedMazeFactory extends MazeFactory {
	
	@Override
	public Room makeRoom(int number) { 
		return new RoomWithABomb(number);
	}
	
	@Override
	public Wall makeWall() { 
		return new BombedWall();
	}
	
}
