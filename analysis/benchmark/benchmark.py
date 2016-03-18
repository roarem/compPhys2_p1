#*-*coding: utf-8 *-*
import re
import os

class ReadFile:

    def start(self):
        self.string="\\begin{table}[h!]\n"+\
                "\\centering \n"+\
                "\\begin{tabular}{|l|l|l|l|l|}\n"+\
                "\\hline \n"+\
                "N particles & $<E>$ & Variance & Accepted & Time [s]\\\ \n "+\
                "\\hline \n"

    def collect(self,inFile=None):

        ansi_escape = re.compile(r'\x1b[^m]*m')
        temp_string = "" 

        for i,line in enumerate(inFile):
            #print(i,line)
            line = ansi_escape.sub("",line)
            if i==5:
                particles = line.split()[-1]
                temp_string += "{} & ".format(line.split()[-1])
            if i==15:
                temp_string += "{} & ".format(line.split()[-1])
            if i==16:
                temp_string += "{} & ".format(line.split()[-1])
            if i==17:
                temp_string += "{} & ".format(line.split()[-1])
            if i==23:
                seconds = int(line.split()[-1])/1000
                temp_string += "{} ".format(seconds)
        
        self.string += temp_string+"\\\ \\hline \n"

    def end(self,label):
        self.string += "\end{tabular}\n"+"\label{%s} \n"%label+\
                "\end{table} \n"

if __name__=="__main__":
    tablemaker = ReadFile()
    
    for method in ["hastings","imp"]:
        for anaNum in ["ana","num"]:
            for d in [1,2,3]:
                with open("tables/{}_{}{}dim.tex".format(method,anaNum,d),'w') as outfile:
                    tablemaker.start()
                    for p in [1,10,100,500]:
                        with open("steplong/{}/{}d{}p{}".format(method,anaNum,d,p),'r') as infile:
                            tablemaker.collect(infile)
                    tablemaker.end("tab:"+method[0]+"{}{}".format(anaNum[0],d))
                    outfile.write(tablemaker.string)
