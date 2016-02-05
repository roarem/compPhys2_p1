#pragma once
#include "WaveFunction.h"
#include <cmath>

class TrialWaveFunction : public WaveFunction
{
  public:
    TrialWaveFunction	    (class System* system, double alpha);
    double evaluate	    ();
    double computeEnergy    ();
};
