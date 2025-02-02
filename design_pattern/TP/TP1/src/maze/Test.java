package maze;

public class Test {
	
	public static void main(String[] args) {
		
		SimpleMazeGame smg = new SimpleMazeGame();
		
		smg.setRoomCreatorMined();
		
		Maze tkt = smg.createMaze();
		System.out.println(tkt.toString());
		
		SimpleMazeGame smgE = new SimpleMazeGameEnchanted();
		
		smgE.setRoomCreatorEnchanted();
		
		Maze oklm = smgE.createMaze();
		System.out.println(oklm.toString());
		
	}

}
