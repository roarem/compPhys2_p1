#pragma once
#include "System.h"
#include "Particle.h"
#include "Timer.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../WaveFunction/WaveFunction.h"



class Sampler {
  public:
    Sampler(class System* system);

    void sample		(bool accepted);
    void printResults	();
    
    double get_cumuEn (){return cumulativeEnergy;}

  protected:
    int	    my_nCycles		      = 0;
    int	    my_stepNumber	      = 0;
    double  cumulativeEnergy	      = 0;
    double  cumulativeEnergy2	      = 0;
    double  cumulativeAcceptanceRate  = 0;
    class   System* my_system	      = nullptr;
};

