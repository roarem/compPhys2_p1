#include "HarmonicOscillator.h"


HarmonicOscillator::HarmonicOscillator (System* system, double omega) :
  Hamiltonian(system)
{
  my_omega = omega;
}

double HarmonicOscillator::computeLocalEnergy ()
{
  return my_system->my_waveFunction->computeEnergy();
}
 
    

