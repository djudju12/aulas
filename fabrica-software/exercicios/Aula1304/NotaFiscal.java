import java.util.ArrayList;
import java.util.HashMap;

public class NotaFiscal {
    private ArrayList<Venda> itensComprados;

    /**
     * @return
     */
    NotaFiscal () {
        this.itensComprados = new ArrayList<Venda>();
    }

    /**
     * @return
     */
    public double totalVendas(){
        double total = 0;
        
        for (Venda item: this.itensComprados) {
            total = total + item.getTotalVendas();
        }
        return total;
    }

    public void getRelatorio(){
        for(Venda entry: this.itensComprados){
            System.out.println(entry.getItem().getNome());
            System.out.println(entry.getQuantidade());
            System.out.println(entry.getTotalVendas());
            System.out.println("-----");
        }
        System.out.println(this.totalVendas());
    }

    /**
     * @param item
     */
    public void adicionarItem(Venda item){
        this.itensComprados.add(item);;
    }
}