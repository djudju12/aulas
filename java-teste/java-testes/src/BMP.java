import java.io.*;
import java.util.Arrays;

public class BMP {

   private byte[] byteArray; 

   public void readBytes(File file) {
      try (FileInputStream fis = new FileInputStream(file)){
         this.byteArray = fis.readAllBytes();
      } catch (IOException e){
         e.printStackTrace();
      }
   }

   public byte[] getByteArray(){
      if (this.byteArray == null){
         // you cant
      } 
      return this.byteArray;
   }
   
   public boolean isBpmFile(){
      byte[] headerBytes = Arrays.copyOfRange(this.byteArray, 0, 2);
      String headerField = new String();

      for (byte b: headerBytes){
         headerField += (char) b;
      }
      return headerField.equals("BM");
   }

   
}