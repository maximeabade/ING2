package maze;
import maze.door.Door;
import maze.room.Room;
import maze.room.Room.Direction;
import maze.room.RoomCreator;
import maze.room.RoomDefaultCreator;
import maze.room.RoomEnchanted;
import maze.room.RoomEnchantedCreator;
import maze.room.RoomMined;
import maze.room.RoomMinedCreator;
import maze.wall.Wall;

public class SimpleMazeGame {
	private Maze maze = new Maze();
	private RoomCreator roomcreator = new RoomDefaultCreator();
	
	public Room createRoom(int number) {
		return new Room(number);
	}
	
	
	public Maze createMaze() {
		Room room1 = roomcreator.create(1);
		Room room2 = roomcreator.create(2);
		
		maze.addRoom(room1);
		maze.addRoom(room2);
		
		room1.setSide( Direction.EAST , new Wall());
		room1.setSide( Direction.WEST , new Wall());
		room1.setSide( Direction.SOUTH , new Wall());
		
		room2.setSide( Direction.EAST , new Wall());
		room2.setSide( Direction.WEST , new Wall());
		room2.setSide( Direction.NORTH , new Wall());
		
		Door door = new Door(room1,room2);
		
		room1.setSide(Direction.NORTH, door);
		room2.setSide(Direction.SOUTH, door);
		
		return maze;
	}
	public void setRoomCreatorDefault() {
		this.roomcreator = new RoomDefaultCreator();
	}
	
	public void setRoomCreatorEnchanted() {
		this.roomcreator = new RoomEnchantedCreator();
	}

	public void setRoomCreatorMined() {
		this.roomcreator = new RoomMinedCreator();
	}
}
