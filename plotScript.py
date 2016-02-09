import csv
from matplotlib import cm
from matplotlib import pyplot
import pylab
from mpl_toolkits.mplot3d import Axes3D

hFile = open("myTestBox.csv", 'r')
datfile = csv.reader(hFile)
dat = []

for row in datfile:
        dat.append(map(float,row))

temp = zip(*(dat))

fig = pylab.figure(figsize=pyplot.figaspect(.96))
#ax = Axes3D(fig)
ax = fig.gca(projection='3d')
xtext = ax.set_xlabel("Stride") # returns a Text instance
ytext = ax.set_ylabel("N")
ztext = ax.set_zlabel("Throughput")
ax.plot_trisurf(temp[0], temp[1], temp[2], cmap=cm.jet, linewidth=0.2)
pyplot.show()

