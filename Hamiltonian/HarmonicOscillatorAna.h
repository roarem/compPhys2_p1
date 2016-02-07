#pragma once
#include "Hamiltonian.h"
#include <vector>

class HarmonicOscillatorAna : public Hamiltonian
{
  public:
    
    HarmonicOscillatorAna( System* system, double omega);

    double computeLocalEnergy		();
  private:

    double my_omega   = 0;
};

