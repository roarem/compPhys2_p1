#include "HarmonicOscillatorInteracting.h"

HarmonicOscillatorInteracting::HarmonicOscillatorInteracting(System* system, 
							     double bosonSize):
  HarmonicOscillator(system)
{
  my_bosonSize = bosonSize;
  my_bosonSize2 = bosonSize*bosonSize;
}

double HarmonicOscillatorInteracting::computeLocalEnergy ()
{
  double seperation	      =	  0;
  double r		      =   0;
  double vInt		      =	  0;

  double vExt = HarmonicOscillator::computeLocalEnergy();

  for (int p1 = 0 ; p1 < my_system->get_nParticles()-1 ; p1++){
    for (int p2 = p1 + 1 ; p2 < my_system->get_nParticles() ; p2++){
      r = 0;
      for (int d = 0 ; d < my_system->get_nDimensions() ; d++){

	 seperation = my_system->get_particle()[p1]->get_position()[d] -
		      my_system->get_particle()[p2]->get_position()[d];

	 r += seperation*seperation;
      }
      vInt += (r < my_bosonSize2) * 1e8;
      //cout << vInt << endl;
    }
  }

  return vInt + vExt;
}
      




