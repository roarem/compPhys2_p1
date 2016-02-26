#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <sys/stat.h>

int  getFileSize ();
double* readFile (int);

int main()
{
  
  int	  nSamples;
  double*  results;
  
  nSamples = getFileSize();
  results = readFile(nSamples);
  std::cout << nSamples << std::endl;
  std::cout << results[10000] << std::endl;
  return 0;
}

double* readFile (int n)
{
  double* output;
  output = new double [n];
  std::ostringstream ost;
  std::ifstream inFile;
  inFile.open(ost.str().c_str(), std::ios::in | std::ios::binary);
  inFile.read((char*)&(output[n]),n);
  inFile.close();
  return output;
}

int getFileSize ()
{
  int n;
  struct stat result;
  
  if(stat("energies.out", &result) == 0){
    n = result.st_size;
  }
  else{
    std::cerr << "error in getting file size" << std::endl;
  }
  return n;
}
