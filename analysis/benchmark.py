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
                particles = line.split()[-1]
                temp_string += "{} & ".format(line.split()[-1])
            if i==14:
                temp_string += "{} & ".format(line.split()[-1])
            if i==15:
                temp_string += "{} & ".format(line.split()[-1])
            if i==16:
                temp_string += "{} & ".format(line.split()[-1])
            if i==22:
                temp_string += "{} ".format(line.split()[-1])
        if int(particles) == 500:
            self.string += temp_string+"\\\ \\hline \n"
        else:
            self.string += temp_string+"\\\ \\hline \n"

    def end(self,label):
        self.string += "\label{%s} \n"%label+"\end{tabular}"

if __name__=="__main__":
    read = ReadFile()
    
    for method in ["hastings","imp"]:
        for d in [1,2,3]:
            with open("tables/{}_ana{}dim.tex".format(method,d),'w') as outfile:
                read.start("Analytical {}D".format(d))
                for p in [1,10,100,500]:
                    with open("{}/1e6anad{}p{}".format(method,d,p),'r') as infile:
                        read.collect(infile)
                read.end(method[0]+":a{}".format(d))
                outfile.write(read.string)
            with open("tables/{}_num{}dim.tex".format(method,d),'w') as outfile:
                read.start("Numerical {}D".format(d))
                for p in [1,10,100,500]:
                    with open("{}/1e6numd{}p{}".format(method,d,p),'r') as infile:
                        read.collect(infile)
                read.end(method[0]+":n{}".format(d))
                outfile.write(read.string)
