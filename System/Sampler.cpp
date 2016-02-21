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
  int	 nParticles	= my_system->get_nParticles();
  int	 nDimensions	= my_system->get_nDimensions(); 
  int	 nCycles	= my_system->get_nCycles();
  double stepLength	= my_system->get_stepLength();
  double derivativeStep	= my_system->get_derivativeStep();
  double energyAverage	= cumulativeEnergy/(double)my_stepNumber;
  double energy2Average = cumulativeEnergy2/(double)my_stepNumber;
  double variance	= energy2Average - energyAverage*energyAverage;
//  double variance	=  (cumulativeEnergy2 - cumulativeEnergy*
//			   cumulativeEnergy/(double)my_stepNumber)/
//			   (double)my_stepNumber;
  double acceptanceRatio= cumulativeAcceptanceRate/(double)my_stepNumber;

  printf("\033[1;44m====================  System Data ====================\033[1;m\n");
  printf("\033[0;93mNumber of particles:     %i\033[0;m\n",nParticles);
  printf("\033[0;93mNumber of dimensions:    %i\033[0;m\n",nDimensions);
  printf("\033[0;93mNumber of cycles:        %i\033[0;m\n",nCycles);
  printf("\033[0;93mStep length:             %f\033[0;m\n",stepLength);
  printf("\033[0;93mDerivative step:         %f\033[0;m\n",derivativeStep);
  printf("\033[1;105m~~~~~~~~~~~~~~~~~~~~~ Results ~~~~~~~~~~~~~~~~~~~~~~~~\033[1;m\n");
  printf("\033[0;91mEnergy average:          %e\033[0;m\n", energyAverage);
  printf("\033[0;91mVariance:                %e\033[0;m\n",variance);
  printf("\033[0;91mAcceptance ratio:        %f\033[0;m\n",acceptanceRatio);
}
