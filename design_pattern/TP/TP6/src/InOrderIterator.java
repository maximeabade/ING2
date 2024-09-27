//on veut laisser le choix de quel iterateur, et retourner cet itérateur. Choix entre InfixIterator, PostfixIterator et PrefixIterator
import java.util.Scanner;
import java.util.Iterator;
import java.util.*;

public class InOrderIterator {
    public Iterator<V> InOrderIterator(){
        System.out.println("Please enter a choice");
        System.out.println("1. PrefixIterator");
        System.out.println("2. InfixIterator");
        System.out.println("3. PostfixIterator");
        Scanner sc = new Scanner(System.in);
        int choice = sc.nextInt();
        if(choice == 1){
            return new PrefixIterator();
        }else if(choice == 2){
            return new InfixIterator();
        }else if(choice == 3){
            return new PostfixIterator();
        }else{
            System.out.println("Please enter a valid choice");
            return null;
        }
    }
}