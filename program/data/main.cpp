#include "ReadFile.h"
#include "Statistics.h"
//#include <iostream>
//#include <fstream>

using namespace std;

int main(int nargs, char* args[])
{

  int minBlockSize, maxBlockSize, nBlockSamples;
  if (nargs > 3){
    minBlockSize  = atoi(args[1]);
    maxBlockSize  = atoi(args[2]);
    nBlockSamples = atoi(args[3]);
  }
  else{
    cout << "Need minBlockSize, maxBlockSize, nBlocks as input\n";
    exit(1);
  }
  int	  nSamples = 0;
  double* data	   = nullptr;
  ifstream inFile;
  inFile.open("energies.out",ios::in | ios::binary | ios::ate);

  ReadFile* reader = new ReadFile(&inFile);
  nSamples = reader->get_sampleSize(); 

  data = reader->get_input(data);

  Statistics* analyze = new Statistics(data, nSamples);

  analyze->meanAndVariance(analyze->get_data(),analyze->get_nSamples());
  double mean	      = analyze->get_mean();
  double variance     = analyze->get_variance();
  double standardDev  = analyze->get_standardDev();
  cout << "mean	        = " << mean	    << endl;
  cout << "sigma	= " << variance	    << endl;
  cout << "sqrt(sigma)	= " << standardDev  << endl;
  
  analyze->Blocking(minBlockSize, maxBlockSize, nBlockSamples);
  return 0;
}

