#pragma once
#include "WaveFunction.h"
#include <cmath>

class TrialWaveFunction : public WaveFunction
{
  public:
    TrialWaveFunction		  (class System* system, 
				   double alpha,  
				   double omega);
    double evaluate		    ();
    double computeDoubleDerivative  (int p, int d, double waveFunctionCurrent);
    double computeDerivative	    (int p, int d, double waveFunctionCurrent);
    double computeQuantumForce	    (double waveFunctionCurrent);
    double computeEnergy	    (){return 0;}
};
