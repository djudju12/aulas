public class TestePascoa {

   public static void main(String[] args) {
      int ano = 2023;
      Pascoa p = new Pascoa(ano);

      int dia = p.getDia();
      int mes = p.getMes();

      System.out.printf("Pascoa sera no dia %d do mes %d no ano de %d", dia, mes, ano);
   }
}
