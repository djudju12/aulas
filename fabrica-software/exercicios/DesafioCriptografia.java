import java.util.Scanner;

class DesafioCriptografia {
    public static void main(String[] args) {
        String in = inputString();
        // L eh calculado antes ou depois de retirar os espacos?????
        in = in.replaceAll(" ", "");
        int L = in.length();
        int raizL = (int) Math.sqrt(L);

        int lowerBound = raizL;
        int upperBound = raizL + 1;

        // ifmanwas
        // 0
        // meanttos
        // 8
        // tayonthe
        // 16
        // groundgo
        // 24
        // dwouldha
        // 32
        // vegivenu
        // 40
        // sroots
        // 48

        // ifmanwasmeanttostayonthegroundgodwouldhavegivenusroots
        
        String codificada = codificar(in, lowerBound, upperBound);
        System.out.println(codificada);
    }

    public static String codificar(String in, int upperBound, int lowerBound) {
        String codificada = "";
        System.out.println(in);

        for (int i = 0; i < upperBound; i++) {
            for (int j = 0; j < lowerBound; j++) {
                if (i*j >= in.length()) {
                    return codificada;
                }
                if (((i % upperBound) + j * upperBound) >= in.length()){
                    return codificada;
                }
                System.out.println((i % (upperBound + 1)) + j * (upperBound + 1) );
                // System.out.println(String.valueOf((i % upperBound) + j * upperBound));
                // codificada += String.valueOf(in.charAt((i % upperBound) + j * upperBound));
                codificada += String.valueOf(in.charAt((i % (upperBound + 1)) + j * (upperBound + 1)));
            }
        }
        return codificada;
    }

    public static String inputString() {
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        sc.close();
        return s;
    }
}