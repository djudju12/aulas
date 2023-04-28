public class Venda {
    private Produto item;
    private int quantidade;

    Venda (Produto item, int quantidade) {
        this.item = item;
        this.quantidade = quantidade;
    }

    public Produto getItem() {
       return this.item;
    }

    public int getQuantidade() {
       return this.quantidade;
    }

    public double getTotalVendas() {
        return this.quantidade * this.item.getPreco();
    }
}

