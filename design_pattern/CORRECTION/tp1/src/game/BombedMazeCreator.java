package game;

import maze.room.Room;
import maze.room.RoomWithABomb;
import maze.wall.BombedWall;
import maze.wall.Wall;

public class BombedMazeCreator extends MazeGameCreator {

	public Room makeRoom(int number) { 
		return new RoomWithABomb(number);
	}
	
	public Wall makeWall() { 
		return new BombedWall();
	}
	
}
