import ast
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

fig, ax = plt.subplots(subplot_kw={'projection': '3d'})

x_start, y_start, z_start = [], [], []
x_end, y_end, z_end = [], [], []

for i in range(1,6):
	temp_x, temp_y, temp_z = [], [], []
	with open("data2/kleenex_"+str(i)+".txt") as f:
		for l in f:
			coordinates = ast.literal_eval(l)
			if temp_x != 0.0 and temp_y != 0.0 and temp_z != 0.0:
				temp_x.append(coordinates[0])
				temp_y.append(coordinates[1])
				temp_z.append(coordinates[2])
		x_start.append(temp_x[0])
		y_start.append(temp_y[0])
		z_start.append(temp_z[0])
		x_end.append(temp_x[-1])
		y_end.append(temp_y[-1])
		z_end.append(temp_z[-1])
	temp_x.pop()
	temp_y.pop()
	temp_z.pop()
	ax.plot(temp_x,temp_y,temp_z,label="trajectory_"+str(i))
	ax.legend()

ax.scatter(x_start,y_start,z_start,c='r',marker='o',label="Start point", s=30)
ax.scatter(x_end, y_end, z_end, c='g', marker ='o', label="End point", s=30)

plt.show()