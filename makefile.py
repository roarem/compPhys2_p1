import subprocess as sub
import argparse
import time

class Make:

    def __init__(self, root_folder, dev_folders, build_folder):
        self.root_folder = root_folder+'/'
        self.dev_folders = dev_folders
        self.build_folder = self.root_folder+build_folder+'/'


    def make(self):

        print('Warming up the compiler')
        for folder in self.dev_folders:
            print('Compiles in folder '+folder)
            folder = self.root_folder+folder+'/'
            cpile = sub.Popen(['make','-C',folder],stdout=sub.PIPE)
            cpile.wait()
            copy = sub.Popen('cp '+folder+'*.o '+self.build_folder,shell=True)
	print('Done compiling everything, starting on the linking.')	
	time.sleep(0.01)
	cpile = sub.Popen(['make','-C',self.build_folder],stdout=sub.PIPE)
	cpile.wait()
        print('Done compiling, taking some time off')

    def clean(self):

        for folder in self.dev_folders:
            folder = self.root_folder+folder+'/'
            clean = sub.Popen(['make','-C',folder,'clean'])
            clean.wait() 
        
        print('Cleaning up the build folder...')
        sub.Popen('rm '+self.build_folder+'*.o',shell=True)
        print('Sparkling clean')



            
if __name__=='__main__':
    #root_folder = '/home/rat/fys4411/compPhys2_p1'
    root_folder = '/uio/hume/student-u49/roarem/compPhys2_p1'
    build_folder = 'build'
    dev_folders = ['wavefunctions', 'main']

    parser = argparse.ArgumentParser()
    parser.add_argument('clean',nargs='?',default=None, help='Cleans')
    args = parser.parse_args()

    compiling = Make(root_folder, dev_folders, build_folder)

    if args.clean == None:
        compiling.make()
    if args.clean == 'clean':
        compiling.clean()







#A MAKEFILE EXAMPLE:
MAKEFILE='''
CXX=g++
CXXFLAGS=-Wall -std=c++11 -c

SRCS=$(wildcard *.cpp)

OBJS=$(subst .cpp,.o,$(SRCS))

all:
	for source in $(SRCS); do \
	  $(CXX) $(CXXFLAGS) $$source; \
	done

clean:
	rm $(OBJS)
'''
