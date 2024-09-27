package command;

import water.Can;

public class CommandTransvase implements Commands{
	private Can A;
	private Can B;
	private int decantedVolume;
	
	
	public CommandTransvase(Can A,Can B) {
		this.A = A;
		this.B = B;
	}
	
	public void undo(){
		this.A.setVolume(this.A.getVolume()+this.decantedVolume);
		this.B.setVolume(this.B.getVolume()-this.decantedVolume);
		
	}
	
	public void execute() {
		this.decantedVolume = this.A.decant(this.B);
	}
}
