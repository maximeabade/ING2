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

public class TestTD4EX2 {

    public TD4EX2 test;

    @BeforeAll
    public static void start(){
        System.out.println("START");
    }

    @AfterAll
    public static void end(){
        System.out.println("END");
    }

    @BeforeEach
    public void start_test(){
        System.out.println("New Test");
        test = new TD4EX2();
    }

    @AfterEach
    public void end_test(){
        System.out.println("End Test");
        test = null;
    }


    @Test
    public void test_empty(){
        Assertions.assertEquals("0.0",test.add(""), "Une chaîne vide retourne 0.0" );
    }

    @Test
    public void test_integer_numbers(){
        Assertions.assertAll("",
            () -> Assertions.assertEquals("0.0",test.add("0,0"),"Chaine \"0,0\", résultat 0.0"),
            () -> Assertions.assertEquals("3.0",test.add("1,2"),"Chaine \"1,2\", résultat 0.0"),
            () -> Assertions.assertEquals("18.0",test.add("5,6,7"),"Chaine \"5,6,7\", résultat 18.0")
        );
    }

    @Test
    public void test_double_numbers(){
        Assertions.assertAll("",
            () -> Assertions.assertEquals("0.0",test.add("0.0,0"),"Chaine \"0,0\", résultat 0.0"),
            () -> Assertions.assertEquals("3.1",test.add("1.1,2"),"Chaine \"1,2\", résultat 0.0"),
            () -> Assertions.assertEquals("18.0",test.add("5.5,5.5,7"),"Chaine \"5,6,7\", résultat 18.0")
        );
    }

    @Test
    public void test_negative_numbers(){
        Assertions.assertAll("",
            () -> Assertions.assertEquals("0.0",test.add("-0.0,0"),"Chaine \"0,0\", résultat 0.0"),
            () -> Assertions.assertEquals("0.9",test.add("-1.1,2"),"Chaine \"-1.1,2\", résultat 0.9"),
            () -> Assertions.assertEquals("-7.0",test.add("5.5,-5.5,-7"),"Chaine \"5,6,7\", résultat 18.0")
        );
    }

    @Test
    public void test_any_number_of_numbers(){
        Assertions.assertAll("",
            () -> Assertions.assertEquals("0.0",test.add("0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0"),"Chaine \"0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\", résultat 0.0"),
            () -> Assertions.assertEquals("64.1",test.add("1.1,2,5.8,35.8,19.4"),"Chaine \"1,2\", résultat 64.1"),
            () -> Assertions.assertEquals("7.0",test.add("-5.5,5.5,7"),"Chaine \"5,6,7\", résultat 18.0")
        );
    }

}