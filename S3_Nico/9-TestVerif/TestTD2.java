import org.junit.jupiter.api.*;

import java.util.*;

public class TestTD2 {

    private TD2 t;

    @BeforeAll
    private static void start(){
        System.out.println("START");
    }

    @AfterAll
    private static void end(){
        System.out.println("END");
    }

    @BeforeEach
    private void start_test(){
        System.out.println("New Test");
        t = new TD2();
    }

    @AfterEach
    private void end_test(){
        System.out.println("End Test");
        t = null;
    }


    @Test
    @DisplayName("toz")
    private void test_empty(){
        System.out.println("toz le retour");
        Assertions.assertEquals(new int[]{}, t.triBicolore( new int[]{}), "Bah non du coup" );
    }

    //TD3

    //Q1
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
	public void test_valeur_standart(){
		Assertions.assertEquals("1",test.fizzBuzz(1),"On doit afficher le nombre quand c'est ni un multiple de 3 ou 5");
		Assertions.assertEquals("2",test.fizzBuzz(2),"On doit afficher le nombre quand c'est ni un multiple de 3 ou 5");
		Assertions.assertEquals("11",test.fizzBuzz(11),"On doit afficher le nombre quand c'est ni un multiple de 3 ou 5");
	}
	
	@Test
	public void test_div_3_et_5() {
        Assertions.assertAll("FizzBuzz",
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(15),"On doit afficher FizzBuzz pour les multiples de 3 et 5"),
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(30),"On doit afficher FizzBuzz pour les multiples de 3 et 5"),
            () -> Assertions.assertEquals("FizzBuzz",test.fizzBuzz(75),"On doit afficher FizzBuzz pour les multiples de 3 et 5")
        )
		
	}
	
	//Q2

    @Test
    public void test_3_in_number(){
        Assertions.assertEquals("Fizz",test.fizzBuzz(13),"On doit afficher Fizz pour les nombres contenant 3");
    }

    @Test
    public void test_5_in_number(){
        Assertions.assertEquals("Buzz",test.fizzBuzz(58),"On doit afficher Fizz pour les nombres contenant 5");
    }

    @Test
    public void test_div3_cont3(){
        Assertions.assertAll("Fizz",
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(3)),
            () -> Assertions.assertEquals("Fizz",test.fizzBuzz(33))
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


    //TD3 EX2
    @Test
    public void testNb(){
        Assertions.assertEquals("1",test.add("1"),"On retourne 1 quand la chaine possède seulement un nombre");
    }

    @Test
    public void testNb1(){
        Assertions.assertEquals("2",test.add("1,2"),"On retourne 1 quand la chaine possède seulement un nombre");
    }




} 