package command;

import water.Can;

public class CommandEmpty implements Commands{
	private Can can;
	private int Volume;
	
	public CommandEmpty(Can can) {
		this.can = can;
	}
	
	public void undo() {
		this.can.setVolume(this.Volume);
	}
	
	public void execute() {
		this.Volume = this.can.getVolume();
		this.can.setVolume(0);
	}
}
