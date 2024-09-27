

public class TD4EX2 {

    public String add(String s){

        if (s.equals("")){
            return "0.0";
        }

        String[] tab = s.split(",|\n");
        Double res = 0.0;

        for (int i=0; i<tab.length; i++){
            res += Double.valueOf(tab[i]);
        }

        return String.valueOf(res);

    }

}