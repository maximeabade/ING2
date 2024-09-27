public class Test { 
    public static void main(String args[]){
    
        Facade maFacade = new Facade();
    
        maFacade.SystemActivateFirst();
        System.out.println("Premier systeme activé");

        Facade maSecondeFacade = new Facade();

        maSecondeFacade.SystemActivateSecond();
        System.out.println("second system activé");

    }
}