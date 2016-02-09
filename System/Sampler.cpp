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
  cout << "accumulated energy average: " << cumulativeEnergy/(double)my_stepNumber << endl;;
  cout << (cumulativeEnergy*cumulativeEnergy/(double)my_stepNumber - cumulativeEnergy2)/(double)my_stepNumber <<endl;
  cout << "Acceptence ratio: " << cumulativeAcceptanceRate/(double)my_stepNumber << endl;
}
