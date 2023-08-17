import tkinter as tk
from tkinter import messagebox
def checa_admin(senha, login):
    if senha == "admin" and login == "admin":
        messagebox.showinfo("Login", "boa camarada")
    else:
        messagebox.showinfo("Login", "senha incorreta")
    pass 

def main():
    window = tk.Tk()
    window.title("Simple Text Editor")
    frame1 = tk.Frame(master=window, height=100)
    frame1.pack(side=tk.TOP, fill="x")

    login_label = tk.Label(frame1, text="Usuario")
    login_entry = tk.Entry(frame1, width=13)
    login_label.pack(side=tk.LEFT)
    login_entry.pack(side=tk.RIGHT)

    frame2 = tk.Frame(master=window)
    frame2.pack()
    senha = tk.Label(frame2, text="Senha:")
    senha_entry = tk.Entry(frame2, width=13)
    senha.pack(side=tk.LEFT)
    senha_entry.pack(side=tk.RIGHT)

    frame3 = tk.Frame(master=window)
    frame3.pack(side=tk.RIGHT)

    button = tk.Button(frame3, text="Entrar", command=lambda: checa_admin(senha_entry.get(), login_entry.get()))
    button.pack()

    window.mainloop()

if __name__ == '__main__':
    main()