class Main {
    public static void main(String[] args) {
        NotaFiscal nf = new NotaFiscal();
        Produto p1 = new Produto("arroz", 5.4, 4);
        Produto p2 = new Produto("feijao", 2.4, 4);
        Produto p3 = new Produto("carne", 29.4, 4);
        Produto p4 = new Produto("pao", 10.4, 4);
        
        Venda v1 = new Venda(p1, 2);
        Venda v2 = new Venda(p2, 2);
        Venda v3 = new Venda(p3, 2);
        Venda v4 = new Venda(p4, 2);
        
        nf.adicionarItem(v4);
        nf.adicionarItem(v1);
        nf.adicionarItem(v3);
        nf.adicionarItem(v2);

        nf.getRelatorio();
    }
}