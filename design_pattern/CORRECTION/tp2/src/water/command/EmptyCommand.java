package water.command;

import water.Can;

public class EmptyCommand extends AbstractCommand {

	private Can can;
	
	public EmptyCommand(Can b) {
		this.can = b;
	}
	
	@Override
	public void execute() {
		setDecantedVolume(can.getVolume());
		can.empty();

	}

	@Override
	public void cancel() {
		can.setVolume(getDecantedVolume());
	}

}
