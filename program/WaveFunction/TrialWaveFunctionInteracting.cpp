#include "TrialWaveFunctionInteracting.h"

TrialWaveFunctionInteracting::TrialWaveFunctionInteracting (System* system,double  bosonSize) :
  TrialWaveFunction(system){
    my_bosonSize = bosonSize;
  }

double TrialWaveFunctionInteracting::evaluate ()
{
  double r2		     = 0;
  double rij2		     = 0;
  double rij	     	     = 0;
  double correlationFunction = 1;
  const double alpha = my_system->get_parameters()[0];
  const double beta  = my_system->get_parameters()[3];

  for (int p1 = 0 ; p1 < my_system->get_nParticles() ; p1++){
    for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
      const double x = my_system->get_particle()[p1]->get_position()[d];
      r2 +=x*x*(d != 2 ? 1 : beta);
    }

    for (int p2 =  p1 + 1; p2 < my_system->get_nParticles() ; p2++){
      rij2 = 0;
      for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
	      const double seperation = my_system->get_particle()[p1]->get_position()[d] -
				                          my_system->get_particle()[p2]->get_position()[d];
	      rij2 += seperation*seperation;
      }
      rij = sqrt(rij2);
      if (rij > my_bosonSize){
	      correlationFunction *= (1 -my_bosonSize/rij);
      }
      else{
	      return 0;
      }
    }
  }
  return exp(-alpha*r2) * correlationFunction;
}

