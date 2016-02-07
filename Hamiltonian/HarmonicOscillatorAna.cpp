#include "HarmonicOscillatorAna.h"


HarmonicOscillatorAna::HarmonicOscillatorAna (System* system, double omega) :
  Hamiltonian(system)
{
  my_omega = omega;
}

double HarmonicOscillatorAna::computeLocalEnergy ()
{
  return my_system->get_waveFunction()->computeEnergy();
}
 
    


