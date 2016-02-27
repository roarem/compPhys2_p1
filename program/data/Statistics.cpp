#include "Statistics.h"
#include <iostream>

Statistics::Statistics (double* data, int nSamples)
{
  my_data     = data;
  my_nSamples =	nSamples;
}

double Statistics::mean (double* values, int nValues)
{
  double valueMean  = 0;
  double valueSum   = 0;
  for (int i = 0 ; i < nValues ; i++)
    valueSum  +=  values[i];
  valueMean = valueSum/(double)nValues;
  return valueMean;
}

void Statistics::meanAndVariance (double* values, int nSamples)
{
   double value		= 0; 
   double valueSum	= 0;
   double value2Sum	= 0;
   double valueMean	= 0;
   double value2Mean	= 0;

   for (int i = 0 ; i < nSamples ; i++){
     value	=   values[i];
     valueSum	+=  value;
     value2Sum	+=  value*value; 
   }

   valueMean  = valueSum/nSamples;
   value2Mean = value2Sum/nSamples;

   my_mean	  = valueMean;
   my_variance	  = value2Mean - valueMean*valueMean;
   my_standardDev = sqrt(my_variance);
}

void Statistics::Blocking (int minBlockSize, int maxBlockSize, int nBlockSamples)
{
  
  int nBlocks = int(my_nSamples/nBlockSamples);
  int blockStepLength, blockSize;
  ofstream outFile;
  outFile.open("blocked.out", ios::out);

  blockValues = new double[nBlocks];

  blockStepLength = (maxBlockSize - minBlockSize)/nBlockSamples; 
    
  for (int i = 0 ; i < nBlockSamples ; i++){
    blockSize = minBlockSize + i*blockStepLength;
    
    for (int j = 0 ; j < nBlocks ; j++){
      blockValues[j] = mean(my_data+j*blockSize, blockSize);
    }

  meanAndVariance(blockValues, nBlocks);

  outFile << blockSize << " , " << sqrt(my_variance/(my_nSamples/blockSize - 1.0)) << endl;

  }
  outFile.close();
}
