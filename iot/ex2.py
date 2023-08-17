import tkinter as tk
import re 

def contar(e0, e1, e2):
    with open(e0.get(), "r") as f: 
        content = f.read()
        content = re.split(r"\s|,|\.|\n", content)
        content = [x for x in content if x != ""]
        chars = 0
        for word in content:
            for _ in word:
                chars+=1

    e1.insert(0, chars)
    e2.insert(0, len(content))
    

def main():
    window = tk.Tk()
    window.title("Simple Text Editor")

    frame1 = tk.Frame(master=window, height=100)
    frame1.pack(side=tk.TOP, fill="x")

    arquivo_label = tk.Label(frame1, text="Arquivo")
    arquivo_entry = tk.Entry(frame1, width=13)
    arquivo_label.pack(side=tk.LEFT)
    arquivo_entry.pack(side=tk.RIGHT)

    frame2 = tk.Frame(master=window)
    frame2.pack()

    button = tk.Button(frame2, text="Contar", command=lambda: contar(arquivo_entry, total_char_entry, total_pal_entry))
    button.pack()

    frame3 = tk.Frame(master=window)
    frame3.pack()
    total_pal = tk.Label(frame3, text="Total Palavras")
    total_pal_entry = tk.Entry(frame3, width=13)
    total_pal.pack(side=tk.LEFT)
    total_pal_entry.pack(side=tk.RIGHT)

    frame4 = tk.Frame(master=window)
    frame4.pack(side=tk.BOTTOM)
    total_char = tk.Label(frame4, text="Total caracteres")
    total_char_entry = tk.Entry(frame4, width=13)
    total_char.pack(side=tk.LEFT)
    total_char_entry.pack(side=tk.RIGHT)
    window.mainloop()

if __name__ == '__main__':
    main()