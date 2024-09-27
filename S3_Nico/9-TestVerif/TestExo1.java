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


    // @Test
    // public void test_div_3() {
    //     Assertions.assertEquals("Fizz",test.fizzBuzz(3),"On doit afficher Fizz pour les multiples de 3");
    // }

    // @Test
    // public void test_div_5() {
    //     Assertions.assertEquals("Buzz",test.fizzBuzz(5),"On doit afficher Buzz pour les multiples de 5");
    // }

    @Test
    public void test_valeur_standart(){
        Assertions.assertEquals("1",test.fizzBuzz(1),"On doit afficher le nombre quand c'est ni un multiple de 3 ou 5");
        Assertions.assertEquals("2",test.fizzBuzz(2),"On doit afficher le nombre quand c'est ni un multiple de 3 ou 5");
        Assertions.assertEquals("11",test.fizzBuzz(11),"On doit afficher le nombre quand c'est ni un multiple de 3 ou 5");
    }

    // @Test
    // public void test_div_3_et_5() {
    //     Assertions.assertEquals("FizzBuzz",test.fizzBuzz(15),"On doit afficher FizzBuzz pour les multiples de 3 et 5");
    // }


    @Test
    public void test_3_in_number(){
        Assertions.assertEquals("Fizz",test.fizzBuzz(13),"On doit afficher Fizz pour les nombres contenant 3");
    }


    @Test
    public void test_5_in_number(){
        Assertions.assertEquals("Buzz",test.fizzBuzz(58),"On doit afficher Fizz pour les nombres contenant 5");
    }

    @Test
    public void test_div_3() {
        Assertions.assertAll("Fizz",
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(3),"On doit afficher Fizz pour les multiples de 3"),
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(33),"On doit afficher Fizz pour les multiples de 3"),
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(21),"On doit afficher Fizz pour les multiples de 3"),
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(24),"On doit afficher Fizz pour les multiples de 3"),
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(99),"On doit afficher Fizz pour les multiples de 3")
        );    
    }

    @Test
    public void test_div_5() {
        Assertions.assertAll("Buzz",
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(5),"On doit afficher Buzz pour les multiples de 5"),
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(50),"On doit afficher Buzz pour les multiples de 5"),
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(25),"On doit afficher Buzz pour les multiples de 5"),
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(80),"On doit afficher Buzz pour les multiples de 5"),
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(100),"On doit afficher Buzz pour les multiples de 5")
        );
    }

    @Test
    public void test_div_3_et_5() {
        Assertions.assertAll("FizzBuzz",
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(15),"On doit afficher FizzBuzz pour les multiples de 3 et 5"),
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(30),"On doit afficher FizzBuzz pour les multiples de 3 et 5"),
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(75),"On doit afficher FizzBuzz pour les multiples de 3 et 5")
        );
        
    }

    @Test
    public void test_div5_cont5(){
        Assertions.assertAll("Buzz",
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(5)),
            () -> Assertions.assertEquals("Buzz",test.fizzBuzz(55))
        );
    }

    @Test
    public void test_div3_cont5(){
        Assertions.assertAll("FizzBuzz",
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(51)),
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(57))
        );
    }


    @Test
    public void test_div5_cont3(){
        Assertions.assertAll("FizzBuzz",
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(30)),
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(35))
        );
    }

 }
