package command;

import java.util.Stack;

public class Invoker {
	
	private Stack<Commands> commandStack;
	
	
	public Invoker() {
		this.commandStack = new Stack<Commands>();
	}
	
	public void execute(Commands command) {
		this.commandStack.push(command);
		command.execute();
	}
	
	public void undo() {
		this.commandStack.pop().undo();
	}
	
	public Stack<Commands> getCommandsHistory(){
		return commandStack;
	}
}
