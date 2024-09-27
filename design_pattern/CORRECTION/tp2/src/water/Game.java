package water;

import java.util.Scanner;

import water.command.DecantCommand;
import water.command.EmptyCommand;
import water.command.FillCommand;

public class Game {

	private Can[] cans;
	private int desiredVolume;
	private Invoker invoker;
	private static Scanner sc = new Scanner(System.in);

	public Game(Can[] cans, int desiredVolume) {
		this.cans = cans;
		this.desiredVolume = desiredVolume;
		this.invoker = new Invoker();
	}

	private Can chooseCan() {
		int choice;
		do {
			for (int i = 0; i < cans.length; i++)
				System.out.println((i + 1) + ". " + cans[i]);
			choice = sc.nextInt();
		} while (choice < 1 || choice > cans.length);
		return cans[choice - 1];
	}

	public void start() {
		while (true) {
			int choice;
			do {
				System.out.println("1. Remplir un bidon");
				System.out.println("2. Vider un bidon");
				System.out.println("3. Transvaser un bidon dans un autre");
				System.out.println("4. Annuler la derni�re action");
				System.out.println("5. Quitter");
				choice = sc.nextInt();
			} while (choice < 1 || choice > 5);
			switch (choice) {
			case 1:
				invoker.pushCommand(new FillCommand(chooseCan()));
				break;
			case 2:
				invoker.pushCommand(new EmptyCommand(chooseCan()));
				break;
			case 3:
				invoker.pushCommand(new DecantCommand(chooseCan(), chooseCan()));
				break;
			case 4:
				invoker.popLastCommand();
				break;
			case 5:
				return;
			}
			for (Can c : cans) {
				System.out.println(c);
			}
			for (Can c : cans) {
				if (c.getVolume() == desiredVolume) {
					System.out.println("Gagn� !");
					return;
				}
			}
		}
	}

	public static void main(String[] args) {
		Can[] cans = { new Can(3), new Can(5) };
		new Game(cans, 4).start();
	}
}
