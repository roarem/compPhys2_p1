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
        self.meanValue  = 0
        self.varValues  = 0
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

            varVal = np.var(blockValues)
            varValues[i] = varVal
            stdValues[i] = np.sqrt(varVal/(self.Npoints/size))
            #print(stdValues[i])

        self.varValues = varValues[::-1]
        self.stdValues = stdValues[::-1]
        self.blockSize = blockSize[::-1]
    '''
    def mean(self, data):
        
        return np.sum(data)/len(data)

    def variance(self, data):

        valueSquared    = np.sum(np.square(data))/len(data)
        valueMean       = self.mean(data) 

        varValue = valueSquared - valueMean**2
        return varValue
    '''

if __name__=="__main__":
    filename    = "energies.out"
    read        = ReadFile(filename)
    stats       = Statistics(read.get_data())
    stats.blocking(1,6000,3000)
    
    plt.plot(stats.blockSize,stats.stdValues)
    plt.show()
    #print(stats.STDValue,stats.meanValue,stats.varValue)
