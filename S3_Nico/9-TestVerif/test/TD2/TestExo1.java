import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import java.util.*;

public class TestExo1{

    private Exo1 test;

    @BeforeAll
    public static void debut(){
        System.out.println("Hé coquin, faisons des tests");
    }

    @AfterAll
    public static void fin(){
        System.out.println("A une prochaine fois pour faire du Test à grande échelle coquin");
    }

    @BeforeEach
    public void init(){
        System.out.println("Tiens toi prêt pour un Nouveau Test !");
        test = new Exo1();
    }

    @AfterEach
    public void term(){
        System.out.println("C'est la fin de ce test, j'espère que ça t'as plus ! (Je suis receptif aux critiques positives, garde les négatives pour toi )");
        test = null;
    }

    @Test
    @DisplayName("on va voir si tu réfléchie")
    public void test1(){
        // int[] i = new int[]; 
        // int tab[] = new int[];
        System.out.println("youhou");
        Assertions.assertEquals(Arrays.toString(new int []{1}), Arrays.toString(test.triBicolore(new int []{1})), "Te fous pas de ma gueule !");
    }

    @Test
    @DisplayName("on va voir si tu réfléchie - le retour")
    public void test2(){
        //int[] i = new int[]{0,1}; 
        // int tab[] = new int[];
        Assertions.assertEquals(Arrays.toString(new int []{1,0}), Arrays.toString(test.triBicolore(new int[]{0,1})), "Te fous pas de ma gueule ! - le retour");
    }
}