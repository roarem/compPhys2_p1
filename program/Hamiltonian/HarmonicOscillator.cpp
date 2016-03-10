#include "HarmonicOscillator.h"


HarmonicOscillator::HarmonicOscillator (System* system) :
  Hamiltonian(system)
{
}

double HarmonicOscillator::computeLocalEnergy ()
{
  int	 nD		      = my_system->get_nDimensions();
  int	 nP		      = my_system->get_nParticles();
  double potEnergy	      = 0;
  double kinEnergy	      = 0;
  double doubleDerivative     = 0;
  double alpha		      = my_system->get_parameters()[0];
  double omega2		      = my_system->get_parameters()[1]*
				my_system->get_parameters()[1];
  double gamma2		      = my_system->get_parameters()[2]*
				my_system->get_parameters()[2];
  double waveFunctionCurrent  = my_system->get_waveFunction()->evaluate();
  
  
  for (int p = 0 ; p < nP ; p++){
    for (int d = 0 ; d < nD ; d++){
      const double x = my_system->get_particle()[p]->get_position()[d];
      if (d==2){
	potEnergy += x*x*gamma2;
      }
      else{
        potEnergy += x*x*omega2;

      }
      //kinEnergy -= (2*alpha*x*x - nD);
      doubleDerivative += my_system->get_waveFunction()->
			  computeDoubleDerivative(p,d,waveFunctionCurrent);
    }
  }

  kinEnergy = -0.5*doubleDerivative/waveFunctionCurrent;
  //kinEnergy = kinEnergy*alpha;
  potEnergy = 0.5*potEnergy;
		  
  return kinEnergy + potEnergy;
}
 
 
