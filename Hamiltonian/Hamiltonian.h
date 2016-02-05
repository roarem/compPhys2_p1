#pragma once
#include "../WaveFunctions/WaveFunction.h"
#include "../System/System.h"
#include "../System/Particle.h"

class Hamiltonian
{
  public:

    Hamiltonian (class System* system);

    virtual double computeLocalEnergy (std::vector <class Particle*> particles) = 0;

  protected:
    
    class System* my_system = nullptr;

}
