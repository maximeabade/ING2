/*
 * Écrivez une classe qui utilise directement les classes de l'archive
 *  pour créer un système de sécurité composé de cinq capteurs, une alarme, deux caméras et trois lumières. En
particulier, la classe contient une méthode pour activer le système de sécurité (i.e.,
activation des capteurs et des alarmes, mise en route des caméras et extinction des
lumières) et une autre pour le désactiver (i.e., désactivation des capteurs, arrêt de la
sonnerie des alarmes et extinction des caméras).
 * */
 

public class Facade {

	Sensor sensor1 = new Sensor();
	Sensor sensor2 = new Sensor();
	Sensor sensor3 = new Sensor();
	Sensor sensor4 = new Sensor();
	Sensor sensor5 = new Sensor();
	Alarm alarm1 = new Alarm();
	Camera cam1 = new Camera();
	Camera cam2 = new Camera();
	Light light1 = new Light();
	Light light2 = new Light();
	Light light3 = new Light();
	
	public void SystemActivateFirst() {
		sensor1.activate();
		sensor2.activate();
		sensor3.activate();
		sensor4.activate();
		sensor5.activate();
		alarm1.activate();
		cam1.turnOn();
		cam2.turnOn();
		light1.turnOn();
		light2.turnOn();
		light3.turnOn();
		
	}	

	public void SystemActivateSecond() {
		sensor1.activate();
		sensor2.activate();
		alarm1.activate();
		cam1.turnOn();
		cam2.turnOn();
		
	}
	
}