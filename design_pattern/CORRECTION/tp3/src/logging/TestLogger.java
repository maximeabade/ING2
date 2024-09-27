package logging;

public class TestLogger {
	
	public static void main(String[] args) {
		System.out.println("Eager instanciation");
		LoggerEager.getInstance().log("Hello!");
		LoggerEager.getInstance().log("Bye.");
		System.out.println();
		System.out.println("Lazy instanciation");
		LoggerLazy.getInstance().log("Hello!");
		LoggerLazy.getInstance().log("Bye.");
		System.out.println();
		System.out.println("Multiton");
		LoggerMultiton.getInstance("info").log("Hello!");
		LoggerMultiton.getInstance("err").log("Bug...");
		LoggerMultiton.getInstance("info").log("Bye.");
	}
	
}
