#pragma once
#include "WaveFunction.h"

class TrialWaveFunctionAna : public WaveFunction
{
  public:
    TrialWaveFunctionAna	  (class System* system);
    double evaluate		    ();
    double computeDoubleDerivative  (int p, int d, double waveFunctionCurrent){return 0;}
    double computeDerivative	    (int p, int d, double waveFunctionCurrent){return 0;}
    double computeQuantumForce	    (int p, int d, double waveFunctionCurrent){return 0;}
    double computeEnergy	    ();

  protected:
};