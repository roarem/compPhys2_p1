#pragma once
#include "TrialWaveFunction.h"

class TrialWaveFunctionInteracting : public TrialWaveFunction
{
  public:
    TrialWaveFunctionInteracting    (class System* system, double bosonSize);
    double evaluate		    ();
    //double computeDoubleDerivative  (int p, int d, double waveFunctionCurrent);
    //double computeDerivative	    (int p, int d, double waveFunctionCurrent);
    //double computeQuantumForce	    (int p, int d, double waveFunctionCurrent);
    //double computeEnergy	    (){return 0;}

  protected:
    double my_bosonSize	  = 0;
};


