public class Exo2{


// public String add(String st){
//         Integer count = 0;

//         for(int i = 0; i < st.length(); i++) {    
//         if( Character.isDigit(st.charAt(i)))    
//             count += Character.getNumericValue(st.charAt(i)) ;    
//         }    

//         return count.toString();
//     }

// }

public String add(String st){
        Integer count = 0;
        String[] arr = st.split(",");
        Boolean isNumeric;
        
        for(int i = 0; i < arr.length; i++) {
            isNumeric = true;
            for (int j = 0;  j< arr[i].length(); j++) {
                if (!Character.isDigit(arr[j].charAt(j))) {
                    isNumeric = false;
                }
            }
            if( isNumeric){
                count += Integer.parseInt(arr[i]) ;    
            }
        }    

        return count.toString();
    }

}