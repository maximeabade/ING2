import java.util.Scanner;

public class Client {
    public static void main(String[] args){
        //creation d un nouvel arbre
        

        //choix du traitement a faire

        System.out.println("Please make a choice");
        System.out.println("1. PrefixIterator");
        System.out.println("2. InfixIterator");
        System.out.println("3. PostfixIterator");
        Scanner sc = new Scanner(System.in);
        int choice = sc.nextInt();
        if(choice == 1){
            PrefixIterator<V> monIterateur =  new PrefixIterator<>();
        }else if(choice == 2){
            InfixIterator<V> monIterateur = new InfixIterator<>();
        }else if(choice == 3){
            PostfixIterator<V> monIterateur = new PostfixIterator();
        }else{
            System.out.println("Please enter a valid choice");
        }
        

    }

}