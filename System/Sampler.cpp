#include "Sampler.h"

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
