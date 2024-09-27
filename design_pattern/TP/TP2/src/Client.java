import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import command.CommandEmpty;
import command.CommandFill;
import command.CommandTransvase;
import command.Invoker;
import water.Can;

public class Client {
	
	
	public static void main(String[] args){
		int N;
		int goalVolume;
		Map<Integer, Can> map = new HashMap<Integer,Can>();
		boolean isGoalAchieved = false;
		Invoker invoker = new Invoker();
		Scanner sc= new Scanner(System.in);
		
		System.out.println("Entrez le nombre de bidons");
		N = sc.nextInt();
		
		for (int i = 0; i < N; i++) {
			System.out.println("Entrez le volume du prochain bidon");
			map.put(i,new Can(sc.nextInt()));
		}
		System.out.println("Tous les bidons sont crées");
		System.out.println("Entrez le volume recherché");
		goalVolume = sc.nextInt();
		
		
		while(!isGoalAchieved) {
			System.out.println("Choississez votre action :");
			System.out.println("1 - Remplir");
			System.out.println("2 - Vider");
			System.out.println("3 - Transvaser");
			System.out.println("4 - Undo");

			
			switch (sc.nextInt()) {
			case 1:
				System.out.println("Entrez le bidon cible");
				invoker.execute(new CommandFill(map.get(sc.nextInt())));
				
				break;
			case 2:
				System.out.println("Entrez le bidon cible");
				invoker.execute(new CommandEmpty(map.get(sc.nextInt())));
				
				break;
			case 3:
				System.out.println("Entrez les bidons cibles");
				invoker.execute(new CommandTransvase(map.get(sc.nextInt()),map.get(sc.nextInt())));
	
				break;

			case 4:
				invoker.undo();
				break;
				
			default:
				break;
			}
			
			for (int i = 0; i < N; i++) {
				if (map.get(i).getVolume() == goalVolume) {
					isGoalAchieved = true;
				}
			}
			
			System.out.println(map.toString());
		}
	
		System.out.println(invoker.getCommandsHistory().toString());
		sc.close();
	}
	

}



