class Produto {
    private String nome;
    private Double preco;
    private int estoque;

    Produto(String nome, Double preco, int estoque){
        this.nome = nome;
        this.preco = preco;
        this.estoque = estoque;
    }
 
    public double getPreco(){
        return this.preco;
    }
    public String getNome(){
        return this.nome;
    }

    public int getEstoque(){
        return this.estoque;
    }

    public int setEstoque(int estoque){
        return this.estoque = estoque;
    }
}
