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
  double variance	=  (cumulativeEnergy2 - cumulativeEnergy*
			   cumulativeEnergy/(double)my_stepNumber)/
			   (double)my_stepNumber;
  double acceptanceRatio= cumulativeAcceptanceRate/(double)my_stepNumber;

  cout << "====================  System Data ====================\n";
  cout << "Energy average:		    " << energyAverage << endl;
  cout << "Variance:		    " << variance << endl;
  cout << "Acceptance ratio:	    " << acceptanceRatio << endl;
}
