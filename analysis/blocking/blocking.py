import matplotlib.pyplot as plt
import numpy as np

class ReadFile:

    def __init__(self, filename=None):
        self.data = np.fromfile(\
                file=filename,\
                dtype=float,\
                count=-1,\
                sep="")

    def get_data(self):
        return self.data

class Statistics:

    def __init__(self,data):

        self.data       = data
        self.Npoints    = len(self.data)
        self.stdValues  = 0
        self.blockSize  = 0

    def blocking(self,minBlock, maxBlock, nBlockSamples):

        nBlocks = int(self.Npoints/nBlockSamples)
        blockValues = np.zeros(nBlocks)

        blockStepLength = int((maxBlock - minBlock)/nBlockSamples)
        blockSize = minBlock + np.arange(nBlockSamples)*blockStepLength

        varValues   = np.zeros(len(blockSize))
        stdValues   = np.zeros(len(blockSize))

        for i,size in enumerate(blockSize):
            for j in range(nBlocks-1):
                blockValues[j] = np.mean(self.data[j*size:(j+1)*size])

            varVal = np.var(blockValues,ddof=0)
            varValues[i] = varVal
            stdValues[i] = np.sqrt(varVal/nBlocks)

        self.stdValues = stdValues[::]
        self.blockSize = blockSize[::]

    def plotting(self, save=True):

        fig, ax = plt.subplots(figsize=(10,5))
        ax.plot(self.blockSize,self.stdValues)
        ax.set_xlabel("Block size")
        ax.set_ylabel("$\sigma$")
        #ax.set_yscale("log")
        plt.ticklabel_format(style='sci', axis='y',scilimits=(0,0))

        if save:
            plt.savefig("STDBlocking.pdf")
        else:
            plt.show()

    def writeData(self):
        with open("outBlock.out","w") as out:
            for col1, col2 in zip(self.blockSize,self.stdValues):
                out.write("{},{}\n".format(col1,col2))



if __name__=="__main__":
    filename    = "energies.out"
    read        = ReadFile(filename)
    stats       = Statistics(read.get_data())
    stats.blocking(1,8000,6000)

    stats.writeData()
    stats.plotting(save=True)
    #fig, ax = plt.subplots()
    #ax.plot(read.data)
    #plt.show()
