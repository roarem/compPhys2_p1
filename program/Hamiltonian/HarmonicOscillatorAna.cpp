#include "HarmonicOscillatorAna.h"


HarmonicOscillatorAna::HarmonicOscillatorAna (System* system) :
  Hamiltonian(system)
{
}

double HarmonicOscillatorAna::computeLocalEnergy ()
{
  return my_system->get_waveFunction()->computeEnergy();
}
 
    


