import re

class ReadFile:

    def __init__(self):
        self.datalist = []

    def collect(self,inFile=None):
        ansi_escape = re.compile(r'\x1b[^m]*m')
        for line in inFile:
            if "particles" in line:
                nPart = int(ansi_escape.sub("",line).strip().split()[-1])
            if "dimensions" in line:
                nDim =  int(ansi_escape.sub("",line).strip().split()[-1])
            if "Seconds" in line:
                seconds =  int(ansi_escape.sub("",line).strip().split()[-1])
            if "Milliseconds" in line:
                milli =  int(ansi_escape.sub("",line).strip().split()[-1])
            if "Expectation" in line:
                expectation = float(ansi_escape.sub("",line).strip().split()[-1])
            if "Accept" in line:
                acceptRatio = float(ansi_escape.sub("",line).strip().split()[-1])
            if "cycles" in line:
                nCycles = float(ansi_escape.sub("",line).strip().split()[-1])
            if "Variance" in line:
                variance = float(ansi_escape.sub("",line).strip().split()[-1])





if __name__=="__main__":

    read = ReadFile()
    with open("imp/1e6anad1p1",'r') as f:

        read.collect(f)
