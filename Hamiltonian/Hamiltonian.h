#pragma once
#include "../WaveFunction/WaveFunction.h"
#include "../System/System.h"
#include "../System/Particle.h"

class Hamiltonian
{
  public:

    Hamiltonian (class System* system);

    virtual double computeLocalEnergy () = 0;

  protected:
    
    class System* my_system = nullptr;

};
