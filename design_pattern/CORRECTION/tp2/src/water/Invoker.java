package water;

import java.util.Stack;

import water.command.Command;

public class Invoker {

	private Stack<Command> history;

	public Invoker() {
		this.history = new Stack<Command>();
	}

	/**
	 * Execute la commande et la sauve dans l'historique
	 */
	public void pushCommand(Command c) {
		c.execute();
		history.push(c);
	}

	/**
	 * Annule la commande la plus récente et la retire de l'historique
	 */
	public void popLastCommand() {
		history.lastElement().cancel();
		history.pop();
	}

}
