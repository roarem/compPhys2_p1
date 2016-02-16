#include "HarmonicOscillator.h"


HarmonicOscillator::HarmonicOscillator (System* system, double omega) :
  Hamiltonian(system)
{
  my_omega = omega;
}

double HarmonicOscillator::computeLocalEnergy ()
{
  double potEnergy	      = 0;
  double kinEnergy	      = 0;
  double doubleDerivative     = 0;
  double waveFunctionCurrent  = my_system->get_waveFunction()->evaluate();
  
  for (int p = 0 ; p < my_system->get_nParticles() ; p++){
    for (int d = 0 ; d < my_system->get_nDimensions() ; d++){

      potEnergy += my_system->get_particle()[p]->get_position()[d]*
		   my_system->get_particle()[p]->get_position()[d];
      doubleDerivative += my_system->get_waveFunction()->
			  computeDoubleDerivative(p,d,waveFunctionCurrent);
    }
  }

  kinEnergy = -0.5*doubleDerivative/waveFunctionCurrent;
  potEnergy = 0.5*potEnergy*my_system->get_parameters()[1]*
			    my_system->get_parameters()[1];
  return kinEnergy + potEnergy;
}
 
 
