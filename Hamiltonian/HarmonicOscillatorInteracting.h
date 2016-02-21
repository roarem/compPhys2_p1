#pragma once
#include "HarmonicOscillator.h"


class HarmonicOscillatorInteracting: public HarmonicOscillator
{
  public:

    HarmonicOscillatorInteracting( System* system, double bosonSize);
    
    double computeLocalEnergy  ();

  private:
    double my_bosonSize	= 0.0;
};