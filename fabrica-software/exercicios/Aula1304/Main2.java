import java.util.ArrayList;

class Main {
    public static void main(String[] args) {
        ArrayList<Integer> nums = new ArrayList<>();
        for (int i = 1000; i > 0; i = i- 2) {

            nums.add(i);
        }
        System.out.println(nums);
 
    }
}