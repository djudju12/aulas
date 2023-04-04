from automaton2D import *
import time
from matplotlib.animation import FuncAnimation
from matplotlib import rcParams

rcParams['toolbar'] = 'None'
fig = plt.figure(figsize=(5, 5))
ax = fig.add_axes([0,0,1,1], frame_on=False)

matrix = make_seed(DENSIDADE)
rules = rule(224)

im = ax.imshow(matrix)

def update_frame(frame):
    next_gen(matrix, rules)
    im.set_data(matrix)

animation = FuncAnimation(fig, update_frame, interval=30, save_count=200)
plt.show()