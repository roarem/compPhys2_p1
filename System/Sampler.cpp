#include "Sampler.h"
#include <iostream>
using std::cout;
using std::endl;

Sampler::Sampler(System* system){
  my_system	= system;
  my_stepNumber = 0;
}

void Sampler::sample (bool accepted)
{
  if (my_stepNumber == 0)
  {
    cumulativeEnergy	      = 0;
    cumulativeEnergy2	      = 0;
    cumulativeAcceptanceRate  = 0;
  }

  double localEnergy = my_system->get_hamiltonian()->computeLocalEnergy();

  cumulativeEnergy	    += localEnergy;
  cumulativeEnergy2	    += localEnergy*localEnergy;
  cumulativeAcceptanceRate  += accepted;
  my_stepNumber		    += 1;
} 

void Sampler::printResults ()
{
  double energyAverage	=  cumulativeEnergy/(double)my_stepNumber;
  double energy2Average =  cumulativeEnergy2/(double)my_stepNumber;
  double variance	=  energy2Average - energyAverage*energyAverage;
//  double variance	=  (cumulativeEnergy2 - cumulativeEnergy*
//			   cumulativeEnergy/(double)my_stepNumber)/
//			   (double)my_stepNumber;
  double acceptanceRatio= cumulativeAcceptanceRate/(double)my_stepNumber;

  printf("\033[1;44m====================  System Data ====================\033[1;m\n");
  printf("\033[0;32mEnergy average:		    %e\033[0;m\n", energyAverage);
  printf("\033[0;32mVariance:		    %e\033[0;m\n",variance);
  printf("\033[0;32mAcceptance ratio:	    %f\033[0;m\n",acceptanceRatio);
}
