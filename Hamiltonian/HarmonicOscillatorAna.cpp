#include "HarmonicOscillator.h"


HarmonicOscillatorAna::HarmonicOscillator (System* system, double omega) :
  Hamiltonian(system)
{
  my_omega = omega;
}

double HarmonicOscillatorAna::computeLocalEnergy ()
{
  return my_system->my_waveFunction->computeEnergy();
}
 
    


