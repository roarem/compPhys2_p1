#pragma once
#include "Hamiltonian.h"
#include <vector>

class HarmonicOscillator : public Hamiltonian
{
  public:
    
    HarmonicOscillator( System* system, double omega);

    double computeLocalEnergy		();
  private:

    double my_omega   = 0;
}

