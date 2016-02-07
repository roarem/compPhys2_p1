#pragma once
#include "WaveFunction.h"
#include <cmath>

class TrialWaveFunctionAna : public WaveFunction
{
  public:
    TrialWaveFunctionAna	  (class System* system, 
				   double alpha,  
				   double omega);
    double evaluate		  ();
    double computeEnergy	  ();

  protected:
};
