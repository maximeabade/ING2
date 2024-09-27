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
 
public class TestExo2{

    private Exo2 test;

    @BeforeEach
    public void init(){
        System.out.println("Tiens toi prêt pour un Nouveau Test !");
        test = new Exo2();
    }

    @AfterEach
    public void term(){
        System.out.println("C'est la fin de ce test, j'espère que ça t'as plus ! (Je suis receptif aux critiques positives, garde les négatives pour toi )");
        test = null;
    }    


    @Test
    public void somme1nombre(){
        Assertions.assertEquals("1",test.add("1"),"On retourne le nombre quand il est seul");
    }
    @Test
    public void somme2nombres(){
        Assertions.assertEquals("3",test.add("1,2"),"On retourne la somme des 2 nombres");
    }
    @Test
    public void sommepas(){
        Assertions.assertEquals("0",test.add(""),"On retourne 0 quand la chaine ne possède aucun nombre");
    }

    @Test
    public void sommePleins(){
        Assertions.assertEquals("24", test.add("5,1,1,2,15"), "On retourne la somme des 5 nombres séparés par une virule");
    }


    @Test
    public void anti_slash_n_hehe(){
        Assertions.assertEquals("9", test.add("6\n2,1"), "\n peut etre reconnu comme un séparateur");
    }

    @Test void anti_slash_mal_place(){
        Assertions.assertEquals("Number expected but ’\n’ found at position 3.", test.add("62\n,5,9"), "Le anti slash n est mal placé");
    }





}