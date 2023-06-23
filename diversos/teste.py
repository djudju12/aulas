import json


def main():
    import csv
    import pandas as pd
    
    df = pd.read_csv("produtos.csv")

    with open("teste3.csv", "w", newline="") as f:
        csv_writer = csv.writer(f)
        csv_writer.writerow(['produtoId', 'produtoDescricao', 'produtoValor', 'categoria'])
        for i, row in enumerate(df['itens']):
            row_json = json.loads(row)
            for venda in row_json:
                csv_writer.writerow([
                    df['idPedido'][i],
                    venda['produto']['produtoId'],
                    venda['produto']['produtoDescricao'],
                    venda['produto']['produtoValor'],
                    venda['produto']['categoria']
                ])

if __name__ == '__main__':
    main()