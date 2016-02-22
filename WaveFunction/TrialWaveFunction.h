#pragma once
#include "WaveFunction.h"

class TrialWaveFunction : public WaveFunction
{
  public:
    TrialWaveFunction		  (class System* system);
    double evaluate		    ();
    double computeDoubleDerivative  (int p, int d, double waveFunctionCurrent);
    double computeDerivative	    (int p, int d, double waveFunctionCurrent);
    double computeQuantumForce	    (int p, int d, double waveFunctionCurrent);
    double computeEnergy	    (){return 0;}
};
