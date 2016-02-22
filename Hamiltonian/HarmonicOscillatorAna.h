#pragma once
#include "Hamiltonian.h"

class HarmonicOscillatorAna : public Hamiltonian
{
  public:
    
    HarmonicOscillatorAna( System* system);

    double computeLocalEnergy		();
  private:
};

