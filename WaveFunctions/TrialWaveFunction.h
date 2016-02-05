#pragma once
#include "WaveFunction.h"
#include <cmath>

class TrialWaveFunction : public WaveFunction
{
  public:
    TrialWaveFunction	    (class System* system, double alpha);
    double evaluate	    (std::vector<class Particle*> particles);
    double secondDerivative (std::vector<class Particle*> particles);
};
