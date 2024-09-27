public class Logger {
	private static Logger uniqueInstance = null; //on est en lazy ==> ici on cree un nouvelle
	//instance de Logger en un objet null ainsi on est sur que dans la creation on n a 
	//qu une seule et unique instance d un tel objet
	private int nbLoggedMessages;
	
	public static Logger getUniqueInstance() {
		if(uniqueInstance == null) {uniqueInstance = new Logger();}
		return uniqueInstance;
	}
	
	private Logger() {
		this.nbLoggedMessages = 0;
	}
	public void log(String msg) {
		this.nbLoggedMessages++;
		System.out.println("LOG" + this.nbLoggedMessages + ": " + msg);
}
}