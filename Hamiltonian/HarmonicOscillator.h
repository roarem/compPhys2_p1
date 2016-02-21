#pragma once
#include "Hamiltonian.h"
#include <vector>

class HarmonicOscillator : public Hamiltonian
{
  public:
    
    HarmonicOscillator( System* system);

    double computeLocalEnergy		();
  private:

};

