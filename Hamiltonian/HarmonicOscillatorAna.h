#pragma once
#include "Hamiltonian.h"
#include <vector>

class HarmonicOscillatorAna : public Hamiltonian
{
  public:
    
    HarmonicOscillatorAna( System* system);

    double computeLocalEnergy		();
  private:
};

