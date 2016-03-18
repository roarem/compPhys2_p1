#pragma once
#include "HarmonicOscillator.h"


class HarmonicOscillatorInteracting: public HarmonicOscillator
{
  public:

    HarmonicOscillatorInteracting( System* system, double bosonSize);
    
    double computeLocalEnergy  ();
    double u_mark	       (double r);
    double u_2mark	       (double r);

  private:
    double my_bosonSize	 = 0.0;
    double my_bosonSize2 = 0.0;
};
