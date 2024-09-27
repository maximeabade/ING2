package command;

import water.Can;

public class CommandFill implements Commands{
	private Can can;
	private int Volume;
	
	public CommandFill(Can can) {
		this.can = can;
	}
	
	public void undo() {
		this.can.setVolume(this.Volume);
	}
	
	public void execute() {
		this.Volume = this.can.getVolume();
		this.can.setVolume(this.can.getMaxVolume());
	}

}
