import subprocess as sub
import argparse
import time
import os

class Make:

    def __init__(self, root_folder, dev_folders, build_folder):
        self.root_folder = root_folder+'/'
        self.dev_folders = dev_folders
        self.build_folder = self.root_folder+build_folder+'/'


    def make(self):

        print('\n\nWarming up the compiler')
        print('-'*100)
        print(' ')
        pyntSize  = 30

        for folder in self.dev_folders:
            size = pyntSize-len(folder)//2 
            if len(folder)%2 == 0:
                
                outString = '\033[1;44m*\033[1;m'*size+' \033[1;36m'+folder+'\033[1;m  '+'\033[1;44m*\033[1;m'*size
            else:
                outString = '\033[1;44m*\033[1;m'*size+' \033[1;36m'+folder+'\033[1;m '+'\033[1;44m*\033[1;m'*size
                 
            print(outString)
            folder = self.root_folder+folder+'/'
            cpile = sub.Popen(['make','-C',folder],stdout=sub.PIPE,stderr=sub.PIPE)
            cpile.wait()
            cpile_out = cpile.stdout.read().decode('utf-8')
            cpile_err = cpile.stderr.read().decode('utf-8')
            print("\033[1;41m"+cpile_err+"\033[1;m")
            print("\033[1;32m"+cpile_out+"\033[1;m")
            #print(cpile_out.decode('utf-8'))
            copy = sub.Popen('cp '+folder+'*.o '+self.build_folder,shell=True)
            print(' ')
            print('-'*100+'\n')
        print('.'*100)
        print('Done compiling everything, starting on the linking.')    
        time.sleep(0.01)
        cpile = sub.Popen(['make','-C',self.build_folder],stdout=sub.PIPE)
        cpile.wait()
        print('.'*100)
        print('Done compiling, taking some time off\n\n')

    def clean(self):

        for folder in self.dev_folders:
            folder = self.root_folder+folder+'/'
            clean = sub.Popen(['make','-C',folder,'clean'])
            clean.wait() 
        
        print('Cleaning up the build folder...')
        clean = sub.Popen(['make','-C',self.build_folder,'clean'])
        print('Sparkling clean')



            
if __name__=='__main__':
    root_folder = os.getcwd()
    #root_folder = '/home/roar/fys4411/compPhys2_p1'
    #root_folder = '/home/rat/fys4411/compPhys2_p1'
    ##root_folder = '/uio/hume/student-u49/roarem/compPhys2_p1'
    build_folder = 'build'
    dev_folders = ['System', 'Sampler', 'Hamiltonian', 'WaveFunction','InitialState', 'main']

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
CXXFLAGS=-Wall -std=c++11

SRCS=$(wildcard *.cpp)

OBJS=$(subst .cpp,.o,$(SRCS))

all: $(OBJS)

    $(echo Done compiling.)

clean:
        rm $(OBJS)
'''
