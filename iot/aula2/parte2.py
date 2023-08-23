import tkinter as tk
from datetime import datetime
from dateutil.relativedelta import relativedelta

def main():
    root = tk.Tk()
    root.title("Meancenter")
    root.geometry("350x150")
    frame1 = tk.Frame(master=root, height=100)
    frame1.pack(side=tk.TOP, fill="x")

    arquivo_label = tk.Label(frame1, text="Dia do nascimento: ", font=("Arial", 15, "bold"))   
    arquivo_entry = tk.Entry(frame1, width=20)
    arquivo_label.pack(side=tk.LEFT)
    arquivo_entry.pack(side=tk.RIGHT)

    frame2 = tk.Frame(master=root)
    frame2.pack(fill="x")

    button = tk.Button(frame2, text="Calcular", font=("Arial", 15, "bold"), height=2, width=8, command=lambda: calcula(arquivo_entry.get(), frame3))
    button.pack()

    frame3 = tk.Frame(master=root)
    frame3.pack(side=tk.BOTTOM, fill="x")
    total_pal = tk.Label(frame3, text="Resultado: ", font=("Arial", 15, "bold"))
    total_pal.pack(side=tk.LEFT)

    root.mainloop()

def calcula(data, frame):
    data = datetime.strptime(data, "%d/%m/%Y")
    resultado = relativedelta(datetime.now(), data)
    label = tk.Label(frame, text=f"{resultado.years} anos, {resultado.months} meses e {resultado.days} dias", font=("Arial", 12, "bold"))
    label.pack(side=tk.RIGHT)

if __name__ == '__main__':
    main()