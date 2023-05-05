import java.util.Scanner;

class DesafioCriptografia {
    public static void main(String[] args) {
        String in = inputString();
        // String in = new String("if man was meant to stay on the ground god would have given us roots");
        // L eh calculado antes ou depois de retirar os espacos?????
        in = in.replaceAll(" ", "");
        int L = in.length();
        int raizL = (int) Math.sqrt(L);

        int lowerBound = raizL;
        int upperBound = raizL + 1;
        String codificada = codificar(in, upperBound, lowerBound);
        System.out.println(codificada);
    }

    public static String codificar(String in, int upperBound, int lowerBound) {
        String codigo = "";

        //   01234567                  8
        // 0 ifmanwas => 0 1   | (uppderBound) * coluna + linha = 0 ...   1 ... 7
        // 1 meanttos => 8 9   | (uppderBound) * coluna + linha = 8 ...   9 ... 15
        // 2 tayonthe => 16 17 | (uppderBound) * coluna + linha = 16 ... 17 ... 23
        // 3 groundgo => 24 25 | (uppderBound) * coluna + linha = 24 ... 25 ... 31
        // 4 dwouldha => 32 33 | (uppderBound) * coluna + linha = 32 ... 33 ... 39
        // 5 vegivenu => 40 34 | (uppderBound) * coluna + linha = 40 ... 34 ... 47
        // 6 sroots => 48 49   | (uppderBound) * coluna + linha = 48 ... 49 ... 55 (não entra)

        for (int linha = 0; linha < upperBound; linha++){    
            for (int coluna = 0; coluna < lowerBound; coluna++){
                int posicaoChar = (upperBound * coluna) + linha;
                if (posicaoChar < in.length()){
                    codigo += String.valueOf(in.charAt(posicaoChar));
                } 
            }
            codigo += " ";
        }
            return codigo;
    }

    public static String inputString() {
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        sc.close();
        return s;
    }
}