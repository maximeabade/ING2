public class Test {
	public static void main (String args[]){
		Logger myFirstLog = Logger.getUniqueInstance();
		myFirstLog.log("Test 1 test 2");
		myFirstLog.log("Test 1 test 2");
		Logger mySecondLog = Logger.getUniqueInstance();
		mySecondLog.log("Test 2 test 1");
		mySecondLog.log("Test 2 test 2");
		myFirstLog.log("bonjour");

		/*
		 * OUTPUT
		 * LOG1: Test 1 test 2
		 * LOG2: Test 1 test 2
		 * LOG3: Test 2 test 1
		 * LOG4: Test 2 test 2
		 * LOG5: bonjour
		 * 
		*/
	}
}