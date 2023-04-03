from tkinter import *
import numpy as np

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure

window_width = 1000
window_height = 600

root = Tk()

fig = Figure(figsize=(5, 4), dpi=100)

canvas = FigureCanvasTkAgg(fig, master=root)  # A tk.DrawingArea.
canvas.get_tk_widget().pack(side=TOP, fill=BOTH, expand=1)

def draw_chart():
    fig.clear()
    fig.add_subplot(111).plot(np.random.randint(1,10,5), np.random.randint(10,20,5)) #generate random x/y
    canvas.draw_idle()

Button(root,text="Draw",command=draw_chart).pack()

root.mainloop()