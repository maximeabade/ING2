public class Exo1{

    public boolean existNumber(Integer i, Integer nbATrouver){
        String tempString = i.toString();
        return tempString.contains(nbATrouver.toString());
    }


    public String fizzBuzz(Integer i){
        String res = "";
        if ( (i%3 == 0) || (existNumber(i,3))){
            res = res + "Fizz";
        }
        if ((i%5 == 0) || (existNumber(i,5))){
            res = res + "Buzz";
        }
        if (res == ""){
            res = i.toString();
        }
        return (res);
    }
}