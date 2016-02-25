#include "TrialWaveFunctionInteracting.h"

TrialWaveFunctionInteracting::TrialWaveFunctionInteracting (System* system,double  bosonSize) :
  TrialWaveFunction(system){
    my_bosonSize = bosonSize;
  }

double TrialWaveFunctionInteracting::evaluate ()
{
  double r2		     = 0;
  double r	     	     = 0;
  double correlationFunction = 1;
  const double alpha = my_system->get_parameters()[0];
  const double beta  = my_system->get_parameters()[3];

  for (int p1 = 0 ; p1 < my_system->get_nParticles() ; p1++){
    for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
      const double x = my_system->get_particle()[p1]->get_position()[d];
      if (d==2)
	r2 += x*x*beta;
      else
	r2 += x*x;
    }

    for (int p2 =  p1 + 1; p2 < my_system->get_nParticles() ; p2++){
      r = 0;
      for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
	const double seperation = my_system->get_particle()[p1]->get_position()[d] -
				  my_system->get_particle()[p2]->get_position()[d];
	r += seperation*seperation;
      }
      if (r > my_bosonSize){
	correlationFunction *= (1 -my_bosonSize/r);
      }
      else{
	return 0;
      }
    }
  }
  return exp(-alpha*r2) * correlationFunction;
}

