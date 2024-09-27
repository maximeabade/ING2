import java.util.HashMap;
import java.util.Map;

public class counterMaxCar{
        public static char countMaxCar(String input){
        Map< Character, Integer > charMap = new HashMap<>();
        int maxi = 0;
        int cpt = 0;
        char res = 'r';
        for(char key : input.toCharArray()) {
            if(charMap.containsKey(key)) {
                cpt = charMap.get(key);
                charMap.replace(key, cpt++);
            }
            else{charMap.put(key, 1);}
        }
        for(char key : charMap.keySet() ){
            if(charMap.get(key) >= maxi) {
                maxi = charMap.get(key);
                System.out.println("je suis dedans");
                res = key;
            }
        }
        return res;
    }
}
