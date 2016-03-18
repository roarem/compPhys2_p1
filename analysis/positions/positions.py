from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np

class ReadFile:

    def __init__(self, filename=None):
        self.date = open(filename)
    def get_data(self):
        return self.data

class Positions:
    
    def __init__(self, filename):
        self.fig = plt.figure()
        self.ax  = self.fig.add_subplot(111, projection='3d')
        self.filename = filename 
        self.ani = animation.FuncAnimation(self.fig,self.animate,interval=10)

    def readData(self):
        
        with open(self.filename,'r') as infile:
            line = infile.readline().split()
            cycles      = np.zeros((int(line[0])-1,int(line[1]),int(line[2])))
            for i,line in enumerate(infile.readlines()):
                particles = line.strip().split(";") 
                for j,particle in enumerate(particles):
                    coords = particle.split(",")
                    for k,coord in enumerate(coords):
                        cycles[i,j,k] = float(coord)

        print("Done")
        self.cycles = cycles
    def plotting(self,data,i):
        
        self.ax.set_xlim(-4,4)
        self.ax.set_ylim(-4,4)
        self.ax.set_zlim(-4,4)
        self.ax.scatter(data[:,0],data[:,1],data[:,2],label=str(i))
        plt.legend()

    def animate(self,i):
        i = i*10
        data = self.cycles[i,:,:]
        self.ax.clear()
        self.plotting(data,i)

    
       

if __name__=="__main__":
    read = Positions("positions.out")

    read.readData()
    plt.show()

