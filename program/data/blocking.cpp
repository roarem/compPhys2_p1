#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <sys/stat.h>

void readFile (double*, int);

int main()
{
  
  int	  nSamples;
  double  results;
  
  readFile(&results, nSamples);
  std::cout << nSamples << std::endl;

  return 0;
}

void readFile (double &output, int n)
{
  struct stat result;
  
  if(stat("energies.out", &result) == 0){
    n = result.st_size;
  }
  else{
    std::cerr << "error in getting file size" << std::endl;
  }

  output = new double[n];
  std::ostringstream ost;
  std::ifstream inFile;
  inFile.open(ost.str().c_str(), std::ios::in | std::ios::binary);
  inFile.read((char*)&(output[n]),result.st_size);
  inFile.close();
}
