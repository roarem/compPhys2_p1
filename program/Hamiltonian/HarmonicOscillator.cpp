#include "HarmonicOscillator.h"


HarmonicOscillator::HarmonicOscillator (System* system) :
  Hamiltonian(system)
{
}

double HarmonicOscillator::computeLocalEnergy ()
{
  double potEnergy	      = 0;
  double kinEnergy	      = 0;
  double doubleDerivative     = 0;
  double omega2		      = my_system->get_parameters()[1]*
				my_system->get_parameters()[1];
  double gamma2		      = my_system->get_parameters()[2]*
				my_system->get_parameters()[2];
  double waveFunctionCurrent  = my_system->get_waveFunction()->evaluate();
  
  for (int p = 0 ; p < my_system->get_nParticles() ; p++){
    for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
      if (d==2){
	potEnergy += my_system->get_particle()[p]->get_position()[d]*
		     my_system->get_particle()[p]->get_position()[d]*
		     gamma2;
      }
      else{
        potEnergy += my_system->get_particle()[p]->get_position()[d]*
		     my_system->get_particle()[p]->get_position()[d]*
		     omega2;

      }
      doubleDerivative += my_system->get_waveFunction()->
			  computeDoubleDerivative(p,d,waveFunctionCurrent);
    }
  }

  kinEnergy = -0.5*doubleDerivative/waveFunctionCurrent;
  potEnergy = 0.5*potEnergy;
		  
  return kinEnergy + potEnergy;
}
 
 
