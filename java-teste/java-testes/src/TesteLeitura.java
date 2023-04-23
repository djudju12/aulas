// import com.google.common.io.*;
import java.io.*;


public class TesteLeitura{

   public static void main(String[] args) {
      // Nao achei uma maneira mais facil de ler um path sem ser scapando os \ 
      File file = new File("C:\\Users\\jonathan.santos\\Desktop\\unisc\\aulas\\java-teste\\java-testes\\samples\\lena.bmp");
      // Path file = File.toPath("C:\\Users\\jonathan.santos\\Desktop\\unisc\\aulas\\java-teste\\java-testes\\samples\\lena.bmp");

         try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = fis.readAllBytes();

            for (byte b: buffer){
               System.out.print(b);
            }

         } catch (IOException e) {
            e.printStackTrace();
      }
   }
}