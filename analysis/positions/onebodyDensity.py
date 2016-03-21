import numpy as np
import matplotlib.pyplot as plt


class Density:
    
    def __init__(self,filename):
        self.filename = filename
        self.densities = [] 
        self.rs        = []
        self.x_and_ys  = []

    def getCoords(self,Ncycles=10):

        with open(self.filename,'r') as infile:
            line    = infile.readline().split()
            cycles  = np.zeros((Ncycles,int(line[1]),int(line[2])))#(int(line[0])-1,int(line[1]),int(line[2])))
            for i,line in enumerate(infile.readlines()):
                if i == Ncycles:
                    break
                particles = line.strip().split(";") 
                for j,particle in enumerate(particles):
                    coords = particle.split(",")
                    for k,coord in enumerate(coords):
                        cycles[i,j,k] = float(coord)
        self.cycles = cycles
    
    def oneBodyDensity(self):
        r = []
        for particle in self.cycles:
            r.append(np.linalg.norm(particle))
        fig, ax = plt.subplots()
        ax.hist(r,bins=1000,histtype='step')
        plt.show()




    def getDensity(self,particles,dr):
        r = []
        x_and_y = []
        for particle in particles:
            x_and_y.append(particle[0:2])
            r.append(np.linalg.norm(particle))
        r = np.asarray(r)
        maxRad  = np.max(r)
        density = []  
        shells  = []
        shell = 0 
        i = 0
        while shell<maxRad:
            density.append(len(np.where(np.logical_and(r>=shell, r<(shell+dr)))[0]))
            shells.append(shell+dr)
            shell += dr
            i += 1
        
        self.dr = dr
        self.x_and_ys.append(x_and_y)
        self.rs.append(r)
        self.densities.append(density)
        self.shells = shells

    def cross(self,densNR=0,distNR=0):
        dist = np.asarray(self.x_and_ys[distNR])
        density = np.asarray(self.densities[densNR])
        fig,ax = plt.subplots(1,2,figsize=(10,5))
        circles = [] 
        for shell in self.shells:
            ax[1].add_patch(plt.Circle((0,0),shell,fill=False))
         
        ax[1].scatter(np.abs(dist[:,0]),np.abs(dist[:,1]))
        ax[1].set_xlim(0,1)
        ax[1].set_ylim(0,1)
        ax[1].set_xlabel('x')
        ax[1].set_ylabel('y')

        plt.legend()
        ax[0].plot(self.shells,density)
        ax[0].set_ylabel("Number of particles")
        ax[0].set_xlabel("Distance from origo")
        plt.savefig("dist.pdf")
        plt.show()



if __name__=="__main__":
    filename = "positions.out"

    dense = Density(filename)
    dense.getCoords(8000)
    #dense.oneBodyDensity()
    dense.getDensity(particles=dense.cycles[7999],dr=0.1)
    dense.cross()
