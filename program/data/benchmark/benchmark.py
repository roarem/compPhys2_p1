#*-*coding: utf-8 *-*
import re

class ReadFile:

    def start(self,string):
        self.string="\\begin{tabular}{|l|l|l|l|l|}\n"+\
                "\\hline \n"+\
                "\\multicolumn{5}{|c|}{%s}\\\ \n"%string+\
                "\\hline \n"+\
                "N particles & $<E>$ & Variance & Accepted & Time [ms]\\\ \n "+\
                "\\hline \n"

    def collect(self,inFile=None):

        ansi_escape = re.compile(r'\x1b[^m]*m')

        temp_string = "" 
        for i,line in enumerate(inFile):
            line = ansi_escape.sub("",line)
            if i==4:
                temp_string += "{} & ".format(line.split()[-1])
            if i==14:
                temp_string += "{} & ".format(line.split()[-1])
            if i==15:
                temp_string += "{} & ".format(line.split()[-1])
            if i==16:
                temp_string += "{} & ".format(line.split()[-1])
            if i==22:
                temp_string += "{} \\\ \n".format(line.split()[-1])
        self.string += temp_string+"\\hline"
    def end(self):
        self.string += "\end{tabular}"

if __name__=="__main__":
    read = ReadFile()
    
    for method in ["hastings","imp"]:
        for d in [1,2,3]:
            with open("tables/{}_ana{}dim.tex".format(method,d),'w') as outfile:
                read.start("Analytical")
                for p in [1,10,100,500]:
                    with open("{}/1e6anad{}p{}".format(method,d,p),'r') as infile:
                        read.collect(infile)
                read.end()
                outfile.write(read.string)
            with open("tables/{}_num{}dim.tex".format(method,d),'w') as outfile:
                read.start("Numerical")
                for p in [1,10,100,500]:
                    with open("{}/1e6numd{}p{}".format(method,d,p),'r') as infile:
                        read.collect(infile)
                read.end()
                outfile.write(read.string)
