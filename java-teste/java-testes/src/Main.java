import java.io.*;
public class Main{

   public static void main(String[] args) {
      BMP image = new BMP();
      File file = new File("C:\\Users\\jonathan.santos\\Desktop\\unisc\\aulas\\java-teste\\java-testes\\samples\\lena.bmp");
      image.readBytes(file);
      System.out.print(image.isBpmFile());
   }
}